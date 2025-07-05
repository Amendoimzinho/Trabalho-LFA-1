#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Ler as Letras
// Ler os estados

// Estados sao as Linhas
// Letras sao as Colunas

// Ultima Coluna eh a Flag de Final

// O Estado so precisa saber do seu propio Numero/Index

// A Letra Precisa saber de se char e o proximo Estado

class Letra {
    private:
    char C;
    // int Ant;
    int Prox;

    public:
    Letra(){
        C = '\0';
        Ant = -1;
        Prox = -1;
    }
    ~Letra(){}

    int getC(){
        return this->C;
    }

    // int getAnt(){
    //     return this->Ant;
    // }

    int getProx(){
        return this->Prox;
    }

    void setC(char c) {
        this->C = c;
    }

    // void setAnt(int a) {
    //     this->Ant = a;
    // }

    void setProx(int p) {
        this->Prox = p;
    }
};

int lerPalavra() {
    std::string palavra;
    // le a palavra
    for(int i = 0; i < palavra.size(); i++) {

    }
}

std::vector<std::vector<Letra>> criarMatriz_Arquivo() {
    std::string Alfabeto;
    std::vector<int> Estados; // SO O NUMERO
    std::vector<int> Finais; // SO O NUMERO
    //le o Alfabeto, Estados e os Finais

    std::vector<std::vector<Letra>> Tabela(Estados.size(), std::vector<Letra>(Alfabeto.size() + 1));

    // Loop de ler Transicao
    int E; // Estado de orige da Transicao 
    char A; // Letra lida na transicao
    int Pos = Alfabeto.find_first_of(A);  // Encontra a Posicao da Letra no Alfabeto
                                          // Que vai ser o numero da Coluna daquela Letra
    Tabela[E][Pos].setC(/* Letra */); // Coloca a Letra na ... Letra
    Tabela[E][Pos].setProx(/* Destino */); // Coloca o Destino na Letra
    // fim do Loop quando acaba as transicoes

    return Tabela;
}
#endif