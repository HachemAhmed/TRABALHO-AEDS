#ifndef FLORESTA_HPP
#define FLORESTA_HPP
#include "config.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Floresta {
private:
    int linhas;
    int colunas;
    vector<vector<int>> mapa;
    
public:

    static const int VAZIO = 0;
    static const int ARVORE_SAUDAVEL = 1;
    static const int ARVORE_EM_CHAMAS = 2;
    static const int ARVORE_QUEIMADA = 3;
    static const int AGUA = 4;

    Floresta(int linhas, int colunas);
    bool inicializar(const vector<vector<int>>& gradeInicial);
    int getCelula(int linha, int coluna) const;
    void setCelula(int linha, int coluna, int valor);
    bool isPosicaoValida(int linha, int coluna) const;
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    string toString() const;
};

#endif