#ifndef GENERO_HPP
#define GENERO_HPP

#include <vector>

/**
 * Classe que representa os gêneros possíveis de um candidato.
 * Utiliza um enum interno para mapear os tipos e seus respectivos códigos.
 */
class Genero {
public:
    /**
     * Enum que define os tipos de gênero.
     */
    enum Tipo {
        MASCULINO = 2, ///< Gênero masculino.
        FEMININO = 4, ///< Gênero feminino.
        NAO_INFORMADO = 0 ///< Gênero não informado ou código inesperado.
    };

    /**
     * Construtor da classe Genero.
     * @param tipo Tipo de gênero.
     */
    Genero(Tipo tipo);

    /**
     * Retorna o código numérico associado ao gênero.
     * @return Código do gênero.
     */
    int getCodigo() const;

    /**
     * Obtém o gênero correspondente ao código fornecido.
     * Se o código não corresponder a nenhum gênero válido,
     * retorna NAO_INFORMADO.
     * @param codigo Código numérico do gênero.
     * @return Instância de Genero correspondente ao código.
     */
    static Genero fromCodigo(int codigo);

private:
    Tipo tipo; ///< Tipo de gênero atual.

    /**
     * Estrutura auxiliar que associa um tipo de gênero ao seu código.
     */
    struct ValorGenero {
        Tipo tipo;
        int codigo;
    };

    /**
     * Lista de todos os gêneros válidos e seus respectivos códigos.
     */
    static const std::vector<ValorGenero> valores;
};

#endif
