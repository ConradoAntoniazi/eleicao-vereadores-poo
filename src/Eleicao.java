import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.text.NumberFormat;

public class Eleicao {
    private int codigoCidade;
    private String data;
    private int numEleitos;
    private HashMap<Integer, Candidato> candidatos;
    private HashMap<Integer, Partido> partidos;
    
    public Eleicao(int codigo, String data) {
        this.codigoCidade = codigo;
        this.data = data;
        this.candidatos = new HashMap<>();
        this.partidos = new HashMap<>();
    }

    public int getCodigo() {
        return this.codigoCidade;
    }

    public String getData() {
        return this.data;
    }
    
    public void processarCandidatosPartidos(String caminhoArquivo) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(caminhoArquivo), "ISO-8859-1"))) {
            String linha;
            boolean primeiraLinha = true;

            while ((linha = br.readLine()) != null) {
                if (primeiraLinha) {
                    primeiraLinha = false;
                    continue;
                }

                String[] campos = linha.split(";");

                try {
                    int codigoCargo = Integer.parseInt(campos[13].trim().replace("\"", ""));
                    int codigoMunicipio = Integer.parseInt(campos[11].trim().replace("\"", ""));
                    int situacaoTurno = Integer.parseInt(campos[48].trim().replace("\"", ""));
                    if(codigoCargo != 13 || codigoMunicipio != this.codigoCidade || situacaoTurno == -1) continue; //Se não for vereador, não for a cidade que estamos avaliando ou a candidatura for inválida, pula.
                } catch (NumberFormatException e) {
                    System.err.println("Erro ao converter número: " + e.getMessage());
                    return;
                }

                int numPartido = Integer.parseInt(campos[25].trim().replace("\"", ""));
                int numeroFederacao = Integer.parseInt(campos[28].trim().replace("\"", ""));

                if(!this.partidos.containsKey(numPartido)) { //partido não está presente no hashMap, então é criado.
                    this.partidos.put(numPartido, new Partido(Integer.parseInt(campos[25]), campos[26].trim().replace("\"", ""), campos[27].trim().replace("\"", ""), numeroFederacao));
                }

                int numero = Integer.parseInt(campos[16].trim().replace("\"", ""));
                String nomeUrna = campos[18].trim().replace("\"", "");
                String dataNascimento = campos[36].trim().replace("\"", "");
                int genero = Integer.parseInt(campos[38].trim().replace("\"", ""));
                int situacao = Integer.parseInt(campos[48].trim().replace("\"", ""));

                Partido partAux = this.partidos.get(numPartido);
                Candidato candAux = new Candidato(numero, nomeUrna, partAux, dataNascimento, genero, situacao);
                
                //Incrementa o número de eleitos da eleição
                if(candAux.isEleito()) this.numEleitos++;

                this.candidatos.put(numero, candAux);
                partAux.addCandidato(candAux);
            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }
    }

    public void processarVotos(String caminhoArquivo) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(caminhoArquivo), "ISO-8859-1"))) {
            String linha;
            boolean primeiraLinha = true;
    
            while ((linha = br.readLine()) != null) {
                if (primeiraLinha) {
                    primeiraLinha = false;
                    continue;
                }
    
                String[] campos = linha.split(";");
    
                try {
                    int codigoCargo = Integer.parseInt(campos[17].trim().replace("\"", "")); // CD_CARGO
                    int codigoMunicipio = Integer.parseInt(campos[13].trim().replace("\"", "")); // CD_MUNICIPIO
                    int numeroVotavel = Integer.parseInt(campos[19].trim().replace("\"", "")); // NR_VOTAVEL
                    int quantidadeVotos = Integer.parseInt(campos[21].trim().replace("\"", "")); // QT_VOTOS
    
                    if (codigoCargo != 13 || codigoMunicipio != this.codigoCidade) {
                        continue;
                    }
    
                    if (numeroVotavel >= 95 && numeroVotavel <= 98) {
                        continue;
                    }
    
                    // Verifica se é voto nominal (candidato) ou de legenda (partido)
                    if (this.candidatos.containsKey(numeroVotavel)) {
                        Candidato candidato = this.candidatos.get(numeroVotavel);
                        candidato.addVotos(quantidadeVotos);

                    } else if (this.partidos.containsKey(numeroVotavel)) {
                        Partido partido = this.partidos.get(numeroVotavel);
                        partido.addVotosLegenda(quantidadeVotos);

                    }
    
                } catch (NumberFormatException e) {
                    System.err.println("Erro ao converter número na linha ignorada: " + e.getMessage());
                    continue;
                }
            }
    
        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo de votação: " + e.getMessage());
        }
    }

    private void geraRelatorioVereadoresEleitos() {
        NumberFormat brFormat = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        ArrayList<Candidato> candidatosEleitos = new ArrayList<Candidato>();

        for(Candidato candidato : this.candidatos.values()) {
            if(candidato.isEleito()) candidatosEleitos.add(candidato);
        }

        candidatosEleitos.sort(Comparator.comparingInt(Candidato::getVotos).reversed());

        int i = 0;
        System.out.println("Vereadores eleitos:");
        for(Candidato candidatoEleito : candidatosEleitos) {
            i++;
            System.out.println(String.format("%d - %s (%s, %s votos)", i, candidatoEleito.getNomeUrna(), candidatoEleito.getPartido().getSigla(), brFormat.format(candidatoEleito.getVotos())));
        }
    }

    private void geraRelatoriosSobreMaisVotados() {
        NumberFormat brFormat = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        List<Candidato> candidatosMaisVotados = new ArrayList<>(candidatos.values());
    
        //Ordena o array de candidatos
        candidatosMaisVotados.sort(Comparator.comparingInt(Candidato::getVotos).reversed());
    
        List<Candidato> candidatosSeriamEleitos = new ArrayList<>();
        List<Candidato> candidatosEleitosPorProporcionalidade = new ArrayList<>();
    
        int i = 0;
        System.out.println("\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):");
        for (Candidato candidato : candidatosMaisVotados) {
            i++;
            if(i <= this.numEleitos) System.out.println(String.format("%d - %s (%s, %s votos)", i, candidato.getNomeUrna(), candidato.getPartido().getSigla(), brFormat.format(candidato.getVotos())));
    
            // Se o candidato não foi eleito e está entre os mais votados, ele teria sido eleito se fosse majoritário
            if (!candidato.isEleito() && i <= this.numEleitos) {
                candidatosSeriamEleitos.add(candidato);
            }
    
            // Se o candidato foi eleito, mas está mais abaixo no ranking de votos, ele se beneficiou do sistema proporcional
            if (candidato.isEleito() && i > this.numEleitos) {
                candidatosEleitosPorProporcionalidade.add(candidato);
            }
        }
    
        System.out.println("\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:");
        for (Candidato candidatoNaoEleito : candidatosSeriamEleitos) {
            System.out.println(String.format("%d - %s (%s, %s votos)", candidatosMaisVotados.indexOf(candidatoNaoEleito) + 1, candidatoNaoEleito.getNomeUrna(), candidatoNaoEleito.getPartido().getSigla(), brFormat.format(candidatoNaoEleito.getVotos())));
        }
    
        System.out.println("\nEleitos, que se beneficiaram do sistema proporcional:");
        for (Candidato candidatoBeneficiado : candidatosEleitosPorProporcionalidade) {
            System.out.println(String.format("%d - %s (%s, %s votos)", candidatosMaisVotados.indexOf(candidatoBeneficiado) + 1, candidatoBeneficiado.getNomeUrna(), candidatoBeneficiado.getPartido().getSigla(), brFormat.format(candidatoBeneficiado.getVotos())));
        }
    }    
    
    public void gerarRelatorios() {

        System.out.println("Número de vagas: " + this.numEleitos + "\n"); //Relatório 1
        this.geraRelatorioVereadoresEleitos(); //Relatório 2
        this.geraRelatoriosSobreMaisVotados(); //Relatórios 3, 4 e 5

    }

    @Override
    public String toString() {
        return "Eleição:\n" + "Código do município: " + this.codigoCidade + "\nData: " + this.data + "\n"; 
    }

    public void imprimirPartidos() {
        System.out.println("Lista de Partidos na Eleição:");
        for (Partido partido : partidos.values()) {
            System.out.println(partido);
        }
    }

    public void imprimirCandidatos() {
        System.out.println("Lista de Candidatos na Eleição:");
        for (Candidato candidato : candidatos.values()) {
            System.out.println(candidato);
        }
    }
}
