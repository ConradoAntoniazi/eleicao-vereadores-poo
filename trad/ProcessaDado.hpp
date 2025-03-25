#ifndef PROCESSA_DADO_HPP
#define PROCESSA_DADO_HPP

#include <string>

class ProcessaDado{
public:
    static std::string iso_8859_1_to_utf8(std::string &str);
    static void trim(std::string &str);
    static void removeAspas(std::string &str);
    static std::string formataNumero(const int& numero);
    static std::string formataPercentual(const int& qtd, const int& total);
};

#endif // PROCESSA_DADO_HPP