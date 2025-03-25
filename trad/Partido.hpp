#ifndef PARTIDO_HPP
#define PARTIDO_HPP

#include <vector>
#include <list>
#include <string>
#include <memory>

class Candidato; //forward reference

class Partido {
private:
    int numero;
    std::string sigla;
    std::string nome;
    int numeroFederacao;
    int votosLegenda;
    // simetrico ao que ocorre em candidato, partido 
    // tambem evita a responsabilidade do ciclo de vida dos
    // ponteiros que guarda de candidato 
    std::list<std::weak_ptr<Candidato>> candidatos; 
public:
    Partido(const int& numero, const std::string& sigla, const std::string& nome, const int& numeroFed);
    
    // Getters
    int getNumero() const;
    std::string getSigla() const;
    std::string getNome() const;
    int getNumeroFederacao() const;
    int getVotosLegenda() const;
    std::vector<std::shared_ptr<Candidato>> getCandidatos() const;
    //
    
    void addVotosLegenda(int votos);
    void addCandidato(std::shared_ptr<Candidato> candidato); 
    int getVotosNominais() const;
    int getTotalVotos() const;
    int getNumEleitos() const;
    
    std::vector<std::shared_ptr<Candidato>> getCandidatosValidos() const;
    std::shared_ptr<Candidato> getCandidatoMaisVotado() const;
};

#endif