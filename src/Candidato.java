import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class Candidato {
    private final int numero;
    private final String nomeUrna;
    private final Partido partido;
    private int votos = 0;
    private final LocalDate dataNascimento;
    private final Genero genero;
    private final SituacaoEleitoral situacaoEleitoral;

    public Candidato(int numero, String nome, Partido partido, String dataNasc, int genero, int situacao) {
        if (partido == null) throw new IllegalArgumentException("Partido não pode ser nulo");
        
        this.numero = numero;
        this.nomeUrna = nome;
        this.partido = partido;
        
        try {
            this.dataNascimento = LocalDate.parse(dataNasc, DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Data de nascimento inválida: " + dataNasc);
        }
        
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
        if (votos < 0) throw new IllegalArgumentException("Votos não podem ser negativos");
        this.votos += votos;
    }

    public Genero getGenero() {
        return this.genero;
    }

    public LocalDate getDataNascimento() {
        return this.dataNascimento;
    }

    public boolean isEleito() {
        return this.situacaoEleitoral == SituacaoEleitoral.ELEITO ||
                this.situacaoEleitoral == SituacaoEleitoral.ELEITO_POR_QUOCIENTE_PARTIDARIO ||
                this.situacaoEleitoral == SituacaoEleitoral.ELEITO_POR_MEDIA;
    }

    public int getIdade(String dataEleicaoStr) {
        LocalDate dataEleicao;
        try {
           dataEleicao = LocalDate.parse(dataEleicaoStr, DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Data de nascimento inválida: " + dataEleicaoStr);
        }
        
        return Period.between(this.dataNascimento, dataEleicao).getYears();
    }

    @Override
    public String toString() {
        return "NOME: " + this.nomeUrna + " (" + this.numero + ") " + "VOTOS: " + this.votos;
    }
}
