#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include "Eleicao.hpp"

using namespace std;
namespace fs = filesystem;

void validarArgumentos(int argc, char* argv[]);
void validarArquivo(const string& caminhoArquivo, const string& tipoArquivo);

int main(int argc, char* argv[]) {
    try {
        validarArgumentos(argc, argv);

        string numeroCidadeStr = argv[1];
        string arquivoCandidatos = argv[2];
        string arquivoVotacao = argv[3];
        string dataEleicao = argv[4];

        int numeroCidade = stoi(numeroCidadeStr);
        
        Eleicao eleicao(numeroCidade, dataEleicao);
        eleicao.processarCandidatosPartidos(arquivoCandidatos);
        eleicao.processarVotos(arquivoVotacao);
        
        // definindo o locale globalmente
        locale::global(locale("pt_BR.UTF-8"));
        // definindo locale para evitar o default
        setlocale(LC_ALL, "pt_BR");

        eleicao.gerarRelatorios();

        cout.imbue(locale("C")); // para evitar memory leak

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Erro inesperado!" << endl;
        return 2;
    }
    return 0;
}

void validarArgumentos(int argc, char* argv[]) {
    vector<string> args(argv, argv + argc);
    
    if (args.size() != 5) {
        throw runtime_error(
            "Número de argumentos inválido! São esperados 4 argumentos:\n"
            "1. Número da cidade\n"
            "2. Caminho para o arquivo de candidatos\n"
            "3. Caminho para o arquivo de votação\n"
            "4. Data da eleição (dd/mm/aaaa)"
        );
    }

    validarArquivo(args[2], "Arquivo de candidatos");
    validarArquivo(args[3], "Arquivo de votação");
}

void validarArquivo(const string& caminhoArquivo, const string& tipoArquivo) {
    if (!fs::exists(caminhoArquivo)) {
        throw runtime_error(tipoArquivo + " não encontrado: " + caminhoArquivo);
    }
    if (!fs::is_regular_file(caminhoArquivo)) {
        throw runtime_error(tipoArquivo + " não é um arquivo válido: " + caminhoArquivo);
    }
}