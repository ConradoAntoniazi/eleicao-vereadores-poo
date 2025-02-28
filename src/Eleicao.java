import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.text.*;

public class Eleicao {
    private final int codigoCidade;
    private final String data;
    private int numEleitos = 0;
    private HashMap<Integer, Candidato> candidatos = new HashMap<>();;
    private HashMap<Integer, Partido> partidos = new HashMap<>();;
    private ArrayList<Candidato> candidatosEleitos = new ArrayList<>();

    public Eleicao(int codigo, String data) {
        this.codigoCidade = codigo;
        this.data = data;
    }

    public int getCodigo() {
        return this.codigoCidade;
    }

    public String getData() {
        return this.data;
    }

    public void processarCandidatosPartidos(String caminhoArquivo) {
        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(caminhoArquivo), "ISO-8859-1"))) {
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
                    if (codigoCargo != 13 || codigoMunicipio != this.codigoCidade || situacaoTurno == -1) { 
                        int numPartido = Integer.parseInt(campos[25].trim().replace("\"", "")); // Necessário fazer isso para ler TODOS os partidos, não so aqueles que possuem vereador em situação boa
                        int numeroFederacao = Integer.parseInt(campos[28].trim().replace("\"", ""));
                        if (!this.partidos.containsKey(numPartido)) { // partido não está presente no hashMap, então é criado.
                            this.partidos.put(numPartido, new Partido(Integer.parseInt(campos[25]),
                                    campos[26].trim().replace("\"", ""), campos[27].trim().replace("\"", ""), numeroFederacao));
                        }
                        continue; // Se não for vereador, não for a cidade que estamos avaliando ou a candidatura
                    }
                } catch (NumberFormatException e) {
                    System.err.println("Erro ao converter número: " + e.getMessage());
                    return;
                }

                int numPartido = Integer.parseInt(campos[25].trim().replace("\"", ""));
                int numeroFederacao = Integer.parseInt(campos[28].trim().replace("\"", ""));

                if (!this.partidos.containsKey(numPartido)) { // partido não está presente no hashMap, então é criado.
                    this.partidos.put(numPartido, new Partido(Integer.parseInt(campos[25]),
                            campos[26].trim().replace("\"", ""), campos[27].trim().replace("\"", ""), numeroFederacao));
                }

                int numero = Integer.parseInt(campos[16].trim().replace("\"", ""));
                String nomeUrna = campos[18].trim().replace("\"", "");
                String dataNascimento = campos[36].trim().replace("\"", "");
                int genero = Integer.parseInt(campos[38].trim().replace("\"", ""));
                int situacao = Integer.parseInt(campos[48].trim().replace("\"", ""));

                Partido partAux = this.partidos.get(numPartido);
                Candidato candAux = new Candidato(numero, nomeUrna, partAux, dataNascimento, genero, situacao);

                // Incrementa o número de eleitos da eleição
                if (candAux.isEleito()){
                    this.numEleitos++;
                    this.candidatosEleitos.add(candAux);
                }

                this.candidatos.put(numero, candAux);
                partAux.addCandidato(candAux);

            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }
    }

    public void processarVotos(String caminhoArquivo) {
        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(caminhoArquivo), "ISO-8859-1"))) {
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

        for (Candidato candidato : this.candidatos.values()) {
            if (candidato.isEleito())
                candidatosEleitos.add(candidato);
        }

        candidatosEleitos.sort(Comparator
                .comparingInt(Candidato::getVotos).reversed()
                .thenComparing(Candidato::getDataNascimento));

        int i = 0;
        System.out.println("Vereadores eleitos:");
        for (Candidato candidatoEleito : candidatosEleitos) {
            i++;
            System.out.println(String.format("%d - %s (%s, %s votos)", i, candidatoEleito.getNomeUrna(1),
                    candidatoEleito.getPartido().getSigla(), brFormat.format(candidatoEleito.getVotos())));
        }
    }

    private void geraRelatoriosSobreMaisVotados() {
        NumberFormat brFormat = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        List<Candidato> candidatosMaisVotados = new ArrayList<>(candidatos.values());

        // Ordena o array de candidatos
        candidatosMaisVotados.sort(Comparator
                .comparingInt(Candidato::getVotos).reversed()
                .thenComparing(Candidato::getDataNascimento));

        List<Candidato> candidatosSeriamEleitos = new ArrayList<>();
        List<Candidato> candidatosEleitosPorProporcionalidade = new ArrayList<>();

        int i = 0;
        System.out
                .println("\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):");
        for (Candidato candidato : candidatosMaisVotados) {
            i++;
            if (i <= this.numEleitos)
                System.out.println(String.format("%d - %s (%s, %s votos)", i, candidato.getNomeUrna(1),
                        candidato.getPartido().getSigla(), brFormat.format(candidato.getVotos())));

            // Se o candidato não foi eleito e está entre os mais votados, ele teria sido
            // eleito se fosse majoritário
            if (!candidato.isEleito() && i <= this.numEleitos) {
                candidatosSeriamEleitos.add(candidato);
            }

            // Se o candidato foi eleito, mas está mais abaixo no ranking de votos, ele se
            // beneficiou do sistema proporcional
            if (candidato.isEleito() && i > this.numEleitos) {
                candidatosEleitosPorProporcionalidade.add(candidato);
            }
        }

        System.out.println("\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n(com sua posição no ranking de mais votados)");
        for (Candidato candidatoNaoEleito : candidatosSeriamEleitos) {
            System.out.println(String.format("%d - %s (%s, %s votos)",
                    candidatosMaisVotados.indexOf(candidatoNaoEleito) + 1, candidatoNaoEleito.getNomeUrna(1),
                    candidatoNaoEleito.getPartido().getSigla(), brFormat.format(candidatoNaoEleito.getVotos())));
        }

        System.out.println("\nEleitos, que se beneficiaram do sistema proporcional:\n(com sua posição no ranking de mais votados)");
        for (Candidato candidatoBeneficiado : candidatosEleitosPorProporcionalidade) {
            System.out.println(String.format("%d - %s (%s, %s votos)",
                    candidatosMaisVotados.indexOf(candidatoBeneficiado) + 1, candidatoBeneficiado.getNomeUrna(1),
                    candidatoBeneficiado.getPartido().getSigla(), brFormat.format(candidatoBeneficiado.getVotos())));
        }
    }

    private void geraRelatorioVotacaoPartidos() {
        NumberFormat brFormat = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));

        List<Partido> partidosOrdenados = new ArrayList<>(this.partidos.values());

        partidosOrdenados.sort((p1, p2) -> {
            int comparacaoVotos = Integer.compare(p2.getTotalVotos(), p1.getTotalVotos());
            if (comparacaoVotos != 0)
                return comparacaoVotos;
            else
                return Integer.compare(p1.getNumero(), p2.getNumero());
        });

        // cabecalho
        System.out.println("\nVotação dos partidos e número de candidatos eleitos:");

        int posicao = 1;
        for (Partido partido : partidosOrdenados) {
            int votosNominais = partido.getVotosNominais();
            int votosLegenda = partido.getVotosLegenda();
            int totalVotos = partido.getTotalVotos();
            int numEleitos = partido.getNumEleitos();
           
            String votoStr = (totalVotos <= 1) ? "voto" : "votos";
			String votoNominalStr = (votosNominais <= 1) ? "nominal" : "nominais";
			String candidatoStr = (numEleitos <= 1) ? "candidato eleito" : "candidatos eleitos";

			if (totalVotos == 0) {
				System.out.printf("%d - %s - %d, 0 voto (0 %s e 0 de legenda), 0 candidato eleito\n",
					posicao++,
					partido.getSigla(),
					partido.getNumero(),
					votoNominalStr);
			} else {
				System.out.printf("%d - %s - %d, %s %s (%s %s e %s de legenda), %d %s\n",
					posicao++,
					partido.getSigla(),
					partido.getNumero(),
					brFormat.format(totalVotos),
					votoStr,
					brFormat.format(votosNominais),
					votoNominalStr,
					brFormat.format(votosLegenda),
					numEleitos,
					candidatoStr);
			}
        }
    }

    private void geraRelatorioPrimeiroUltimoPartido() {
        NumberFormat brFormat = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));

        // Filtrando partidos com candidatos validos
        List<Partido> partidosValidos = new ArrayList<>(this.partidos.values());
        partidosValidos.removeIf(p -> p.getCandidatosValidos().isEmpty());

        // Ordenando partidos pelo candidato mais votado (decrescente)
        // e número do partido (crescente)
        partidosValidos.sort((p1, p2) -> {
            Candidato c1 = p1.getCandidatoMaisVotado();
            Candidato c2 = p2.getCandidatoMaisVotado();

            int comparacaoVotos = Integer.compare(c2.getVotos(), c1.getVotos());
            if (comparacaoVotos != 0)
                return comparacaoVotos;
            else
                return Integer.compare(p1.getNumero(), p2.getNumero());
        });

        System.out.println("\nPrimeiro e último colocados de cada partido:");
        int posicao = 1;
        for (Partido partido : partidosValidos) {
            Comparator<Candidato> comparator = Comparator
                    .comparingInt(Candidato::getVotos).reversed()
                    .thenComparing(Candidato::getDataNascimento);

            List<Candidato> candidatosOrdenados = partido.getCandidatosValidos()
                    .stream()
                    .sorted(comparator)
                    .collect(Collectors.toList());

            Candidato primeiro = candidatosOrdenados.get(0);
            Candidato ultimo = candidatosOrdenados.get(candidatosOrdenados.size() - 1);

            System.out.printf("%d - %s - %d, %s (%d, %s votos) / %s (%d, %s votos)%n",
                    posicao++,
                    partido.getSigla(),
                    partido.getNumero(),
                    primeiro.getNomeUrna(0),
                    primeiro.getNumero(),
                    brFormat.format(primeiro.getVotos()),
                    ultimo.getNomeUrna(0),
                    ultimo.getNumero(),
                    brFormat.format(ultimo.getVotos()));
        }
    }

    private void geraRelatorioFaixaEtaria() {
        int[] faixas = new int[5]; // [<30, 30-39, 40-49, 50-59, >=60]

        for (Candidato candidato : this.candidatosEleitos) {
            int idade = candidato.getIdade(this.data);

            if (idade < 30)
                faixas[0]++;
            else if (idade < 40)
                faixas[1]++;
            else if (idade < 50)
                faixas[2]++;
            else if (idade < 60)
                faixas[3]++;
            else
                faixas[4]++;
        }

        int total = this.numEleitos;
        if (total == 0)
            return;

        NumberFormat percentFormat = NumberFormat.getPercentInstance(Locale.forLanguageTag("pt-BR"));
        percentFormat.setMinimumFractionDigits(2);

        System.out.println("\nEleitos, por faixa etária (na data da eleição):");
        System.out.printf("      Idade < 30: %d (%s)%n", faixas[0], percentFormat.format((double) faixas[0] / total));
        System.out.printf("30 <= Idade < 40: %d (%s)%n", faixas[1], percentFormat.format((double) faixas[1] / total));
        System.out.printf("40 <= Idade < 50: %d (%s)%n", faixas[2], percentFormat.format((double) faixas[2] / total));
        System.out.printf("50 <= Idade < 60: %d (%s)%n", faixas[3], percentFormat.format((double) faixas[3] / total));
        System.out.printf("60 <= Idade    : %d (%s)%n", faixas[4], percentFormat.format((double) faixas[4] / total));
    }

    private void geraRelatorioGenero() {
        int feminino = 0;
        int masculino = 0;

        for (Candidato candidato : this.candidatosEleitos) {
            Genero genero = candidato.getGenero();
            if (genero == Genero.FEMININO)
                feminino++;
            else if (genero == Genero.MASCULINO)
                masculino++;
        }

        int total = this.numEleitos;
        NumberFormat percentFormat = NumberFormat.getPercentInstance(Locale.forLanguageTag("pt-BR"));
        percentFormat.setMinimumFractionDigits(2);

        System.out.println("\nEleitos, por gênero:");
        System.out.printf("Feminino: %d (%s)%n", feminino,
                (total == 0) ? "0,00%" : percentFormat.format((double) feminino / total));
        System.out.printf("Masculino: %d (%s)%n", masculino,
                (total == 0) ? "0,00%" : percentFormat.format((double) masculino / total));
    }

    private void geraRelatorioTotalVotos() {
        // Somatorio dos nominais
        int votosNominais = this.candidatos.values().stream().mapToInt(Candidato::getVotos).sum();

        // Somatorio das legendas
        int votosLegenda = this.partidos.values().stream().mapToInt(Partido::getVotosLegenda).sum();

        int totalVotosValidos = votosNominais + votosLegenda;

        // Formatando numeros e porcentagens
        NumberFormat numFormat = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        NumberFormat percentFormat = NumberFormat.getPercentInstance(Locale.forLanguageTag("pt-BR"));
        percentFormat.setMinimumFractionDigits(2);

        double percentNominais = (totalVotosValidos == 0) ? 0.0 : (double) votosNominais / totalVotosValidos;
        double percentLegenda = (totalVotosValidos == 0) ? 0.0 : (double) votosLegenda / totalVotosValidos;

        System.out.println("\nTotal de votos válidos:    " + numFormat.format(totalVotosValidos));
        System.out.println("Total de votos nominais:    " + numFormat.format(votosNominais) +
                " (" + percentFormat.format(percentNominais) + ")");
        System.out.println("Total de votos de legenda: " + numFormat.format(votosLegenda) +
                " (" + percentFormat.format(percentLegenda) + ")");
    }

    public void gerarRelatorios() {

        System.out.println("Número de vagas: " + this.numEleitos + "\n"); // Relatório 1
        this.geraRelatorioVereadoresEleitos(); // Relatório 2
        this.geraRelatoriosSobreMaisVotados(); // Relatórios 3, 4 e 5
        this.geraRelatorioVotacaoPartidos(); // Relatório 6
        this.geraRelatorioPrimeiroUltimoPartido(); // Relatório 7
        this.geraRelatorioFaixaEtaria(); // Relatório 8
        this.geraRelatorioGenero(); // Relatório 9
        this.geraRelatorioTotalVotos(); // Relatório 10
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
