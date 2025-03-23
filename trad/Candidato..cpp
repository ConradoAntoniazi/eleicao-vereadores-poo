#include "Candidato.hpp"
#include "Partido.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

bool Candidato::validarData(const string &data)
{
    istringstream ss(data);
    int dia, mes, ano;
    char delim1, delim2;

    ss >> dia >> delim1 >> mes >> delim2 >> ano;
    if (delim1 != '/' || delim2 != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900)
    {
        return false;
    }
    return true;
}

Candidato::Candidato(const int& numero, const string& nomeUrna, Partido &partido,
                     const string &dataNasc, const int& genero, const int& situacao)
    : numero(numero),
      nomeUrna(nomeUrna),
      partido(&partido),
      genero(Genero::fromCodigo(genero)), 
      situacaoEleitoral(SituacaoEleitoral::fromCodigo(situacao))
{

    if (!(&partido))
    {
        throw invalid_argument("Partido não pode ser nulo");
    }

    if (!validarData(dataNasc))
    {
        throw invalid_argument("Data de nascimento inválida: " + dataNasc);
    }

    this->dataNascimento = dataNasc; 
    this->votos = 0;
}

// Getters
int Candidato::getNumero() const { return numero; }

string Candidato::getNomeUrna(int flagFederado) const
{
    if (partido->getNumeroFederacao() != -1 && flagFederado != 0)
    {
        return "*" + nomeUrna;
    }
    return nomeUrna;
}

Partido &Candidato::getPartido() const { return *partido; }
int Candidato::getVotos() const { return votos; }
Genero Candidato::getGenero() const { return genero; }
string Candidato::getDataNascimento() const { return dataNascimento; }

bool Candidato::isEleito() const
{
    return situacaoEleitoral.getCodigo() == SituacaoEleitoral::ELEITO ||
           situacaoEleitoral.getCodigo() == SituacaoEleitoral::ELEITO_POR_QUOCIENTE_PARTIDARIO ||
           situacaoEleitoral.getCodigo() == SituacaoEleitoral::ELEITO_POR_MEDIA;
}

void Candidato::addVotos(int votos)
{
    if (votos < 0)
    {
        throw invalid_argument("Votos não podem ser negativos");
    }
    this->votos += votos;
}

int Candidato::getIdade(const string &dataEleicaoStr) const
{
    // Implementação do cálculo de idade usando <chrono> , da std (simplificado)
    // Nota: Requer parsing completo das datas
    return 0;
}