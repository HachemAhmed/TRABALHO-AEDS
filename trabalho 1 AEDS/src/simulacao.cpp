#include "simulacao.hpp"

Simulacao::Simulacao(int linhas, int colunas, const std::vector<std::vector<int>>& gradeInicial, 
                     int fogoLinha, int fogoCol, const std::string& arquivoSaida)
    : floresta(linhas, colunas), 
      propagadorFogo(linhas, colunas),
      iteracaoAtual(0), 
      simulacaoEncerrada(false), 
      arquivoSaida(arquivoSaida) {
    
    if (!floresta.inicializar(gradeInicial)) {
        IO::logError(arquivoSaida, "Erro ao inicializar a floresta. Dimensões incompatíveis.");
        simulacaoEncerrada = true;
        return;
    }
    propagadorFogo.inicializar(floresta);
    
    if (!floresta.isPosicaoValida(fogoLinha, fogoCol)) {
        IO::logError(arquivoSaida, "Posição inicial do fogo inválida: " + 
                   std::to_string(fogoLinha) + "," + std::to_string(fogoCol));
        simulacaoEncerrada = true;
        return;
    }
    propagadorFogo.iniciarFogo(fogoLinha, fogoCol, floresta);
    
    if (!animal.inicializar(floresta)) {
        IO::logError(arquivoSaida, "Erro: não foi possível encontrar uma posição segura para o animal.");
        simulacaoEncerrada = true;
        return;
    }
    
    caminhoAnimal.emplace_back(animal.getLinha(), animal.getColuna());
    IO::initOutput(arquivoSaida);
}

void Simulacao::inicializar() {

    iteracaoAtual = 0;
    simulacaoEncerrada = false;
    
    if (floresta.getCelula(animal.getLinha(), animal.getColuna()) == Floresta::AGUA) {
        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};

        floresta.setCelula(animal.getLinha(), animal.getColuna(), Floresta::VAZIO);
        
        for (int d = 0; d < 4; ++d) {
            int ni = animal.getLinha() + dr[d];
            int nj = animal.getColuna() + dc[d];
            if (floresta.isPosicaoValida(ni, nj)) {
                floresta.setCelula(ni, nj, Floresta::ARVORE_SAUDAVEL);
            }
        }
    }

    gravarEstado();
}

bool Simulacao::executarIteracao() {
    if (simulacaoEncerrada) {
        return false;
    }
    
    iteracaoAtual++;
    
    bool animalVivo = true;

    if (animal.getIteracaoBloqueio() < 0) {
        animalVivo = animal.mover(floresta, iteracaoAtual);
        
        if (animalVivo) {
            caminhoAnimal.emplace_back(animal.getLinha(), animal.getColuna());
        }
    }

    propagadorFogo.propagar(floresta);
    if (animalVivo && animal.getIteracaoBloqueio() < 0 && animal.estaEmChamas(floresta)) {
        animalVivo = animal.mover(floresta, iteracaoAtual);
        if (animalVivo) {
            caminhoAnimal.emplace_back(animal.getLinha(), animal.getColuna());
        }
    }
    
    if (!animalVivo && animal.getIteracaoBloqueio() < 0) {
        animal.setIteracaoBloqueio(iteracaoAtual);
    }
    gravarEstado();
    
    if (propagadorFogo.isIncendioExtinto(floresta)) {
        simulacaoEncerrada = true;
    } else if (iteracaoAtual >= K) {
        simulacaoEncerrada = true;
    }
    
    return !simulacaoEncerrada;
}

void Simulacao::executarSimulacao() {
    
    while (!simulacaoEncerrada) {
        executarIteracao();
    }
    gravarEstatisticasFinais();
}

bool Simulacao::isSimulacaoEncerrada() const {
    return simulacaoEncerrada;
}

void Simulacao::gravarEstado() {
    std::vector<std::vector<int>> matriz(
        floresta.getLinhas(),
        std::vector<int>(floresta.getColunas())
    );
    for (int i = 0; i < floresta.getLinhas(); ++i)
        for (int j = 0; j < floresta.getColunas(); ++j)
            matriz[i][j] = floresta.getCelula(i, j);
    
    std::ofstream out(arquivoSaida, std::ios::app);
    if (!out) {
        return; 
    }
    
    out << "Iteração " << iteracaoAtual << ":\n";

    for (int i = 0; i < floresta.getLinhas(); i++) {
        for (int j = 0; j < floresta.getColunas(); j++) {
            out << matriz[i][j] << " ";
        }
        out << "\n";
    }
    out << "\n"; 
    out.close();
}

void Simulacao::gravarEstatisticasFinais() {
    std::ofstream out(arquivoSaida, std::ios::app);
    if (!out) {
        return; 
    }
    
    out << "\nDADOS FINAIS: \n";
    out << "Total de iterações: " << iteracaoAtual << "\n";
    out << "Total de passos do animal: " << animal.getPassos() << "\n";
    out << "Vezes que o animal encontrou água: " << animal.getVezesAgua() << "\n";
    
    if (animal.getIteracaoBloqueio() > 0) {
        out << "O animal foi atingido pelo fogo na iteração " << animal.getIteracaoBloqueio() << "\n";
    } else {
        out << "O animal sobreviveu até o fim da simulação\n";
    }
    
    out << "\nCaminho percorrido pelo animal:\n";
    for (size_t i = 0; i < caminhoAnimal.size(); i++) {
        out << "Passo " << i << ": (" << caminhoAnimal[i].first << "," << caminhoAnimal[i].second << ")\n";
    }
    out.close();
}