#ifndef PARTIDO_HPP
#define PARTIDO_HPP

#include "Candidato.hpp"
#include <vector>
#include <algorithm>

using namespace std;

class Candidato; //forward reference

class Partido {
private:
    int numero;
    string sigla;
    string nome;
    int numeroFederacao;
    int votosLegenda;
    vector<Candidato*> candidatos; 
public:
    Partido(int numero, const string& sigla, const string& nome, int numeroFed);
    
    // Getters
    int getNumero() const;
    string getSigla() const;
    string getNome() const;
    int getNumeroFederacao() const;
    int getVotosLegenda() const;
    const vector<Candidato*>& getCandidatos() const;
    
    void addVotosLegenda(int votos);
    void addCandidato(Candidato* candidato); 
    int getVotosNominais() const;
    int getTotalVotos() const;
    int getNumEleitos() const;
    
    vector<Candidato*> getCandidatosValidos() const;
    Candidato* getCandidatoMaisVotado() const;
};

#endif