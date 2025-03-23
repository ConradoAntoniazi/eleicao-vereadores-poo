#include "Genero.hpp"
#include <algorithm>

const vector<Genero::ValorGenero> Genero::valores = {
    {MASCULINO, 2},
    {FEMININO, 4},
    {NAO_INFORMADO, 0}
};

Genero::Genero(Tipo tipo) : tipo(tipo) {}

int Genero::getCodigo() const {
    auto it = find_if(valores.begin(), valores.end(), 
        [this](const ValorGenero& vg) { return vg.tipo == this->tipo; });
    return it->codigo;
}

Genero Genero::fromCodigo(int codigo) {
    auto it = find_if(valores.begin(), valores.end(), 
        [codigo](const ValorGenero& vg) { return vg.codigo == codigo; });
    
    return (it != valores.end()) ? Genero(it->tipo) : Genero(NAO_INFORMADO);
}