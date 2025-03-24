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
    int codigoCidade;
    int numEleitos;
    DataUtils data;

    std::vector<Candidato> candidatosEleitos;
    std::map<int, Candidato> candidatos;
    std::map<int, Partido> partidos;

public:
    Eleicao(int condigo, string dataStr);

    // getters na implementacao em java nao eram usados
    // entao serao ignorados aqui

    void processarCandidatosPartidos(string caminhoArquivo);
    void processarVotos(string caminhoArquivo);
    void gerarRelatorios();
};

#endif