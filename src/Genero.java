public enum Genero {
    MASCULINO(2),
    FEMININO(4),
    NAO_INFORMADO(0); // Caso venha um código inesperado

    private final int codigo;

    Genero(int codigo) {
        this.codigo = codigo;
    }

    public int getCodigo() {
        return codigo;
    }

    public static Genero fromCodigo(int codigo) {
        for (Genero genero : Genero.values()) {
            if (genero.getCodigo() == codigo) {
                return genero;
            }
        }
        return NAO_INFORMADO;
    }
}
