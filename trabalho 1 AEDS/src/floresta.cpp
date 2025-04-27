#include "floresta.hpp"

const int Floresta::VAZIO;
const int Floresta::ARVORE_SAUDAVEL;
const int Floresta::ARVORE_EM_CHAMAS;
const int Floresta::ARVORE_QUEIMADA;
const int Floresta::AGUA;

Floresta::Floresta(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    mapa.assign(linhas, vector<int>(colunas, VAZIO));
}

bool Floresta::inicializar(const vector<vector<int>>& gradeInicial) {
    if (gradeInicial.size() != static_cast<size_t>(linhas) ||
        gradeInicial[0].size() != static_cast<size_t>(colunas)) {
        return false;
    }
    mapa = gradeInicial;
    return true;
}

int Floresta::getCelula(int linha, int coluna) const {
    if (isPosicaoValida(linha, coluna)) {
        return mapa[linha][coluna];
    }
    return -1; 
}

void Floresta::setCelula(int linha, int coluna, int valor) {
    if (isPosicaoValida(linha, coluna)) {
        mapa[linha][coluna] = valor;
    }
}

bool Floresta::isPosicaoValida(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

string Floresta::toString() const {
    stringstream ss;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            ss << mapa[i][j] << " ";
        }
        ss << "\n";
    }
    return ss.str();
}