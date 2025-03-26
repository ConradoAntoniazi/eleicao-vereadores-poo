#ifndef PARTIDO_HPP
#define PARTIDO_HPP

#include <vector>
#include <list>
#include <string>
#include <memory>

class Candidato; // Referência antecipada para evitar dependências circulares

/**
 * Classe que representa um partido político com informações sobre
 * número, sigla, nome, federação, votos e seus candidatos.
 */
class Partido {
private:
    int numero; ///< Número do partido.
    std::string sigla; ///< Sigla do partido.
    std::string nome; ///< Nome completo do partido.
    int numeroFederacao; ///< Número da federação do partido.
    int votosLegenda; ///< Total de votos de legenda recebidos pelo partido.

    /**
     * Lista de candidatos do partido.
     * Utiliza weak_ptr para evitar problemas de ciclo de vida com shared_ptr.
     */
    std::list<std::weak_ptr<Candidato>> candidatos; 

public:
    /**
     * Construtor do partido.
     * @param numero Número do partido.
     * @param sigla Sigla do partido.
     * @param nome Nome completo do partido.
     * @param numeroFed Número da federação associada.
     */
    Partido(const int& numero, const std::string& sigla, const std::string& nome, const int& numeroFed);

    // Getters

    /** @return Número do partido. */
    int getNumero() const;

    /** @return Sigla do partido. */
    std::string getSigla() const;

    /** @return Nome do partido. */
    std::string getNome() const;

    /** @return Número da federação associada ao partido. */
    int getNumeroFederacao() const;

    /** @return Total de votos de legenda do partido. */
    int getVotosLegenda() const;

    /** @return Vetor de ponteiros compartilhados para os candidatos do partido. */
    std::vector<std::shared_ptr<Candidato>> getCandidatos() const;

    /**
     * Adiciona votos à legenda do partido.
     * @param votos Quantidade de votos a adicionar.
     */
    void addVotosLegenda(int votos);

    /**
     * Adiciona um candidato ao partido.
     * @param candidato Ponteiro compartilhado para o candidato a ser adicionado.
     */
    void addCandidato(std::shared_ptr<Candidato> candidato); 

    /**
     * @return Total de votos nominais dos candidatos do partido.
     */
    int getVotosNominais() const;

    /**
     * @return Total de votos do partido (nominais + legenda).
     */
    int getTotalVotos() const;

    /**
     * @return Número de candidatos eleitos pelo partido.
     */
    int getNumEleitos() const;

    /**
     * @return Vetor com candidatos válidos (com mais de 0 votos).
     */
    std::vector<std::shared_ptr<Candidato>> getCandidatosValidos() const;

    /**
     * @return Candidato mais votado do partido, ou nullptr se não houver candidatos válidos.
     */
    std::shared_ptr<Candidato> getCandidatoMaisVotado() const;
};

#endif
