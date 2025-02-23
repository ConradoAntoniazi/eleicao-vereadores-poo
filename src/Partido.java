import java.util.LinkedList;

public class Partido {
    private int numero;
    private String sigla;
    private int votosLegenda;
    private LinkedList<Candidato> candidatos; //Talvez trocar por um hashMap

    public Partido(int numero, String sigla, int votosLegenda) {
        this.numero = numero;
        this.sigla = sigla;
        this.votosLegenda = votosLegenda;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public String getSigla() {
        return sigla;
    }

    public void setSigla(String sigla) {
        this.sigla = sigla;
    }

    public int getVotosLegenda() {
        return votosLegenda;
    }

    public void setVotosLegenda(int votosLegenda) {
        this.votosLegenda = votosLegenda;
    }

    public LinkedList<Candidato> getCandidatos() {
        return candidatos;
    }
    
    public void setCandidatos(LinkedList<Candidato> candidatos) {
        this.candidatos = candidatos;
    }
}
