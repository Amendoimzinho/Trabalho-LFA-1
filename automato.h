#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <string>
#include <vector>


class Transicao {
    private:
    char C; // O que eh para ser Escrito
    int Prox; // O Estado de Entrada

    public:
    Transicao(){
        C = '\0';
        Prox = 0;
    }
    ~Transicao(){}

    char getC(){
        return this->C;
    }
    int getProx(){
        return this->Prox;
    }
};

class Estado {
    protected:
    int Num; // Numero do Estado Atual
    bool EhFinal; // Flag para se eh Final

    std::vector<Transicao> Transicoes; // Vetor de Transicoes Saindo desse Estado
    public:
    Estado(){
        Num = -1;
        EhFinal = false;
    }
    ~Estado(){}

    void addTrancicao(Transicao& t){
        this->Transicoes.emplace_back(t);
    }

    int fazerTransicao(char c){
        for(int i = 0; i <= Transicoes.size(); i++)
            if(Transicoes[i].getC() == c) return Transicoes[i].getProx();
    return -1;
    }
};

class Automato {
    private:
    std::string Alfabeto; // Alfabeto do Automato
    std::vector<Estado> Estados; // Vetor de Estados
    public:
    Automato(){}
    ~Automato(){};
};

#endif