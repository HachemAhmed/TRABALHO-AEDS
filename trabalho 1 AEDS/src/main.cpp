#include "simulacao.hpp"
#include "io.hpp"
#include <exception>

int main() {
    std::string arquivoEntrada = "input.dat";
    std::string arquivoSaida = "output.dat";
    
    try {
        IO::initOutput(arquivoSaida);
        Arquivo dados;
        try {
            dados = IO::readInput(arquivoEntrada);
        } catch (const std::exception& e) {
            return EXIT_FAILURE;
        }
        
        try {
            Simulacao simulacao(dados.N, dados.M, dados.forest, dados.fogoLinha, dados.fogoCol, arquivoSaida);
            simulacao.inicializar();
            simulacao.executarSimulacao();
        } catch (const std::exception& e) {
            IO::logError(arquivoSaida, std::string("Erro durante a simulação: ") + e.what());
            return EXIT_FAILURE;
        }
        
    } catch (const std::exception& e) {
        try {
            IO::logError(arquivoSaida, std::string("Erro não tratado: ") + e.what());
        } catch (...) {
        }
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}