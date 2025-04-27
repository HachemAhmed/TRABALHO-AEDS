#ifndef FOGO_HPP
#define FOGO_HPP
#include "floresta.hpp"

class PropagadorFogo {
private:

    std::vector<std::vector<int>> tempoQueimando;
    std::vector<std::vector<int>> proximoTempoQueimando;
    std::vector<std::pair<int, int>> posicoesQueViraramFogo; 
    int linhas;
    int colunas;
    
public:
    PropagadorFogo(int linhas, int colunas);
    void inicializar(const Floresta& floresta);
    void propagar(Floresta& floresta);
    bool isIncendioExtinto(const Floresta& floresta) const;
    void iniciarFogo(int linha, int coluna, Floresta& floresta);
    const std::vector<std::pair<int, int>>& getPosicoesQueViraramFogo() const;
};

#endif 