import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

public class Eleicao {
    private int codigoCidade;
    private String data;
    private HashMap<Integer, Candidato> candidatos;
    private HashMap<String, Partido> partidos;
    
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
                    if (codigoCargo != 13 || codigoMunicipio != this.codigoCidade || situacaoTurno == -1) continue; //Se não for vereador, não for a cidade que estamos avaliando ou a candidatura for inválida, pula.

                } catch (NumberFormatException e) {
                    System.err.println("Erro ao converter número: " + e.getMessage());
                    return;
                }

                String siglaPartido = campos[26].trim().replace("\"", "");
                int numeroFederacao = Integer.parseInt(campos[28].trim().replace("\"", ""));

                if(!this.partidos.containsKey(siglaPartido)) { //partido não está presente no hashMap, então é criado.
                    this.partidos.put(siglaPartido, new Partido(Integer.parseInt(campos[25]), siglaPartido, campos[27].trim().replace("\"", ""), numeroFederacao));
                }

                int numero = Integer.parseInt(campos[16].trim().replace("\"", ""));
                String nomeUrna = campos[18].trim().replace("\"", "");
                String dataNascimento = campos[36].trim().replace("\"", "");
                int genero = Integer.parseInt(campos[38].trim().replace("\"", ""));
                int situacao = Integer.parseInt(campos[48].trim().replace("\"", ""));

                Partido partAux = this.partidos.get(siglaPartido);
                Candidato candAux = new Candidato(numero, nomeUrna, partAux, dataNascimento, genero, situacao);

                this.candidatos.put(numero, candAux);
                partAux.addCandidato(candAux);
            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }
    }

    public void processarVotos(String caminhoArquivo) {
        // Lógica para ler e processar o CSV de votação
    }

    public void gerarRelatorios() {
        // Geração dos relatórios exigidos
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
