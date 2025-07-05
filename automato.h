#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <string>
#include <vector>

class Transicao {
    protected:
    std::string AEscrever; // O que eh para ser Escrito
    int Ant; // O Estado de Saida
    int Prox; // O Estado de Entrada

    public:
    Transicao(){
        Ant = 0;
        Prox = 0;
    }
};

class Estado {
    protected:
    int Num; // Numero do Estado Atual
    int EhFinal; // Flag para se eh Final

    std::vector<Transicao> Transicoes; // Vetor de Transicoes Saindo desse Estado
    public:
    Estado(){
        Num = -1;
        EhFinal = 0;
    }
};

class Automato {
    private:
    std::string Alfabeto; // Alfabeto do Automato
    std::vector<int> Estados; // Vetor de Estados
    public:
    Automato(){}
    ~Automato(){};
};

#endif