#include "Partido.hpp"
#include "Candidato.hpp"
#include <iterator>
#include <algorithm>


Partido::Partido(const int& numero, const string& sigla, const string& nome, const int& numeroFed)
    : numero(numero), sigla(sigla), nome(nome), numeroFederacao(numeroFed), votosLegenda(0) {}

// Getters
int Partido::getNumero() const { return numero; }

string Partido::getSigla() const { return sigla; }

string Partido::getNome() const { return nome; }

int Partido::getNumeroFederacao() const { return numeroFederacao; }

int Partido::getVotosLegenda() const { return votosLegenda; }

const list<Candidato*>& Partido::getCandidatos() const { return candidatos; }


void Partido::addVotosLegenda(int votos) { votosLegenda += votos; }

void Partido::addCandidato(Candidato* candidato) { candidatos.push_back(candidato); }

int Partido::getVotosNominais() const {
    int total = 0;
    for (Candidato* c : candidatos) {
        total += c->getVotos();
    }
    return total;
}

int Partido::getTotalVotos() const { 
    return votosLegenda + getVotosNominais(); 
}

int Partido::getNumEleitos() const {
    return count_if(candidatos.begin(), candidatos.end(),
        [](Candidato* c) { return c->isEleito(); });
}

list<Candidato*> Partido::getCandidatosValidos() const {
    list<Candidato*> validos;
    copy_if(candidatos.begin(), candidatos.end(), back_inserter(validos),
        [](Candidato* c) { return c->getVotos() > 0; });
    return validos;
}

Candidato* Partido::getCandidatoMaisVotado() const {
    auto validos = getCandidatosValidos();
    if (validos.empty()) return nullptr;
    
    // list tem sort nativo
    validos.sort([](Candidato* a, Candidato* b) {
        if (a->getVotos() != b->getVotos()) {
            return a->getVotos() > b->getVotos(); // Decrescente
        } else {
            return a->getDataNascimento() < b->getDataNascimento(); // Crescente
        }
    });

    
    return validos.front();
}