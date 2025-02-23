public enum SituacaoEleitoral {
    CANDIDATURA_INVALIDA(-1),
    ELEITO(1),
    ELEITO_POR_QUOCIENTE_PARTIDARIO(2),
    ELEITO_POR_MEDIA(3),
    NAO_ELEITO(4),
    SUPLENTE(5);

    private final int codigo;

    SituacaoEleitoral(int codigo) {
        this.codigo = codigo;
    }

    public int getCodigo() {
        return codigo;
    }

    public static SituacaoEleitoral fromCodigo(int codigo) {
        for (SituacaoEleitoral situacao : SituacaoEleitoral.values()) {
            if (situacao.getCodigo() == codigo) {
                return situacao;
            }
        }
        throw new IllegalArgumentException("Código de situação eleitoral inválido: " + codigo);
    }
}
