#include "io.hpp"

void IO::logError(const std::string &filename, const std::string &errorMessage) {
    std::ofstream outFile(filename, std::ios::app);
    if (outFile) {
        outFile << "\n[ERRO] " << errorMessage << "\n";
        outFile.close();
    }
}

Arquivo IO::readInput(const std::string &filename) {
    std::ifstream in(filename);
    Arquivo data;
    if (!in) {

        std::ofstream errOut("output.dat", std::ios::trunc);
        if (errOut) {
            errOut << "ERRO: Não foi possível abrir o arquivo de entrada: " << filename << "\n";
            errOut.close();
        }
        exit(EXIT_FAILURE);
    }

    in >> data.N >> data.M >> data.fogoLinha >> data.fogoCol;
    data.forest.assign(data.N, std::vector<int>(data.M));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.M; ++j) {
            in >> data.forest[i][j];
        }
    }
    return data;
}

void IO::initOutput(const std::string &filename) {
    std::ofstream out(filename, std::ios::trunc);
    if (!out) {
        std::ofstream errOut("error_log.txt", std::ios::trunc);
        if (errOut) {
            errOut << "ERRO: Não foi possível criar o arquivo de saída: " << filename << "\n";
            errOut.close();
        }
        exit(EXIT_FAILURE);
    }
    out.close();
}

void IO::writeOutput(const std::string &filename, const Matriz &forest, int iteration) {

    std::ofstream out(filename, std::ios::app);
    if (!out) {
        exit(EXIT_FAILURE);
    }

    out << "Iteração " << iteration << ":\n";
    for (const auto &row : forest) {
        for (int cell : row) {
            out << cell << ' ';
        }
        out << '\n';
    }
    out << '\n';
}