#include <fstream>
#include <sstream>
#include <algorithm>

#include "Eleicao.hpp"
#include "ProcessaEntrada.hpp"
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

#define COLUNA_VOTACAO_CODIGO_CARGO 17
#define COLUNA_VOTACAO_CODIGO_MUNICIPO 13
#define COLUNA_VOTACAO_NUMERO_VOTAVEL 19
#define COLUNA_VOTACAO_QTD_VOTOS 21


void Eleicao::processarCandidatosPartidos(const string &caminhoArquivo)
{
    try
    {
        ifstream arquivo(caminhoArquivo, ios::binary);
        if (!arquivo.is_open())
        {
            throw runtime_error("Não foi possível abrir o arquivo");
        }

        string linha;
        bool primeiraLinha = true;

        while (getline(arquivo, linha))
        {
            string linhaUtf8 = ProcessaEntrada::iso_8859_1_to_utf8(linha);

            if (primeiraLinha)
            {
                primeiraLinha = false;
                continue;
            }

            vector<string> campos;
            stringstream ss(linhaUtf8);
            string campo;

            // Dividir a linha por ';'
            while (getline(ss, campo, ';'))
            {
                // Remover aspas e espaços em branco
                //campo.erase(remove(campo.begin(), campo.end(), '\"'), campo.end());
                ProcessaEntrada::removeAspas(campo);
                ProcessaEntrada::trim(campo);
                campos.push_back(campo);
            }

            // Sempre colocar o maior idx de coluna observado aqui
            if (campos.size() < (COLUNA_SITUACAO_CANDIDATO + 1))
            {
                throw out_of_range("Linha com campos insuficientes");

            }

            try
            {
                // Processar campos numéricos
                int codigoCargo = stoi(campos[COLUNA_CODIGO_CARGO]);
                int codigoMunicipio = stoi(campos[COLUNA_CODIGO_MUNICIPIO]);
                int situacaoTurno = stoi(campos[COLUNA_SITUACAO_CANDIDATO]);

                // Filtros iniciais
                if (codigoCargo != 13 || codigoMunicipio != this->codigoCidade || situacaoTurno == -1)
                {
                    int numPartido = stoi(campos[COLUNA_NUMERO_PARTIDO]);
                    int numeroFederacao = stoi(campos[COLUNA_NUMERO_FEDERACAO]);

                    // Criar partido se não existir
                    if (partidos.find(numPartido) == partidos.end())
                    {
                        Partido *novoPartido = new Partido(
                            numPartido,
                            campos[COLUNA_SIGLA_PARTIDO],
                            campos[COLUNA_NOME_PARTIDO],
                            numeroFederacao);
                        partidos.emplace(numPartido, novoPartido);
                    }
                    continue;
                }

                // Processar dados do partido
                int numPartido = stoi(campos[COLUNA_NUMERO_PARTIDO]);
                int numeroFederacao = stoi(campos[COLUNA_NUMERO_FEDERACAO]);

                // Criar/recuperar partido
                auto itPartido = partidos.find(numPartido);
                if (itPartido == partidos.end())
                {
                    Partido *novoPartido = new Partido(
                        numPartido,
                        campos[COLUNA_SIGLA_PARTIDO],
                        campos[COLUNA_NOME_PARTIDO],
                        numeroFederacao);
                    partidos.emplace(numPartido, novoPartido);
                    itPartido = partidos.find(numPartido);
                }

                // Processar dados do candidato
                int numero = stoi(campos[COLUNA_NUMERO_CANDIDATO]);
                string nomeUrna = campos[COLUNA_NOME_URNA_CANDIDATO];
                string dataNascimento = campos[COLUNA_DATA_NASC_CANDIDATO];
                int genero = stoi(campos[COLUNA_GENERO_CANDIDATO]);
                int situacao = stoi(campos[COLUNA_SITUACAO_CANDIDATO]);

                // Criar candidato
                Candidato *candAux = new Candidato(
                    numero,
                    nomeUrna,
                    *(itPartido->second), // referência do partido
                    dataNascimento,
                    genero,
                    situacao);

                // Verificar se foi eleito
                if (candAux->isEleito())
                {
                    numEleitos++;
                    candidatosEleitos.push_back(candAux);
                }

                // Adicionar aos containers
                candidatos[numero] = candAux;
                itPartido->second->addCandidato(candAux);
            }
            catch (const invalid_argument &e)
            {
                cerr << "Erro de conversão numérica: " << e.what() << endl;
                continue;
            }
            catch (const out_of_range &e)
            {
                cerr << "Índice de campo inválido: " << e.what() << endl;
                continue;
            }
        }
        arquivo.close();
    }
    catch (const exception &e)
    {
        cerr << "Erro durante o processamento: " << e.what() << endl;
    }
}

