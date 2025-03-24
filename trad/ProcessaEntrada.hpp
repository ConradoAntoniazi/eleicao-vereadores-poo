#ifndef PROCESSA_ENTRADA_HPP
#define PROCESSA_ENTRADA_HPP

#include <string>

using namespace std;

class ProcessaEntrada{
public:
    static string iso_8859_1_to_utf8(string &str);
    static bool compare_pt_BR(const string &s1, const string &s2);
    static void trim(string &str);
    static void removeAspas(string &str);
    static string formataNumero(int numero);
};

#endif // PROCESSA_ENTRADA_HPP