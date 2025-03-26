#include "Partido.hpp"
#include "Candidato.hpp"
#include <iterator>
#include <algorithm>

using namespace std;

Partido::Partido(const int& numero, const string& sigla, const string& nome, const int& numeroFed)
    : numero(numero), sigla(sigla), nome(nome), numeroFederacao(numeroFed), votosLegenda(0) {}

// Getters
int Partido::getNumero() const { return numero; }

string Partido::getSigla() const { return sigla; }

string Partido::getNome() const { return nome; }

int Partido::getNumeroFederacao() const { return numeroFederacao; }

int Partido::getVotosLegenda() const { return votosLegenda; }

std::vector<std::shared_ptr<Candidato>> Partido::getCandidatos() const {
    std::vector<std::shared_ptr<Candidato>> result;
    for (auto& wk : candidatos) {
        // weak_ptr precisa ser convertido para shared_ptr para acessar o objeto
        // Se o objeto original já tiver sido destruído, lock() retorna nullptr
        if(auto sp = wk.lock()) {
            result.push_back(sp);
        }
    }
    return result;
}
//

void Partido::addVotosLegenda(int votos) { votosLegenda += votos; }

void Partido::addCandidato(std::shared_ptr<Candidato> candidato) {
    // Armazena apenas uma referência fraca ao candidato para evitar gerenciamento de ciclo de vida aqui
    // Isso impede que Partido mantenha o Candidato vivo "à força"
    candidatos.push_back(candidato);
}

int Partido::getVotosNominais() const {
    int total = 0;
    for (auto& wk : candidatos) {
        // lock() falha silenciosamente se o Candidato não existir mais
        if(auto sp = wk.lock()) {
            total += sp->getVotos();
        }
    }
    return total;
}

int Partido::getTotalVotos() const { 
    return votosLegenda + getVotosNominais(); 
}

int Partido::getNumEleitos() const {
    return std::count_if(candidatos.begin(), candidatos.end(),
        [](const std::weak_ptr<Candidato>& wp) {
            if(auto sp = wp.lock()) {
                return sp->isEleito();
            }
            return false;
        });
}

std::vector<std::shared_ptr<Candidato>> Partido::getCandidatosValidos() const {
    std::vector<std::shared_ptr<Candidato>> validos;
    for (auto& wk : candidatos) {
        if(auto sp = wk.lock()) {
            if(sp->getVotos() > 0)
                validos.push_back(sp);
        }
    }
    return validos;
}

std::shared_ptr<Candidato> Partido::getCandidatoMaisVotado() const {
    auto validos = getCandidatosValidos();
    if (validos.empty())
        return nullptr;
    std::sort(validos.begin(), validos.end(), [](std::shared_ptr<Candidato> a, std::shared_ptr<Candidato> b) {
        if (a->getVotos() != b->getVotos())
            return a->getVotos() > b->getVotos();
        return a->getDataNascimento() < b->getDataNascimento();
    });
    return validos.front();
}