void Eleicao::processarVotos(const string &caminhoArquivo)
{
    try
    {
        ifstream arquivo(caminhoArquivo, ios::binary);
        if (!arquivo.is_open())
        {
            throw runtime_error("Não foi possível abrir o arquivo de votação");
        }

        string linha;
        bool primeiraLinha = true;

        while (getline(arquivo, linha))
        {
            if (primeiraLinha)
            {
                primeiraLinha = false;
                continue;
            }

            string linhaUtf8 = ProcessaEntrada::iso_8859_1_to_utf8(linha);
            vector<string> campos;
            stringstream ss(linhaUtf8);
            string campo;

            while (getline(ss, campo, ';'))
            {
                //campo.erase(remove(campo.begin(), campo.end(), '\"'), campo.end());
                ProcessaEntrada::removeAspas(campo);
                ProcessaEntrada::trim(campo);
                campos.push_back(campo);
            }

            try
            {
                if (campos.size() < 22)
                {
                    throw out_of_range("Linha com campos insuficientes");
                }

                int codigoCargo = stoi(campos[COLUNA_VOTACAO_CODIGO_CARGO]);     // CD_CARGO
                int codigoMunicipio = stoi(campos[COLUNA_VOTACAO_CODIGO_MUNICIPO]); // CD_MUNICIPIO
                int numeroVotavel = stoi(campos[COLUNA_VOTACAO_NUMERO_VOTAVEL]);   // NR_VOTAVEL
                int quantidadeVotos = stoi(campos[COLUNA_VOTACAO_QTD_VOTOS]); // QT_VOTOS

                if (codigoCargo != 13 || codigoMunicipio != this->codigoCidade)
                {
                    continue;
                }

                // Ignora votos brancos/nulos (95-98)
                if (numeroVotavel >= 95 && numeroVotavel <= 98)
                {
                    continue;
                }

                // Verifica se é voto nominal (candidato)
                auto itCandidato = candidatos.find(numeroVotavel);
                if (itCandidato != candidatos.end())
                {
                    itCandidato->second->addVotos(quantidadeVotos);
                }
                // Verifica se é voto de legenda (partido)
                else
                {
                    auto itPartido = partidos.find(numeroVotavel);
                    if (itPartido != partidos.end())
                    {
                        itPartido->second->addVotosLegenda(quantidadeVotos);
                    }
                }
            }
            catch (const invalid_argument &e)
            {
                cerr << "Erro de conversão numérica na linha ignorada: " << e.what() << endl;
                continue;
            }
            catch (const out_of_range &e)
            {
                cerr << "Linha mal formatada ou incompleta: " << e.what() << endl;
                continue;
            }
        }
        arquivo.close();
    }
    catch (const exception &e)
    {
        cerr << "Erro durante o processamento dos votos: " << e.what() << endl;
    }
}

