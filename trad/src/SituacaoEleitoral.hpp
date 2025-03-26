#ifndef SITUACAO_ELEITORAL_HPP
#define SITUACAO_ELEITORAL_HPP

#include <stdexcept>
#include <vector>

/**
 * Classe que representa as diferentes situações eleitorais de um candidato.
 * Utiliza um enum interno para definir os possíveis estados.
 */
class SituacaoEleitoral {
public:
    /**
     * Enum que define os tipos de situação eleitoral.
     */
    enum Tipo {
        CANDIDATURA_INVALIDA = -1,
        ELEITO = 1,
        ELEITO_POR_QUOCIENTE_PARTIDARIO,
        ELEITO_POR_MEDIA,
        NAO_ELEITO,
        SUPLENTE
    };

    /**
     * Construtor da classe SituacaoEleitoral.
     * @param tipo Tipo de situação eleitoral.
     */
    SituacaoEleitoral(Tipo tipo);

    /**
     * Retorna o código numérico associado à situação eleitoral.
     * @return Código da situação eleitoral.
     */
    int getCodigo() const;

    /**
     * Retorna a situação eleitoral correspondente ao código fornecido.
     * Lança uma exceção se o código não for válido.
     * @param codigo Código numérico da situação eleitoral.
     * @return Instância de SituacaoEleitoral correspondente ao código.
     * @throws std::invalid_argument Se o código não for válido.
     */
    static SituacaoEleitoral fromCodigo(int codigo);

private:
    Tipo tipo; ///< Tipo atual da situação eleitoral.

    /**
     * Estrutura auxiliar que associa um tipo de situação ao seu código.
     */
    struct ValorSituacao {
        Tipo tipo;
        int codigo;
    };

    /**
     * Lista de todas as combinações válidas de tipo e código.
     */
    static const std::vector<ValorSituacao> valores;
};

#endif
