#include "DataUtils.hpp"
#include <sstream>
#include <algorithm> // Para std::replace
#include <iomanip>

DataUtils::DataUtils(int d, int m, int a) : dia(d), mes(m), ano(a) {
    if (!ehDataValida(d, m, a)) {
        throw std::invalid_argument("Data inválida");
    }
}

bool DataUtils::ehDataValida(int d, int m, int a) {
    if (a < 1 || m < 1 || m > 12 || d < 1) return false;
    
    const int diasPorMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int maxDias = diasPorMes[m-1];
    
    // Verifica ano bissexto (apenas para fevereiro)
    if (m == 2 && (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0))) {
        maxDias = 29;
    }
    
    return d <= maxDias;
}

DataUtils DataUtils::fromString(const std::string& dataStr) {
    std::string strModificada = dataStr;
    std::replace(strModificada.begin(), strModificada.end(), '/', ' ');
    
    std::istringstream iss(strModificada);
    int d, m, a;

    if (!(iss >> d >> m >> a)) {
        throw std::invalid_argument("Formato inválido. Use dd/mm/aaaa");
    }
    
    if(!ehDataValida(d, m, a)){ 
        throw std::invalid_argument("Forneca uma data válida");
    }

    return DataUtils(d, m, a);
}

std::string DataUtils::toString() const {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << this->dia << "/"
       << std::setw(2) << std::setfill('0') << this->mes << "/"
       << this->ano;
    
    return ss.str();
}


int DataUtils::calculaPeriodoEmAnos(const DataUtils& outraData) const {
    int anos = outraData.ano - ano;
    
    if (outraData.mes < mes || (outraData.mes == mes && outraData.dia < dia)) {
        anos--;
    }
    
    return anos;
}

bool DataUtils::operator<(const DataUtils& outra) const {
    if (ano != outra.ano) {
        return ano < outra.ano;
    }
    if (mes != outra.mes) {
        return mes < outra.mes;
    }
    return dia < outra.dia;
}

bool DataUtils::operator==(const DataUtils& outra) const {
    return dia == outra.dia && mes == outra.mes && ano == outra.ano;
}