#ifndef DATA_UTILS_HPP
#define DATA_UTILS_HPP

#include <string>
#include <stdexcept>

class DataUtils {
private:
    int dia;
    int mes;
    int ano;

    static bool ehDataValida(int d, int m, int a);

public:
    DataUtils(int d, int m, int a);
    
    static DataUtils fromString(const std::string& dataStr);
    int calculaPeriodoEmAnos(const DataUtils& outraData) const;

    // Getters
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }

    // sobrecarga de compararadores entre datas
    bool operator<(const DataUtils& outra) const;
    bool operator==(const DataUtils& outra) const;
};

#endif