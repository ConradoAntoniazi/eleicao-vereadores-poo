// Representa os gêneros possíveis de um candidato.

public enum Genero {
    MASCULINO(2),
    FEMININO(4),
    NAO_INFORMADO(0); // Caso venha um código inesperado

    private int codigo;

    /**
     * Construtor do enum.
     * @param codigo Código numérico associado ao gênero.
     */
    Genero(int codigo) {
        this.codigo = codigo;
    }

    /**
     * Retorna o código associado ao gênero.
     * @return Código do gênero.
     */
    public int getCodigo() {
        return codigo;
    }

    /**
     * Obtém o gênero correspondente ao código fornecido.
     * Se o código não corresponder a nenhum gênero válido, retorna NAO_INFORMADO.
     * @param codigo Código numérico do gênero.
     * @return O gênero correspondente ao código.
     */
    public static Genero fromCodigo(int codigo) {
        for (Genero genero : Genero.values()) {
            if (genero.getCodigo() == codigo) {
                return genero;
            }
        }
        return NAO_INFORMADO;
    }
}
