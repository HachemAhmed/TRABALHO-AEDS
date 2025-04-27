#include "animal.hpp"

Animal::Animal() : linha(-1), coluna(-1), passos(0), vezesAgua(0), iteracaoBloqueio(-1), contadorPermanencia(0)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

bool Animal::inicializar(const Floresta &f) {
    std::vector<std::pair<int, int>> posicoesValidas;
    
    for (int i = 0; i < f.getLinhas(); ++i) {
        for (int j = 0; j < f.getColunas(); ++j) {
            int estadoCelula = f.getCelula(i, j);
            if (estadoCelula == Floresta::VAZIO || 
                estadoCelula == Floresta::ARVORE_SAUDAVEL || 
                estadoCelula == Floresta::AGUA) {
                posicoesValidas.emplace_back(i, j);
            }
        }
    }
    
    if (posicoesValidas.empty()) {
        return false;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<size_t> dist(0, posicoesValidas.size() - 1);
    
    size_t indiceAleatorio = dist(g);
    std::tie(linha, coluna) = posicoesValidas[indiceAleatorio];
    
    contadorPermanencia = 0;
    
    if (f.getCelula(linha, coluna) == Floresta::AGUA) {

        vezesAgua++; 
    }
    
    return true;
}

bool Animal::mover(Floresta &f, int iteracao) {
    static const int dr[4] = {-1,1,0,0};
    static const int dc[4] = {0,0,-1,1};

    std::vector<std::pair<int,int>> agua, intermediarios, queimados;

    for (int d = 0; d < 4; ++d) {
        int ni = linha + dr[d], nj = coluna + dc[d];
        if (!f.isPosicaoValida(ni,nj)) continue;
        int estado = f.getCelula(ni,nj);
        if (estado == Floresta::AGUA) {
            agua.emplace_back(ni,nj);
        } else if (estado == Floresta::VAZIO || estado == Floresta::ARVORE_SAUDAVEL) {
            intermediarios.emplace_back(ni,nj);
        } else if (estado == Floresta::ARVORE_QUEIMADA) {
            queimados.emplace_back(ni,nj);
        }
    }

    int novaL=-1, novaC=-1;

    std::random_device rd;
    std::mt19937 g(rd());

    if (!agua.empty()) {
        std::shuffle(agua.begin(), agua.end(), g);
        std::tie(novaL,novaC) = agua.front();
        f.setCelula(novaL,novaC, Floresta::VAZIO);
        for (int d = 0; d < 4; ++d) {
            int ai = novaL + dr[d], aj = novaC + dc[d];
            if (f.isPosicaoValida(ai,aj)) {
                f.setCelula(ai,aj, Floresta::ARVORE_SAUDAVEL);
            }
        }
        vezesAgua++;
        contadorPermanencia = 0;
    }
    else if (!intermediarios.empty()) {
        std::shuffle(intermediarios.begin(), intermediarios.end(), g);
        std::tie(novaL,novaC) = intermediarios.front();
        contadorPermanencia = 0;
    }
    else if (!queimados.empty()) {
        std::shuffle(queimados.begin(), queimados.end(), g);
        std::tie(novaL,novaC) = queimados.front();
        contadorPermanencia = 0;
    }
    if (novaL >= 0) {
        linha = novaL;
        coluna = novaC;
        passos++;
        return true;
    }
    int atual = f.getCelula(linha,coluna);

    if (atual == Floresta::VAZIO && contadorPermanencia < 3) {
        contadorPermanencia++;
        return true;
    }

    if (iteracaoBloqueio < 0) 
        iteracaoBloqueio = iteracao;
    return false;
}

bool Animal::estaEmChamas(const Floresta &f) const {
    return f.getCelula(linha,coluna) == Floresta::ARVORE_EM_CHAMAS;
}

void Animal::setIteracaoBloqueio(int iteracao) {
    iteracaoBloqueio = iteracao;
}
int Animal::getLinha() const { 
    return linha; 
}

int Animal::getColuna() const { 
    return coluna; 
}

int Animal::getPassos() const { 
    return passos;
}

int Animal::getVezesAgua() const {
    return vezesAgua; 
}

int Animal::getIteracaoBloqueio() const { 
    return iteracaoBloqueio; 
}