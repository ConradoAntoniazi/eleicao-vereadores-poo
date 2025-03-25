#include <fstream>
#include <sstream>
#include <algorithm>

#include "Eleicao.hpp"
#include "ProcessaEntrada.hpp"
#include <iostream>
#include <iomanip>

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


Eleicao::Eleicao(const int& codigo,const string& dataStr): numEleitos(0), codigoCidade(codigo), data(dataStr){}

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
                        auto novoPartido = make_shared<Partido>(
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
                    auto novoPartido = make_shared<Partido>(
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
                auto candAux = make_shared<Candidato>(
                    numero,
                    nomeUrna,
                    itPartido->second,
                    dataNascimento,
                    genero,
                    situacao);

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

void Eleicao::processarVotos(const string &caminhoArquivo) {
    try {
        ifstream arquivo(caminhoArquivo, ios::binary);
        if (!arquivo.is_open()) {
            throw runtime_error("Não foi possível abrir o arquivo de votação");
        }

        string linha;
        bool primeiraLinha = true;

        while (getline(arquivo, linha)) {
            if (primeiraLinha) {
                primeiraLinha = false;
                continue;
            }

            vector<string> campos;
            size_t start = 0, end = 0;
            while ((end = linha.find(';', start)) != string::npos) {
                campos.push_back(linha.substr(start, end - start));
                start = end + 1;
            }
            campos.push_back(linha.substr(start)); // Último campo

            if (campos.size() < 22) {
                cerr << "Linha com campos insuficientes" << endl;
                continue;
            }

            char *endPtr;
            int codigoCargo = strtol(campos[COLUNA_VOTACAO_CODIGO_CARGO].c_str(), &endPtr, 10);
            int codigoMunicipio = strtol(campos[COLUNA_VOTACAO_CODIGO_MUNICIPO].c_str(), &endPtr, 10);
            int numeroVotavel = strtol(campos[COLUNA_VOTACAO_NUMERO_VOTAVEL].c_str(), &endPtr, 10);
            int quantidadeVotos = strtol(campos[COLUNA_VOTACAO_QTD_VOTOS].c_str(), &endPtr, 10);

            if (codigoCargo != 13 || codigoMunicipio != this->codigoCidade) {
                continue;
            }

            if (numeroVotavel >= 95 && numeroVotavel <= 98) {
                continue;
            }

            auto itCandidato = candidatos.find(numeroVotavel);
            if (itCandidato != candidatos.end()) {
                itCandidato->second->addVotos(quantidadeVotos);
            } else {
                auto itPartido = partidos.find(numeroVotavel);
                if (itPartido != partidos.end()) {
                    itPartido->second->addVotosLegenda(quantidadeVotos);
                }
            }
        }
        arquivo.close();
    } catch (const exception &e) {
        cerr << "Erro durante o processamento dos votos: " << e.what() << endl;
    }
}

void Eleicao::geraRelatorioVereadoresEleitos() {
    // Ao contrario de C, isso aqui faz uma copia do vetor candidatosEletios
    // (ainda que eles apontem para os mesmos objetos, por serem vetores de ponteiros)
    std::vector<std::shared_ptr<Candidato>> sortedCandidates = this->candidatosEleitos;
    
    // Ordena por votos (decrescente) e, em caso de empate, por data de nascimento (crescente)
    std::sort(sortedCandidates.begin(), sortedCandidates.end(),
         [](const std::shared_ptr<Candidato>& a, const std::shared_ptr<Candidato>& b) {
             if (a->getVotos() != b->getVotos())
                 return a->getVotos() > b->getVotos();
             return a->getDataNascimento() < b->getDataNascimento();
         });
    
    std::cout << "\nVereadores eleitos:\n";
    int posicao = 1;
    for (const auto& candidato : sortedCandidates) {
        // Agora getPartido() retorna um shared_ptr, entao usa-se "->" para acessar getSigla()
        std::cout << posicao << " - " 
                  << candidato->getNomeUrna(1) << " ("
                  << candidato->getPartido()->getSigla() << ", "
                  << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        posicao++;
    }
    std::cout << "\n"; // Espaço entre relatórios
}

void Eleicao::geraRelatoriosSobreMaisVotados() {
    std::vector<std::shared_ptr<Candidato>> candidatosMaisVotados;
    for (const auto& par : candidatos) {
        candidatosMaisVotados.push_back(par.second);
    }

    // Ordena por votos (decrescente) e, em caso de empate, por data de nascimento (crescente)
    std::sort(candidatosMaisVotados.begin(), candidatosMaisVotados.end(),
         [](const std::shared_ptr<Candidato>& a, const std::shared_ptr<Candidato>& b) {
             if (a->getVotos() != b->getVotos())
                 return a->getVotos() > b->getVotos();
             return a->getDataNascimento() < b->getDataNascimento();
         });

    std::vector<std::shared_ptr<Candidato>> candidatosSeriamEleitos;
    std::vector<std::shared_ptr<Candidato>> candidatosEleitosPorProporcionalidade;

    std::cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):\n";
    int posicao = 1;
    for (const auto& candidato : candidatosMaisVotados) {
        if (posicao <= this->numEleitos) {
            std::cout << posicao << " - " 
                      << candidato->getNomeUrna(1) << " ("
                      << candidato->getPartido()->getSigla() << ", "
                      << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        }

        // Se candidato não foi eleito mas está dentro do número de vagas, 
        // ele seria eleito no sistema majoritário.
        if (!candidato->isEleito() && posicao <= this->numEleitos) {
            candidatosSeriamEleitos.push_back(candidato);
        }

        // Se candidato foi eleito, mas está abaixo do número de vagas,
        // se beneficiou do sistema proporcional.
        if (candidato->isEleito() && posicao > this->numEleitos) {
            candidatosEleitosPorProporcionalidade.push_back(candidato);
        }
        posicao++;
    }

    // Relatório: Candidatos que seriam eleitos no sistema majoritário
    std::cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n"
              << "(com sua posição no ranking de mais votados)\n";
    for (const auto& candidato : candidatosSeriamEleitos) {
        auto it = std::find(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), candidato);
        if (it != candidatosMaisVotados.end()) {
            int pos = std::distance(candidatosMaisVotados.begin(), it) + 1;
            std::cout << pos << " - " 
                      << candidato->getNomeUrna(1) << " ("
                      << candidato->getPartido()->getSigla() << ", "
                      << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        }
    }

    // Relatório: Candidatos beneficiados pelo sistema proporcional
    std::cout << "\nEleitos, que se beneficiaram do sistema proporcional:\n"
              << "(com sua posição no ranking de mais votados)\n";
    for (const auto& candidato : candidatosEleitosPorProporcionalidade) {
        auto it = std::find(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), candidato);
        if (it != candidatosMaisVotados.end()) {
            int pos = std::distance(candidatosMaisVotados.begin(), it) + 1;
            std::cout << pos << " - " 
                      << candidato->getNomeUrna(1) << " ("
                      << candidato->getPartido()->getSigla() << ", "
                      << ProcessaEntrada::formataNumero(candidato->getVotos()) << " votos)\n";
        }
    }
}

