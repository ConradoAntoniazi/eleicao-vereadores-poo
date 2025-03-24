#ifndef ELEICAO_HPP
#define ELEICAO_HPP

#include <string>
#include <stdexcept>
#include <map>
#include <vector>

#include "DataUtils.hpp"
#include "Candidato.hpp"
#include "Partido.hpp"

class Eleicao {
private:
    const int codigoCidade;
    const DataUtils data;
    int numEleitos;

    std::vector<Candidato> candidatosEleitos;
    std::map<int, Candidato> candidatos;
    std::map<int, Partido> partidos;

    //static void trim();

public:
    Eleicao(const int& condigo,const string& dataStr);

    // getters na implementacao em java nao eram usados
    // entao serao ignorados aqui

    void processarCandidatosPartidos(const string& caminhoArquivo);
    void processarVotos(const string& caminhoArquivo);
    void gerarRelatorios();
};

#endif