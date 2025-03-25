#ifndef GENERO_HPP
#define GENERO_HPP

#include <vector>

class Genero {
public:
    enum Tipo {
        MASCULINO = 2,
        FEMININO = 4,
        NAO_INFORMADO = 0
    };

    Genero(Tipo tipo);
    
    int getCodigo() const;
    static Genero fromCodigo(int codigo);

private:
    Tipo tipo;
    
    struct ValorGenero {
        Tipo tipo;
        int codigo;
    };

    static const std::vector<ValorGenero> valores;
};

#endif