void Eleicao::geraRelatorioVotacaoPartidos(){
    std::vector<std::shared_ptr<Partido>> partidosOrdenados;
    for (const auto& par : partidos) {
        partidosOrdenados.push_back(par.second);
    }

    // Ordena por total de votos (decrescente) e, em caso de empate, por número do partido (crescente)
    std::sort(partidosOrdenados.begin(), partidosOrdenados.end(),
        [](const std::shared_ptr<Partido>& a, const std::shared_ptr<Partido>& b) {
            if (a->getTotalVotos() != b->getTotalVotos())
                return a->getTotalVotos() > b->getTotalVotos();
            return a->getNumero() < b->getNumero();
        });

    std::cout << "\nVotação dos partidos e número de candidatos eleitos:\n";
    int posicao = 1;
    for (const auto& partido : partidosOrdenados) {
        int votosNominais = partido->getVotosNominais();
        int votosLegenda = partido->getVotosLegenda();
        int totalVotos = partido->getTotalVotos();
        int numEleitos = partido->getNumEleitos();

        // Pluralização das strings
        std::string votoStr = (totalVotos == 1) ? "voto" : "votos";
        std::string votoNominalStr = (votosNominais == 1) ? "nominal" : "nominais";
        std::string candidatoStr = (numEleitos == 1) ? "candidato eleito" : "candidatos eleitos";

        if (totalVotos == 0) {
            std::cout << posicao++ << " - " 
                      << partido->getSigla() << " - " 
                      << partido->getNumero() 
                      << ", 0 voto (0 " << votoNominalStr 
                      << " e 0 de legenda), 0 candidato eleito\n";
        } else {
            std::cout << posicao++ << " - "
                      << partido->getSigla() << " - "
                      << partido->getNumero() << ", "
                      << ProcessaEntrada::formataNumero(totalVotos) << " " << votoStr << " ("
                      << ProcessaEntrada::formataNumero(votosNominais) << " " << votoNominalStr
                      << " e " << ProcessaEntrada::formataNumero(votosLegenda) << " de legenda), "
                      << numEleitos << " " << candidatoStr << "\n";
        }
    }
}

