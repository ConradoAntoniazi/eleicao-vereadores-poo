#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include "Genero.hpp"
#include "SituacaoEleitoral.hpp"
#include "DataUtils.hpp"

#include <string>
#include <memory>

class Partido; //forward reference

class Candidato {
private:
    int votos;
    int numero;
    std::string nomeUrna;
    // weak ptr indica que essa classe
    // nao e' responsavel por gerenciar o ciclo de vida 
    // desse ponteiro
    std::weak_ptr<Partido> partido;  
    DataUtils dataNascimento;
    Genero genero;
    SituacaoEleitoral situacaoEleitoral;

public:
    Candidato(const int& numero, const std::string& nomeUrna, std::shared_ptr<Partido> partido, 
              const std::string& dataNasc, const int& genero, const int& situacao);
    
    // Getters
    int getNumero() const;
    std::string getNomeUrna(int flagFederado) const;
    std::shared_ptr<Partido> getPartido() const;
    int getVotos() const;
    Genero getGenero() const;
    DataUtils getDataNascimento() const;
    bool isEleito() const;
    int getIdade(const std::string& dataEleicaoStr) const;
    
    void addVotos(int votos);
};

#endif