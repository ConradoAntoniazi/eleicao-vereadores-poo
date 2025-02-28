import java.io.File;

public class App {
    public static void main(String[] args) {
        try {
            // Verifica se o número correto de argumentos foi passado
            validarArgumentos(args);

            // Atribui os valores dos argumentos a variáveis explicativas
            String numeroCidade = args[0];
            String candidatosFilePath = args[1];
            String votacaoFilePath = args[2];
            String dataEleicao = args[3];

            // Cria a instância da eleição com os dados fornecidos
            Eleicao eleicao = new Eleicao(Integer.parseInt(numeroCidade), dataEleicao);

            // Processa os dados de candidatos e votos
            eleicao.processarCandidatosPartidos(candidatosFilePath);
            eleicao.processarVotos(votacaoFilePath);

            // Gera os relatórios com base nos dados processados
            eleicao.gerarRelatorios();

        } catch (IllegalArgumentException e) {
            System.out.println("Erro: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Erro inesperado: " + e.getMessage());
            e.printStackTrace();
        }
    }

    // Valida a quantidade e o formato dos argumentos passados para o programa
    private static void validarArgumentos(String[] args) {
        if (args.length != 4) {
            throw new IllegalArgumentException("Número de argumentos inválido! São esperados 4 argumentos:\n" +
                    "1. Número da cidade\n" +
                    "2. Caminho para o arquivo de candidatos\n" +
                    "3. Caminho para o arquivo de votação\n" +
                    "4. Nome da eleição");
        }

        // Valida que os arquivos de candidatos e votação existem
        validarArquivo(args[1], "Arquivo de candidatos");
        validarArquivo(args[2], "Arquivo de votação");
    }

    // Valida se o arquivo existe no caminho fornecido
    private static void validarArquivo(String caminhoArquivo, String tipoArquivo) {
        File arquivo = new File(caminhoArquivo);
        if (!arquivo.exists() || !arquivo.isFile()) {
            throw new IllegalArgumentException(tipoArquivo + " não encontrado ou não é um arquivo válido: " + caminhoArquivo);
        }
    }
}
