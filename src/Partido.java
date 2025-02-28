import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;

public class Partido {
    private final int numero;
    private final String sigla;
    private final String nome;
    private final int numeroFederacao;
    private int votosLegenda = 0;
    private LinkedList<Candidato> candidatos = new LinkedList<>();

    public Partido(int numero, String sigla, String nome, int numeroFed) {
        this.numero = numero;
        this.sigla = sigla;
        this.nome = nome;
        this.numeroFederacao = numeroFed;
    }

    public int getNumero() {
        return numero;
    }

    public String getSigla() {
        return sigla;
    }

    public String getNome() {
        return this.nome;
    }

    public int getNumeroFederacao() {
        return this.numeroFederacao;
    }

    public int getVotosLegenda() {
        return votosLegenda;
    }

    public void addVotosLegenda(int votos) {
        this.votosLegenda += votos;
    }

    public LinkedList<Candidato> getCandidatos() {
        return candidatos;
    }

    public void addCandidato(Candidato candidato) {
        this.candidatos.add(candidato);
    }

    public int getVotosNominais() {
        return this.candidatos.stream().mapToInt(Candidato::getVotos).sum();
    }

    public int getTotalVotos() {
        return this.votosLegenda + this.getVotosNominais();
    }

    public int getNumEleitos() {
        return (int) this.candidatos.stream().filter(Candidato::isEleito).count();
    }

    public List<Candidato> getCandidatosValidos() {
        return this.candidatos.stream()
                .filter(c -> c.getVotos() > 0)
                .collect(Collectors.toList());
    }

    public Candidato getCandidatoMaisVotado() {
        List<Candidato> validos = getCandidatosValidos();
        if (validos.isEmpty())
            return null;

        validos.sort(Comparator
                .comparingInt(Candidato::getVotos).reversed()
                .thenComparing(Candidato::getDataNascimento)
        );

        return validos.get(0);
    }

    @Override
    public String toString() {
        return "NOME: " + this.nome + " (" + this.sigla + ") " + this.numero + " VOTOS: " + this.votosLegenda;
    }
}
