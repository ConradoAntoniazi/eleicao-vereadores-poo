import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;

public class Partido {
    private int numero;
    private String sigla;
    private String nome;
    private int numeroFederacao;
    private int votosLegenda;
    private LinkedList<Candidato> candidatos = new LinkedList<>();

    /**
     * Construtor de partido.
     * @param numero Número do partido.
     * @param sigla Sigla do partido.
     * @param nome Nome do partido.
     * @param numeroFed Número da federação associada ao partido.
     */
    public Partido(int numero, String sigla, String nome, int numeroFed) {
        this.numero = numero;
        this.sigla = sigla;
        this.nome = nome;
        this.numeroFederacao = numeroFed;
    }

    /**
     * Retorna o número do partido.
     * @return O número do partido.
     */
    public int getNumero() {
        return numero;
    }

    /**
     * Retorna a sigla do partido.
     * @return A sigla do partido.
     */
    public String getSigla() {
        return sigla;
    }

    /**
     * Retorna o nome do partido.
     * @return O nome do partido.
     */
    public String getNome() {
        return this.nome;
    }

    /**
     * Retorna o número da federação do partido.
     * @return O número da federação do partido.
     */
    public int getNumeroFederacao() {
        return this.numeroFederacao;
    }

    /**
     * Retorna os votos de legenda do partido.
     * @return Os votos de legenda do partido.
     */
    public int getVotosLegenda() {
        return votosLegenda;
    }

    /**
     * Adiciona votos à legenda do partido.
     * @param votos Número de votos a ser adicionado à legenda.
     */
    public void addVotosLegenda(int votos) {
        this.votosLegenda += votos;
    }

    /**
     * Retorna os candidatos do partido.
     * @return Os candidatos do partido.
     */
    public LinkedList<Candidato> getCandidatos() {
        return candidatos;
    }

    /**
     * Adiciona um candidato ao partido.
     * @param candidato O candidato a ser adicionado.
     */
    public void addCandidato(Candidato candidato) {
        this.candidatos.add(candidato);
    }

    /**
     * Retorna o total de votos nominais dos candidatos do partido.
     * @return O total de votos nominais.
     */
    public int getVotosNominais() {
        return this.candidatos.stream().mapToInt(Candidato::getVotos).sum();
    }

    /**
     * Retorna o total de votos do partido, incluindo votos de legenda e votos nominais.
     * @return O total de votos do partido.
     */
    public int getTotalVotos() {
        return this.votosLegenda + this.getVotosNominais();
    }

    /**
     * Retorna o número de candidatos eleitos do partido.
     * @return O número de candidatos eleitos.
     */
    public int getNumEleitos() {
        return (int) this.candidatos.stream().filter(Candidato::isEleito).count();
    }

    /**
     * Retorna a lista de candidatos válidos (com mais de 0 votos).
     * @return A lista de candidatos válidos.
     */
    public List<Candidato> getCandidatosValidos() {
        return this.candidatos.stream()
                .filter(c -> c.getVotos() > 0)
                .collect(Collectors.toList());
    }

    /**
     * Retorna o candidato mais votado do partido.
     * @return O candidato mais votado, ou null se não houver candidatos válidos.
     */
    public Candidato getCandidatoMaisVotado() {
        List<Candidato> validos = getCandidatosValidos();
        if (validos.isEmpty()) {
            return null;
        }

        validos.sort(Comparator
                .comparingInt(Candidato::getVotos).reversed()
                .thenComparing(Candidato::getDataNascimento)
        );

        return validos.get(0);
    }
}
