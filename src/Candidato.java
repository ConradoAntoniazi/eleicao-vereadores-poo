import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class Candidato {
    private int votos;
    private int numero;
    private String nomeUrna;
    private Partido partido;
    private LocalDate dataNascimento;
    private Genero genero;
    private SituacaoEleitoral situacaoEleitoral;

    /**
     * Construtor de candidato.
     * @param numero Número do candidato na eleição.
     * @param nome Nome do candidato na urna.
     * @param partido Partido do candidato.
     * @param dataNasc Data de nascimento do candidato (formato: dd/MM/yyyy).
     * @param genero Código do gênero do candidato.
     * @param situacao Código da situação eleitoral do candidato.
     * @throws IllegalArgumentException Se o partido for nulo ou se a data de nascimento for inválida.
     */
    public Candidato(int numero, String nome, Partido partido, String dataNasc, int genero, int situacao) {
        if (partido == null) throw new IllegalArgumentException("Partido não pode ser nulo");

        this.numero = numero;
        this.nomeUrna = nome;
        this.partido = partido;

        // Valida a data de nascimento
        try {
            this.dataNascimento = LocalDate.parse(dataNasc, DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Data de nascimento inválida: " + dataNasc);
        }

        this.genero = Genero.fromCodigo(genero);
        this.situacaoEleitoral = SituacaoEleitoral.fromCodigo(situacao);
    }

    /**
     * Retorna o número do candidato.
     * @return Número do candidato.
     */
    public int getNumero() {
        return this.numero;
    }

    /**
     * Retorna o nome do candidato na urna. Se o partido for federado, adiciona um asterisco ao nome.
     * @param flagFederado Indica se o partido é federado ou não.
     * @return Nome do candidato.
     */
    public String getNomeUrna(int flagFederado) {
        // Se o partido for federado e flagFederado for 1, retorna nome com asterisco
        if (this.partido.getNumeroFederacao() != -1 && flagFederado != 0)
            return "*" + this.nomeUrna;
        return nomeUrna;
    }

    /**
     * Retorna o partido do candidato.
     * @return Partido do candidato.
     */
    public Partido getPartido() {
        return this.partido;
    }

    /**
     * Retorna o número de votos do candidato.
     * @return Número de votos do candidato.
     */
    public int getVotos() {
        return this.votos;
    }

    /**
     * Adiciona votos ao candidato. Não permite votos negativos.
     * @param votos Quantidade de votos a ser adicionada.
     * @throws IllegalArgumentException Se a quantidade de votos for negativa.
     */
    public void addVotos(int votos) {
        if (votos < 0) throw new IllegalArgumentException("Votos não podem ser negativos");
        this.votos += votos;
    }

    /**
     * Retorna o gênero do candidato.
     * @return Gênero do candidato.
     */
    public Genero getGenero() {
        return this.genero;
    }

    /**
     * Retorna a data de nascimento do candidato.
     * @return Data de nascimento do candidato.
     */
    public LocalDate getDataNascimento() {
        return this.dataNascimento;
    }

    /**
     * Verifica se o candidato foi eleito.
     * @return Verdadeiro se o candidato for eleito, caso contrário falso.
     */
    public boolean isEleito() {
        return this.situacaoEleitoral == SituacaoEleitoral.ELEITO ||
               this.situacaoEleitoral == SituacaoEleitoral.ELEITO_POR_QUOCIENTE_PARTIDARIO ||
               this.situacaoEleitoral == SituacaoEleitoral.ELEITO_POR_MEDIA;
    }

    /**
     * Calcula a idade do candidato na data da eleição.
     * @param dataEleicaoStr Data da eleição (formato: dd/MM/yyyy).
     * @return Idade do candidato na data da eleição.
     * @throws IllegalArgumentException Se a data da eleição for inválida.
     */
    public int getIdade(String dataEleicaoStr) {
        LocalDate dataEleicao;
        try {
            dataEleicao = LocalDate.parse(dataEleicaoStr, DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Data de eleição inválida: " + dataEleicaoStr);
        }

        return Period.between(this.dataNascimento, dataEleicao).getYears();
    }
}