void Eleicao::geraRelatorioVereadoresEleitos() {
    // Primeiro relatório: Vereadores eleitos
    vector<Candidato*> candidatosEleitos;
    
    // Coleta todos os candidatos eleitos
    for (const auto& par : candidatos) {
        if (par.second->isEleito()) {
            candidatosEleitos.push_back(par.second);
        }
    }

    // Ordena por votos (decrescente) e data nascimento (crescente)
    sort(candidatosEleitos.begin(), candidatosEleitos.end(),
        [](Candidato* a, Candidato* b) {
            if (a->getVotos() != b->getVotos()) {
                return a->getVotos() > b->getVotos();
            }
            return a->getDataNascimento() < b->getDataNascimento();
        });

    // Imprime o relatório
    cout << "Vereadores eleitos:\n";
    int posicao = 1;
    for (const auto& candidato : candidatosEleitos) {
        cout << posicao << " - " 
             << candidato->getNomeUrna(1) << " ("
             << candidato->getPartido().getSigla() << ", "
             << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        posicao++;
    }
    cout << "\n"; // Espaço entre relatórios
}

void Eleicao::geraRelatoriosSobreMaisVotados(){
    // Relatório de mais votados e comparação entre sistemas
    vector<Candidato*> candidatosMaisVotados;
    
    // Preenche com todos os candidatos
    for (const auto& par : candidatos) {
        candidatosMaisVotados.push_back(par.second);
    }

    // Ordena por votos (decrescente) e data nascimento (crescente)
    sort(candidatosMaisVotados.begin(), candidatosMaisVotados.end(),
        [](Candidato* a, Candidato* b) {
            if (a->getVotos() != b->getVotos()) {
                return a->getVotos() > b->getVotos();
            }
            return a->getDataNascimento() < b->getDataNascimento();
        });

    vector<Candidato*> candidatosSeriamEleitos;
    vector<Candidato*> candidatosEleitosPorProporcionalidade;

    cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):\n";
    int posicao = 1;
    for (const auto& candidato : candidatosMaisVotados) {
        if (posicao <= this->numEleitos) {
            cout << posicao << " - " 
                 << candidato->getNomeUrna(1) << " ("
                 << candidato->getPartido().getSigla() << ", "
                 << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        }

        // Verifica candidatos que seriam eleitos no majoritário
        if (!candidato->isEleito() && posicao <= this->numEleitos) {
            candidatosSeriamEleitos.push_back(candidato);
        }

        // Verifica candidatos beneficiados pelo proporcional
        if (candidato->isEleito() && posicao > this->numEleitos) {
            candidatosEleitosPorProporcionalidade.push_back(candidato);
        }

        posicao++;
    }

    // Relatório: Candidatos que seriam eleitos no majoritário
    cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n"
         << "(com sua posição no ranking de mais votados)\n";
    for (const auto& candidato : candidatosSeriamEleitos) {
        auto it = find(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), candidato);
        if (it != candidatosMaisVotados.end()) {
            int pos = distance(candidatosMaisVotados.begin(), it) + 1;
            cout << pos << " - " 
                 << candidato->getNomeUrna(1) << " ("
                 << candidato->getPartido().getSigla() << ", "
                 << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        }
    }

    // Relatório: Candidatos beneficiados pelo proporcional
    cout << "\nEleitos, que se beneficiaram do sistema proporcional:\n"
         << "(com sua posição no ranking de mais votados)\n";
    for (const auto& candidato : candidatosEleitosPorProporcionalidade) {
        auto it = find(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), candidato);
        if (it != candidatosMaisVotados.end()) {
            int pos = distance(candidatosMaisVotados.begin(), it) + 1;
            cout << pos << " - " 
                 << candidato->getNomeUrna(1) << " ("
                 << candidato->getPartido().getSigla() << ", "
                 << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        }
    }
}

void Eleicao::gerarRelatorios() {
    //colocar relatorio 1 dps
    geraRelatorioVereadoresEleitos(); // Relatorio 2
    geraRelatoriosSobreMaisVotados(); // Relatorios 3, 4 e 5

}