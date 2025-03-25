#ifndef ELEICAO_HPP
#define ELEICAO_HPP

#include "DataUtils.hpp"
#include "Candidato.hpp"
#include "Partido.hpp"

#include <string>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>

class Eleicao {
private:
    int numEleitos;
    const int codigoCidade;
    const std::string data;

    std::vector<std::shared_ptr<Candidato>> candidatosEleitos;
    std::map<int, std::shared_ptr<Candidato>> candidatos;
    std::map<int, std::shared_ptr<Partido>> partidos;

    void geraRelatorioVereadoresEleitos();
    void geraRelatoriosSobreMaisVotados();
    void geraRelatorioVotacaoPartidos(); 
    void geraRelatorioPrimeiroUltimoPartido(); 
    void geraRelatorioFaixaEtaria(); 
    void geraRelatorioGenero(); 
    void geraRelatorioTotalVotos();

public:
    Eleicao(const int& condigo,const std::string& dataStr);

    // getters na implementacao em java nao eram usados
    // entao serao ignorados aqui

    void processarCandidatosPartidos(const std::string& caminhoArquivo);
    void processarVotos(const std::string& caminhoArquivo);
    void gerarRelatorios();
};

#endif