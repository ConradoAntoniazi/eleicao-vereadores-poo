#ifndef SITUACAO_ELEITORAL_HPP
#define SITUACAO_ELEITORAL_HPP

#include <stdexcept>
#include <vector>

using namespace std;

class SituacaoEleitoral {
public:
    enum Tipo {
        CANDIDATURA_INVALIDA,
        ELEITO,
        ELEITO_POR_QUOCIENTE_PARTIDARIO,
        ELEITO_POR_MEDIA,
        NAO_ELEITO,
        SUPLENTE
    };

    SituacaoEleitoral(Tipo tipo);
    
    int getCodigo() const;
    static SituacaoEleitoral fromCodigo(int codigo);

private:
    Tipo tipo;
    
    struct ValorSituacao {
        Tipo tipo;
        int codigo;
    };

    static const vector<ValorSituacao> valores;
};

#endif