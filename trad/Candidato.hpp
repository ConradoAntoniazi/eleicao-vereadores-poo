#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include "Genero.hpp"
#include "SituacaoEleitoral.hpp"
#include "DataUtils.hpp"

#include <string>
#include <stdexcept>

using namespace std;

class Partido; //forward reference

class Candidato {
private:
    int votos;
    int numero;
    string nomeUrna;
    Partido *partido;
    DataUtils dataNascimento;
    Genero genero;
    SituacaoEleitoral situacaoEleitoral;

public:
    Candidato(const int& numero, const string& nomeUrna, Partido &partido, 
              const string& dataNasc, const int& genero, const int& situacao);
    
    // Getters
    int getNumero() const;
    string getNomeUrna(int flagFederado) const;
    Partido &getPartido() const;
    int getVotos() const;
    Genero getGenero() const;
    DataUtils getDataNascimento() const;
    bool isEleito() const;
    int getIdade(const string& dataEleicaoStr) const;
    
    void addVotos(int votos);
};

#endif