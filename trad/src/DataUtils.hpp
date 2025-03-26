#ifndef DATA_UTILS_HPP
#define DATA_UTILS_HPP

#include <string>
#include <stdexcept>

/**
 * @class DataUtils
 * @brief Classe utilitária para manipulação de datas.
 */
class DataUtils {
private:
    int dia;
    int mes;
    int ano;

    /**
     * @brief Verifica se uma data é válida.
     * @param d Dia.
     * @param m Mês.
     * @param a Ano.
     * @return true se a data for válida, false caso contrário.
     */
    static bool ehDataValida(int d, int m, int a);

public:
    /**
     * @brief Construtor da classe DataUtils.
     * @param d Dia.
     * @param m Mês.
     * @param a Ano.
     * @throw std::invalid_argument Se a data não for válida.
     */
    DataUtils(int d, int m, int a);
    
    /**
     * @brief Converte uma string no formato DD/MM/AAAA para um objeto DataUtils.
     * @param dataStr String contendo a data.
     * @return Objeto DataUtils representando a data.
     * @throw std::invalid_argument Se a string não representar uma data válida.
     */
    static DataUtils fromString(const std::string& dataStr);
    
    /**
     * @brief Converte a data para uma string no formato DD/MM/AAAA.
     * @return String representando a data.
     */
    std::string toString() const;
    
    /**
     * @brief Calcula a diferença em anos entre duas datas.
     * @param outraData Outra data para comparação.
     * @return Diferença em anos entre as duas datas.
     */
    int calculaPeriodoEmAnos(const DataUtils& outraData) const;

    // Getters
    int getDia() const { return dia; } // Retorna o dia da data.
    int getMes() const { return mes; } // Retorna o mês da data.
    int getAno() const { return ano; } // Retorna o ano da data.

    // Sobrecarga de operadores de comparação
    /**
     * @brief Operador de comparação "menor que" para objetos DataUtils.
     * @param outra Data a ser comparada.
     * @return true se a data atual for menor que a outra, false caso contrário.
     */
    bool operator<(const DataUtils& outra) const;
    
    /**
     * @brief Operador de igualdade para objetos DataUtils.
     * @param outra Data a ser comparada.
     * @return true se as datas forem iguais, false caso contrário.
     */
    bool operator==(const DataUtils& outra) const;
};

#endif