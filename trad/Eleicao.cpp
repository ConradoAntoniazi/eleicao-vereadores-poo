#include <fstream>
#include <sstream>
#include <algorithm>

#include "Eleicao.hpp"
#include "UTF8Utils.hpp"
#include <iostream>

using namespace std;

#define COLUNA_CODIGO_CARGO 13
#define COLUNA_CODIGO_MUNICIPIO 11
#define COLUNA_NUMERO_PARTIDO 25

#define COLUNA_NUMERO_FEDERACAO 28
#define COLUNA_NOME_PARTIDO 27
#define COLUNA_SIGLA_PARTIDO 26

#define COLUNA_NUMERO_CANDIDATO 16
#define COLUNA_NOME_URNA_CANDIDATO 18
#define COLUNA_DATA_NASC_CANDIDATO 36
#define COLUNA_GENERO_CANDIDATO 38
#define COLUNA_SITUACAO_CANDIDATO 48

#define MAIOR_COLUNA_OBSERVADA 48

void Eleicao::processarCandidatosPartidos(const string& caminhoArquivo) {
    try {
        ifstream arquivo(caminhoArquivo, ios::binary);
        if (!arquivo.is_open()) {
            throw runtime_error("Não foi possível abrir o arquivo");
        }

        string linha;
        bool primeiraLinha = true;

        while (getline(arquivo, linha)) {
            string linhaUtf8 = UTF8Utils::iso_8859_1_to_utf8(linha);

            if (primeiraLinha) {
                primeiraLinha = false;
                continue;
            }

            vector<string> campos;
            stringstream ss(linhaUtf8);
            string campo;

            // Dividir a linha por ';'
            while (getline(ss, campo, ';')) {
                // Remover aspas e espaços em branco
                campo.erase(remove(campo.begin(), campo.end(), '\"'), campo.end());
                UTF8Utils::trim(campo);
                campos.push_back(campo);
            }

            if (campos.size() < (MAIOR_COLUNA_OBSERVADA + 1)) {
                cerr << "Linha incompleta: " << linhaUtf8 << endl;
                continue;
            }

            try {
                // Processar campos numéricos
                int codigoCargo = stoi(campos[13]);
                int codigoMunicipio = stoi(campos[11]);
                int situacaoTurno = stoi(campos[48]);

                // Filtros iniciais
                if (codigoCargo != 13 || codigoMunicipio != this->codigoCidade || situacaoTurno == -1) {
                    int numPartido = stoi(campos[25]);
                    int numeroFederacao = stoi(campos[28]);

                    // Criar partido se não existir
                    if (partidos.find(numPartido) == partidos.end()) {
                        Partido* novoPartido = new Partido(
                            numPartido,
                            campos[26],
                            campos[27],
                            numeroFederacao
                        );
                        partidos.emplace(numPartido, novoPartido);
                    }
                    continue;
                }

                // Processar dados do partido
                int numPartido = stoi(campos[25]);
                int numeroFederacao = stoi(campos[28]);

                // Criar/recuperar partido
                auto itPartido = partidos.find(numPartido);
                if (itPartido == partidos.end()) {
                    Partido* novoPartido = new Partido(
                        numPartido,
                        campos[26],
                        campos[27],
                        numeroFederacao
                    );
                    partidos.emplace(numPartido, novoPartido);
                    itPartido = partidos.find(numPartido);
                }

                // Processar dados do candidato
                int numero = stoi(campos[16]);
                string nomeUrna = campos[18];
                string dataNascimento = campos[36];
                int genero = stoi(campos[38]);
                int situacao = stoi(campos[48]);

                // Criar candidato
                Candidato* candAux = new Candidato(
                    numero,
                    nomeUrna,
                    *(itPartido->second), // Passa a referência do partido
                    dataNascimento,
                    genero,
                    situacao
                );
                

                // Verificar se foi eleito
                if (candAux->isEleito()) {
                    numEleitos++;
                    candidatosEleitos.push_back(candAux);
                }

                // Adicionar aos containers
                candidatos[numero] = candAux;
                itPartido->second->addCandidato(candAux);

            } catch (const invalid_argument& e) {
                cerr << "Erro de conversão numérica: " << e.what() << endl;
                continue;
            } catch (const out_of_range& e) {
                cerr << "Índice de campo inválido: " << e.what() << endl;
                continue;
            }
        }
        arquivo.close();

    } catch (const exception& e) {
        cerr << "Erro durante o processamento: " << e.what() << endl;
    }
}

