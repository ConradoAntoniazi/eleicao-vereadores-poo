// Enum que representa as diferentes situações eleitorais de um candidato.

public enum SituacaoEleitoral {
    CANDIDATURA_INVALIDA(-1),
    ELEITO(1),
    ELEITO_POR_QUOCIENTE_PARTIDARIO(2),
    ELEITO_POR_MEDIA(3),
    NAO_ELEITO(4),
    SUPLENTE(5);

    private int codigo;

    /**
     * Construtor do enum.
     * @param codigo Código numérico associado à situação eleitoral.
     */
    SituacaoEleitoral(int codigo) {
        this.codigo = codigo;
    }

    /**
     * Retorna o código associado à situação eleitoral.
     * @return Código da situação eleitoral.
     */
    public int getCodigo() {
        return codigo;
    }

    /**
     * Obtém a situação eleitoral correspondente ao código fornecido.
     * Se o código não corresponder a nenhuma situação válida, lança uma exceção.
     * @param codigo Código numérico da situação eleitoral.
     * @return A situação eleitoral correspondente ao código.
     * @throws IllegalArgumentException Se o código não for válido.
     */
    public static SituacaoEleitoral fromCodigo(int codigo) {
        for (SituacaoEleitoral situacao : SituacaoEleitoral.values()) {
            if (situacao.getCodigo() == codigo) {
                return situacao;
            }
        }
        throw new IllegalArgumentException("Código de situação eleitoral inválido: " + codigo);
    }
}
