public class App {
    public static void main(String[] args) throws Exception {
        if(args.length != 4) {
            System.out.println("Número de argumentos inválido!");
            return;
        }

        String pathCandidatos = args[1];
        String pathVotacao = args[2];
        Eleicao eleicao = new Eleicao(Integer.parseInt(args[0]), args[3]);

        eleicao.processarCandidatosPartidos("../in/" + pathCandidatos);

        eleicao.imprimirPartidos();
        System.out.println("");
        eleicao.imprimirCandidatos();
    }
}
