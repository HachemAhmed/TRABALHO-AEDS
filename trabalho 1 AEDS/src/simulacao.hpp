#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP
#include "animal.hpp"
#include "fogo.hpp"
#include "io.hpp"

class Simulacao {
private:
    Floresta floresta;
    Animal animal;
    PropagadorFogo propagadorFogo;
    int iteracaoAtual;
    bool simulacaoEncerrada;
    std::vector<std::pair<int, int>> caminhoAnimal; 
    std::string arquivoSaida;

public:

    Simulacao(int linhas, int colunas, const std::vector<std::vector<int>>& gradeInicial, int fogoLinha, int fogoCol, const std::string& arquivoSaida);
    void inicializar();
    bool executarIteracao();
    void executarSimulacao();
    bool isSimulacaoEncerrada() const;
    void gravarEstado();
    void gravarEstatisticasFinais();
};

#endif 