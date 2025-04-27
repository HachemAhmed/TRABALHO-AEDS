#include "fogo.hpp"

PropagadorFogo::PropagadorFogo(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    tempoQueimando.assign(linhas, std::vector<int>(colunas, 0));
    proximoTempoQueimando.assign(linhas, std::vector<int>(colunas, 0));
}

void PropagadorFogo::inicializar(const Floresta& floresta) {
    tempoQueimando.assign(linhas, std::vector<int>(colunas, 0));
    proximoTempoQueimando = tempoQueimando;
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (floresta.getCelula(i, j) == Floresta::ARVORE_EM_CHAMAS) {
                tempoQueimando[i][j] = 0; 
            }
        }
    }
}

void PropagadorFogo::propagar(Floresta& floresta) {
    proximoTempoQueimando = tempoQueimando;
    std::vector<std::vector<int>> proximaGrade(linhas, std::vector<int>(colunas));
    posicoesQueViraramFogo.clear();
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            proximaGrade[i][j] = floresta.getCelula(i, j);
        }
    }

    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (floresta.getCelula(i, j) == Floresta::ARVORE_EM_CHAMAS) {
                proximoTempoQueimando[i][j] = tempoQueimando[i][j] + 1;
                if (proximoTempoQueimando[i][j] >= 2) {
                    proximaGrade[i][j] = Floresta::ARVORE_QUEIMADA;
                    posicoesQueViraramFogo.emplace_back(i, j); 
                }

                for (int dir = 0; dir < 4; dir++) {
                    if (VENTO_ATIVADO) {
                        if ((dir == 0 && !VENTO_CIMA) ||
                            (dir == 1 && !VENTO_BAIXO) ||
                            (dir == 2 && !VENTO_ESQUERDA) ||
                            (dir == 3 && !VENTO_DIREITA))
                            continue;
                    }
                    
                    int ni = i + dr[dir], nj = j + dc[dir];
                    if (floresta.isPosicaoValida(ni, nj) &&
                        floresta.getCelula(ni, nj) == Floresta::ARVORE_SAUDAVEL) {
                        proximaGrade[ni][nj] = Floresta::ARVORE_EM_CHAMAS;
                        proximoTempoQueimando[ni][nj] = 0;  
                        posicoesQueViraramFogo.emplace_back(ni, nj); 
                    }
                }
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            floresta.setCelula(i, j, proximaGrade[i][j]);
        }
    }
    tempoQueimando = proximoTempoQueimando;
}

bool PropagadorFogo::isIncendioExtinto(const Floresta& floresta) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (floresta.getCelula(i, j) == Floresta::ARVORE_EM_CHAMAS) {
                return false;
            }
        }
    }
    return true;
}

void PropagadorFogo::iniciarFogo(int linha, int coluna, Floresta& floresta) {
    if (floresta.isPosicaoValida(linha, coluna)) {
        floresta.setCelula(linha, coluna, Floresta::ARVORE_EM_CHAMAS);
        tempoQueimando[linha][coluna] = 0; 
    }
}

const std::vector<std::pair<int, int>>& PropagadorFogo::getPosicoesQueViraramFogo() const {
    return posicoesQueViraramFogo;
}