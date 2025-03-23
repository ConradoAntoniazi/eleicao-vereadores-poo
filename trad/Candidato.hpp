#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include "Genero.hpp"
#include "SituacaoEleitoral.hpp"
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
    string dataNascimento;
    Genero genero;
    SituacaoEleitoral situacaoEleitoral;

    static bool validarData(const string& data);

public:
    Candidato(const int& numero, const string& nomeUrna, Partido &partido, 
              const string& dataNasc, const int& genero, const int& situacao);
    
    // Getters
    int getNumero() const;
    string getNomeUrna(int flagFederado) const;
    Partido &getPartido() const;
    int getVotos() const;
    Genero getGenero() const;
    string getDataNascimento() const;
    bool isEleito() const;
    int getIdade(const string& dataEleicaoStr) const;
    
    void addVotos(int votos);
};

#endif