void Eleicao::geraRelatorioPrimeiroUltimoPartido() {
    // Cria um vetor de smart pointers para os partidos que possuem candidatos
    std::vector<std::shared_ptr<Partido>> partidosValidos;
    for (const auto& par : partidos) {
        if (!par.second->getCandidatos().empty()) {
            partidosValidos.push_back(par.second);
        }
    }

    // Ordena os partidos pelo candidato mais votado
    std::sort(partidosValidos.begin(), partidosValidos.end(),
        [](const std::shared_ptr<Partido>& a, const std::shared_ptr<Partido>& b) {
            // Obtém os candidatos mais votados (smart pointers)
            auto c1 = a->getCandidatoMaisVotado();
            auto c2 = b->getCandidatoMaisVotado();

            // Tratamento de nulos
            if (!c1 || !c2) {
                if (!c1 && !c2)
                    return a->getNumero() < b->getNumero();
                return (c2 != nullptr);
            }
            // Comparação principal: votos decrescentes; em empate, número do partido (crescente)
            if (c1->getVotos() != c2->getVotos())
                return c1->getVotos() > c2->getVotos();
            return a->getNumero() < b->getNumero();
        });

    std::cout << "\nPrimeiro e último colocados de cada partido:\n";
    int posicao = 1;
    for (const auto& partido : partidosValidos) {
        // Ignora partidos com apenas um candidato
        if (partido->getCandidatos().size() == 1)
            continue;

        // Obtém e ordena os candidatos válidos
        std::vector<std::shared_ptr<Candidato>> candidatos = partido->getCandidatos();
        std::sort(candidatos.begin(), candidatos.end(),
            [](const std::shared_ptr<Candidato>& a, const std::shared_ptr<Candidato>& b) {
                if (a->getVotos() != b->getVotos())
                    return a->getVotos() > b->getVotos();
                return a->getDataNascimento() < b->getDataNascimento();
            });

        if (candidatos.empty())
            continue;

        auto primeiro = candidatos.front();
        auto ultimo = candidatos.back();

        std::string votoPrimeiro = (primeiro->getVotos() == 1) ? "voto" : "votos";
        std::string votoUltimo = (ultimo->getVotos() == 1) ? "voto" : "votos";

        std::cout << posicao++ << " - "
                  << partido->getSigla() << " - " 
                  << partido->getNumero() << ", "
                  << primeiro->getNomeUrna(0) << " ("
                  << primeiro->getNumero() << ", "
                  << ProcessaEntrada::formataNumero(primeiro->getVotos()) << " " << votoPrimeiro << ") / "
                  << ultimo->getNomeUrna(0) << " ("
                  << ultimo->getNumero() << ", "
                  << ProcessaEntrada::formataNumero(ultimo->getVotos()) << " " << votoUltimo << ")\n";
    }
}

