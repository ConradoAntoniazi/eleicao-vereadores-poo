#ifndef PROCESSA_DADO_HPP
#define PROCESSA_DADO_HPP

#include <string>

/**
 * Classe utilitária para processar e formatar dados textuais e numéricos.
 * Contém apenas métodos estáticos.
 */
class ProcessaDado{
public:
    /**
     * Converte uma string codificada em ISO-8859-1 para UTF-8.
     * @param str Referência para a string a ser convertida.
     * @return Uma nova string em UTF-8.
     */
    static std::string iso_8859_1_to_utf8(std::string &str);

    /**
     * Remove espaços em branco de uma string.
     * @param str Referência para a string a ser modificada.
     */
    static void trim(std::string &str);

    /**
     * Remove todas as aspas (") de uma string.
     * @param str Referência para a string a ser modificada.
     */
    static void removeAspas(std::string &str);

    /**
     * Formata um número inteiro como string.
     * @param numero Valor inteiro a ser formatado.
     * @return Representação textual do número.
     */
    static std::string formataNumero(const int& numero);

    /**
     * Formata a porcentagem de uma quantidade em relação ao total.
     * @param qtd Quantidade parcial.
     * @param total Quantidade total.
     * @return String com percentual formatado com duas casas decimais e símbolo "%".
     */
    static std::string formataPercentual(const int& qtd, const int& total);
};

#endif // PROCESSA_DADO_HPP
