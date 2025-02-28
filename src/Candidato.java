import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;

public class Candidato {
    private int numero;
    private String nomeUrna;
    private Partido partido;
    private int votos;
    private String dataNascimento;
    private Genero genero;
    private SituacaoEleitoral situacaoEleitoral;

    public Candidato(int numero, String nome, Partido partido, String dataNasc, int genero, int situacao) {
        this.numero = numero;
        this.nomeUrna = nome;
        this.partido = partido;
        this.dataNascimento = dataNasc;
        this.genero = Genero.fromCodigo(genero);
        this.situacaoEleitoral = SituacaoEleitoral.fromCodigo(situacao);
    }

    public int getNumero() {
        return this.numero;
    }

    public String getNomeUrna() {
        if (this.partido.getNumeroFederacao() == -1)
            return nomeUrna;
        return "*" + this.nomeUrna;
    }

    public Partido getPartido() {
        return this.partido;
    }

    public int getVotos() {
        return this.votos;
    }

    public void addVotos(int votos) {
        this.votos += votos;
    }

    public Genero getGenero() {
        return this.genero;
    }

    public String getDataNascimento() {
        return this.dataNascimento;
    }

    public boolean isEleito() {
        return this.situacaoEleitoral == SituacaoEleitoral.ELEITO ||
                this.situacaoEleitoral == SituacaoEleitoral.ELEITO_POR_QUOCIENTE_PARTIDARIO ||
                this.situacaoEleitoral == SituacaoEleitoral.ELEITO_POR_MEDIA;
    }

    public int getIdade(String dataEleicaoStr) {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        LocalDate dataNasc = LocalDate.parse(this.dataNascimento, formatter);
        LocalDate dataEleicao = LocalDate.parse(dataEleicaoStr, formatter);
        return Period.between(dataNasc, dataEleicao).getYears();
    }

    @Override
    public String toString() {
        return "NOME: " + this.nomeUrna + " (" + this.numero + ") " + "VOTOS: " + this.votos;
    }
}
