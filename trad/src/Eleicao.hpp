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

/**
 * @class Eleicao
 * @brief Classe que representa uma eleição.
 * Processa e gera relatórios relacionados aos candidatos, partidos e votos.
 */
class Eleicao {
private:
    int numEleitos; // Número de eleitos na eleição.
    const int codigoCidade; // Código da cidade onde a eleição ocorreu.
    const std::string data; // Data da eleição.

    std::vector<std::shared_ptr<Candidato>> candidatosEleitos; // Lista de candidatos eleitos.
    std::map<int, std::shared_ptr<Candidato>> candidatos; // Mapa de candidatos, chave é o número do candidato.
    std::map<int, std::shared_ptr<Partido>> partidos; // Mapa de partidos, chave é o número do partido.

    /**
     * @brief Gera o relatório dos vereadores eleitos.
     */
    void geraRelatorioVereadoresEleitos();

    /**
     * @brief Gera relatórios sobre os mais votados.
     */
    void geraRelatoriosSobreMaisVotados();

    /**
     * @brief Gera o relatório de votação dos partidos.
     */
    void geraRelatorioVotacaoPartidos();

    /**
     * @brief Gera o relatório do primeiro e último partido.
     */
    void geraRelatorioPrimeiroUltimoPartido();

    /**
     * @brief Gera o relatório sobre faixa etária.
     */
    void geraRelatorioFaixaEtaria();

    /**
     * @brief Gera o relatório sobre gênero.
     */
    void geraRelatorioGenero();

    /**
     * @brief Gera o relatório sobre o total de votos.
     */
    void geraRelatorioTotalVotos();

public:
    /**
     * @brief Construtor da classe Eleicao.
     * @param condigo Código da cidade onde ocorreu a eleição.
     * @param dataStr Data da eleição no formato de string.
     */
    Eleicao(const int& condigo,const std::string& dataStr);

    /**
     * @brief Processa os candidatos e partidos a partir de um arquivo.
     * @param caminhoArquivo Caminho para o arquivo com as informações de candidatos e partidos.
     */
    void processarCandidatosPartidos(const std::string& caminhoArquivo);

    /**
     * @brief Processa os votos a partir de um arquivo.
     * @param caminhoArquivo Caminho para o arquivo com os votos.
     */
    void processarVotos(const std::string& caminhoArquivo);

    /**
     * @brief Gera todos os relatórios.
     */
    void gerarRelatorios();

};

#endif