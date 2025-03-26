#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include "Genero.hpp"
#include "SituacaoEleitoral.hpp"
#include "DataUtils.hpp"

#include <string>
#include <memory>

class Partido; // Forward declaration

/**
 * @brief Representa um candidato em uma eleição.
 */
class Candidato {
private:
    int votos; // Quantidade de votos recebidos pelo candidato.
    int numero; // Número do candidato na urna.
    std::string nomeUrna; // Nome do candidato na urna.
    
    /**
     * @brief Ponteiro fraco para o partido ao qual o candidato pertence.
     * 
     * Um `std::weak_ptr` é usado para evitar ciclos de referência,
     * pois a classe Candidato não é responsável pelo ciclo de vida do Partido.
     */
    std::weak_ptr<Partido> partido;
    
    DataUtils dataNascimento; // Data de nascimento do candidato.
    Genero genero; // Gênero do candidato.
    SituacaoEleitoral situacaoEleitoral; // Situação eleitoral do candidato.

public:
    /**
     * @brief Construtor da classe Candidato.
     * 
     * @param numero Número do candidato.
     * @param nomeUrna Nome do candidato na urna.
     * @param partido Ponteiro compartilhado para o partido do candidato.
     * @param dataNasc Data de nascimento do candidato (string formatada).
     * @param genero Código do gênero do candidato.
     * @param situacao Código da situação eleitoral do candidato.
     */
    Candidato(const int& numero, const std::string& nomeUrna, std::shared_ptr<Partido> partido, 
              const std::string& dataNasc, const int& genero, const int& situacao);
    
    /** @brief Retorna o número do candidato. */
    int getNumero() const;
    
    /**
     * @brief Retorna o nome do candidato na urna.
     * @param flagFederado Flag para indicar formatação específica do nome.
     * @return Nome do candidato formatado.
     */
    std::string getNomeUrna(int flagFederado) const;
    
    /**
     * @brief Retorna o partido do candidato.
     * @return Ponteiro compartilhado para o partido.
     */
    std::shared_ptr<Partido> getPartido() const;
    
    /** @brief Retorna a quantidade de votos recebidos pelo candidato. */
    int getVotos() const;
    
    /** @brief Retorna o gênero do candidato. */
    Genero getGenero() const;
    
    /** @brief Retorna a data de nascimento do candidato. */
    DataUtils getDataNascimento() const;
    
    /** @brief Verifica se o candidato foi eleito. */
    bool isEleito() const;
    
    /**
     * @brief Calcula a idade do candidato com base na data da eleição.
     * @param dataEleicaoStr Data da eleição no formato de string.
     * @return Idade do candidato no dia da eleição.
     */
    int getIdade(const std::string& dataEleicaoStr) const;
    
    /**
     * @brief Adiciona votos ao candidato.
     * @param votos Número de votos a serem adicionados.
     */
    void addVotos(int votos);
};

#endif // CANDIDATO_HPP
