#include "Partido.hpp"

Partido::Partido(int numero, const string& sigla, const string& nome, int numeroFed)
    : numero(numero), sigla(sigla), nome(nome), numeroFederacao(numeroFed), votosLegenda(0) {}

// Getters
int Partido::getNumero() const { return numero; }
string Partido::getSigla() const { return sigla; }
string Partido::getNome() const { return nome; }
int Partido::getNumeroFederacao() const { return numeroFederacao; }
int Partido::getVotosLegenda() const { return votosLegenda; }
const vector<Candidato*>& Partido::getCandidatos() const { return candidatos; }

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

vector<Candidato*> Partido::getCandidatosValidos() const {
    vector<Candidato*> validos;
    copy_if(candidatos.begin(), candidatos.end(), back_inserter(validos),
        [](Candidato* c) { return c->getVotos() > 0; });
    return validos;
}

Candidato* Partido::getCandidatoMaisVotado() const {
    auto validos = getCandidatosValidos();
    if (validos.empty()) return nullptr;
    
    sort(validos.begin(), validos.end(),
        [](Candidato* a, Candidato* b) {
            return a->getVotos() > b->getVotos() || 
                  (a->getVotos() == b->getVotos() && a->getDataNascimento() < b->getDataNascimento());
        });
    
    return validos.front();
}