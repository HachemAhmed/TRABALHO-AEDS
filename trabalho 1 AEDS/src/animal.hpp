#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "floresta.hpp"
#include <utility>
#include <random>  
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Animal {
private:
    int linha, coluna;       
    int passos;              
    int vezesAgua;            
    int iteracaoBloqueio;        
    int contadorPermanencia;      

public:
    Animal();
    bool inicializar(const Floresta &f);
    bool mover(Floresta &f, int iteracao);
    bool estaEmChamas(const Floresta &f) const;
    void setIteracaoBloqueio(int iteracao);
    int getLinha() const;
    int getColuna() const;
    int getPassos() const;
    int getVezesAgua() const;
    int getIteracaoBloqueio() const;
};
#endif 