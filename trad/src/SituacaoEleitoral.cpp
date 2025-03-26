#include "SituacaoEleitoral.hpp"
#include <algorithm>


const std::vector<SituacaoEleitoral::ValorSituacao> SituacaoEleitoral::valores = {
    {CANDIDATURA_INVALIDA, -1},
    {ELEITO, 1},
    {ELEITO_POR_QUOCIENTE_PARTIDARIO, 2},
    {ELEITO_POR_MEDIA, 3},
    {NAO_ELEITO, 4},
    {SUPLENTE, 5}
};

SituacaoEleitoral::SituacaoEleitoral(Tipo tipo) : tipo(tipo) {}

int SituacaoEleitoral::getCodigo() const {
    auto it = find_if(valores.begin(), valores.end(), 
        [this](const ValorSituacao& vs) { return vs.tipo == this->tipo; });
    return it->codigo;
}

SituacaoEleitoral SituacaoEleitoral::fromCodigo(int codigo) {
    auto it = find_if(valores.begin(), valores.end(), 
        [codigo](const ValorSituacao& vs) { return vs.codigo == codigo; });
    
    if (it == valores.end()) {
        throw std::invalid_argument("Código de situação eleitoral inválido: " + std::to_string(codigo));
    }
    
    return SituacaoEleitoral(it->tipo);
}