#ifndef GENERO_HPP
#define GENERO_HPP

#include <vector>

using namespace std;

class Genero {
public:
    enum Tipo {
        MASCULINO,
        FEMININO,
        NAO_INFORMADO
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

    static const vector<ValorGenero> valores;
};

#endif