void Eleicao::geraRelatorioFaixaEtaria() {
    int total = this->numEleitos;
    
    vector<int> faixas(5, 0); // [<30, 30-39, 40-49, 50-59, >=60]

    for (auto candidato : candidatosEleitos) {
        int idade = candidato->getIdade(data);
        if (idade < 30)        faixas[0]++;
        else if (idade < 40)   faixas[1]++;
        else if (idade < 50)   faixas[2]++;
        else if (idade < 60)   faixas[3]++;
        else                   faixas[4]++;
    }

    cout << "\nEleitos, por faixa etária (na data da eleição):\n";
    cout << "      Idade < 30: " << faixas[0] << " (" << ProcessaEntrada::formataPercentual(faixas[0], total) << ")\n";
    cout << "30 <= Idade < 40: " << faixas[1] << " (" << ProcessaEntrada::formataPercentual(faixas[1], total) << ")\n";
    cout << "40 <= Idade < 50: " << faixas[2] << " (" << ProcessaEntrada::formataPercentual(faixas[2], total) << ")\n";
    cout << "50 <= Idade < 60: " << faixas[3] << " (" << ProcessaEntrada::formataPercentual(faixas[3], total) << ")\n";
    cout << "60 <= Idade: " << faixas[4] << " (" << ProcessaEntrada::formataPercentual(faixas[4], total) << ")\n";
}

void Eleicao::geraRelatorioGenero() {
    int total = this->numEleitos;

    int feminino = 0;
    int masculino = 0;

    for (auto candidato : candidatosEleitos) {
        Genero genero = candidato->getGenero();
        if (genero.getCodigo() == Genero::FEMININO)  feminino++;
        else if (genero.getCodigo() == Genero::MASCULINO) masculino++;
    }

    cout << "\nEleitos, por gênero:\n";
    cout << "Feminino: " << feminino << " (" << ProcessaEntrada::formataPercentual(feminino, total) << ")\n";
    cout << "Masculino: " << masculino << " (" << ProcessaEntrada::formataPercentual(masculino, total) << ")\n";
}

void Eleicao::geraRelatorioTotalVotos() {
    int votosNominais = 0;
    for (const auto& par : candidatos) {
        votosNominais += par.second->getVotos();
    }

    int votosLegenda = 0;
    for (const auto& par : partidos) {
        votosLegenda += par.second->getVotosLegenda();
    }

    int totalVotosValidos = votosNominais + votosLegenda;

    cout << "\nTotal de votos válidos:    " << ProcessaEntrada::formataNumero(totalVotosValidos) << "\n";
    cout << "Total de votos nominais:    " << ProcessaEntrada::formataNumero(votosNominais)
         << " (" << ProcessaEntrada::formataPercentual(votosNominais, totalVotosValidos) << ")\n";
    cout << "Total de votos de legenda: " << ProcessaEntrada::formataNumero(votosLegenda)
         << " (" << ProcessaEntrada::formataPercentual(votosLegenda, totalVotosValidos) << ")\n";
}

void Eleicao::gerarRelatorios() {
    cout << "Número de vagas: " << this->candidatosEleitos.size() << endl; // Relatorio 1
    geraRelatorioVereadoresEleitos(); // Relatorio 2
    geraRelatoriosSobreMaisVotados(); // Relatorios 3, 4 e 5
    geraRelatorioVotacaoPartidos(); // Relatorio 6
    geraRelatorioPrimeiroUltimoPartido(); // Relatorio 7
    geraRelatorioFaixaEtaria(); // Relatorio 8
    geraRelatorioGenero(); // Relatorio 9
    geraRelatorioTotalVotos(); // Relatorio 10
}
