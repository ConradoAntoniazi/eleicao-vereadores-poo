#include "ProcessaEntrada.hpp"

#include <locale>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

string ProcessaEntrada::iso_8859_1_to_utf8(string &str)
{
  // adaptado de: https://stackoverflow.com/a/39884120 :-)
  string strOut;
  for (string::iterator it = str.begin(); it != str.end(); ++it)
  {
    uint8_t ch = *it;
    if (ch < 0x80)
    {
      // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
      strOut.push_back(ch);
    }
    else
    {
      // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
      // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
      strOut.push_back(0b11000000 | (ch >> 6));
      // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
      strOut.push_back(0b10000000 | (ch & 0b00111111));
    }
  }
  return strOut;
}

void ProcessaEntrada::trim(string &str)
{
  str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
  str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
}

void ProcessaEntrada::removeAspas(string &str){
  str.erase(remove(str.begin(), str.end(), '\"'), str.end());
}

string ProcessaEntrada::formataNumero(const int& numero) {
  stringstream ss;
  ss << fixed << numero;
  return ss.str();
}

string ProcessaEntrada::formataPercentual(const int& qtd, const int& total){
  if(total <= 0){
    cout << "ERRO EM FORMATA PERCENTUAL" << endl;
  }
  
  double percent = (total > 0) ? ((qtd * 100.0) / total) : 0.0;
  stringstream ss;
  ss << fixed << setprecision(2) << percent << "%";
  return ss.str();
}