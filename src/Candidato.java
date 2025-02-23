import java.time.LocalDate;

public class Candidato {
    private int numero;
    private String nomeUrna;
    private Partido partido;
    private boolean eleito;
    private int votos;
    private LocalDate dataNascimento;
    
    public Candidato (int numero, String nome, Partido partido, LocalDate dataNasc) {
        this.numero = numero;
        this.nomeUrna = nome;
        this.partido = partido;
        this.dataNascimento = dataNasc;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public String getNomeUrna() {
        return nomeUrna;
    }

    public void setNomeUrna(String nomeUrna) {
        this.nomeUrna = nomeUrna;
    }

    public Partido getPartido() {
        return partido;
    }

    public void setPartido(Partido partido) {
        this.partido = partido;
    }

    public boolean isEleito() {
        return eleito;
    }

    public void setEleito(boolean eleito) {
        this.eleito = eleito;
    }

    public int getVotos() {
        return votos;
    }

    public void setVotos(int votos) {
        this.votos = votos;
    }

    public LocalDate getDataNascimento() {
        return dataNascimento;
    }

    public void setDataNascimento(LocalDate dataNascimento) {
        this.dataNascimento = dataNascimento;
    }

}
