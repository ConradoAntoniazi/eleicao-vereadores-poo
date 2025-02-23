public class Candidato {
    private int numero;
    private String nomeUrna;
    private Partido partido;
    private int votos;
    private String dataNascimento;
    private Genero genero;
    private SituacaoEleitoral situacaoEleitoral;
    
    public Candidato (int numero, String nome, Partido partido, String dataNasc, int genero, int situacao) {
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
        return this.nomeUrna;
    }

    public Partido getPartido() {
        return this.partido;
    }
    
    public int getVotos() {
        return this.votos;
    }
    
    public Genero getGenero(){
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

    @Override
    public String toString() {
        return "NOME: " + this.nomeUrna + " (" + this.numero + ") " + this.partido;
    }
}
