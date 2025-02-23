import java.util.LinkedList;

public class Partido {
    private int numero;
    private String sigla;
    private String nome;
    private int numeroFederacao;
    private int votosLegenda;
    private LinkedList<Candidato> candidatos;

    public Partido(int numero, String sigla, String nome, int numeroFed) {
        this.numero = numero;
        this.sigla = sigla;
        this.nome = nome;
        this.numeroFederacao = numeroFed;
        this.candidatos = new LinkedList<>();
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
    
    public Candidato getCandidato(int numCandidato) {
        return this.candidatos.get(numCandidato);
    }

    public void addCandidato(Candidato candidato) {
        this.candidatos.add(candidato);
    }

    @Override
    public String toString() {
        return "NOME: " + this.nome + " (" + this.sigla + ") " + this.numero + " VOTOS: " + this.votosLegenda; 
    }
}
