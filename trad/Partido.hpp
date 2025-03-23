#ifndef PARTIDO_HPP
#define PARTIDO_HPP

#include <vector>
#include <list>
#include <string>

using namespace std;

class Candidato; //forward reference

class Partido {
private:
    int numero;
    string sigla;
    string nome;
    int numeroFederacao;
    int votosLegenda;
    list<Candidato*> candidatos; 
public:
    Partido(const int& numero, const string& sigla, const string& nome, const int& numeroFed);
    
    // Getters
    int getNumero() const;
    string getSigla() const;
    string getNome() const;
    int getNumeroFederacao() const;
    int getVotosLegenda() const;
    const list<Candidato*>& getCandidatos() const;
    
    void addVotosLegenda(int votos);
    void addCandidato(Candidato* candidato); 
    int getVotosNominais() const;
    int getTotalVotos() const;
    int getNumEleitos() const;
    
    list<Candidato*> getCandidatosValidos() const;
    Candidato* getCandidatoMaisVotado() const;
};

#endif