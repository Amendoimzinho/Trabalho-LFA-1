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
        // Ant = -1;
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

class Automato {
    private:
    std::string Alfabeto;
    std::vector<int> Estados;
    std::vector<int> Finais;
    std::vector<std::vector<Letra>> Tabela;

    public:

    // Construtora vai pedir OBRIGATORIAMENTE o arquivo antes de criar
    // o Automato (pra poder iniciar a Tabela)
    Automato(const std::string& nomeArquivo) {

        // Le o Alfabeto
        // le os Estados (so o int / so a quantidade)
        // le os Finais (so o int)

        // Loop de ler Transicao
        int E; // Estado de orige da Transicao 
        char A; // Letra lida na transicao
        int Pos = Alfabeto.find_first_of(A);  // Encontra a Posicao da Letra no Alfabeto
                                            // Que vai ser o numero da Coluna daquela Letra
        Tabela[E][Pos].setC(/* Letra */); // Coloca a Letra na ... Letra
        Tabela[E][Pos].setProx(/* Destino */); // Coloca o Destino na Letra
        // fim do Loop quando acaba as transicoes
    }


    // No estado(i) ve se a letra(c)
    Letra* procurarLetra(int i, char c) {
        for(int j = 0; j < Tabela.size(); j++) {
            if(Tabela[i][j].getC() == c) return &Tabela[i][j];
        }
        return NULL;
    }

    ~Automato(){}
};
    
void conferirPalavras(Automato& Aut) {
    std::string palavra;
    // Pede e le a Palavra

    int posAtual = 0;
    Letra* L;

    for(int i = 0; i < palavra.size(); i++){
        L = Aut.procurarLetra(posAtual, palavra[i]);
        if (L != NULL && palavra[i] == L->getC()){
            posAtual = L->getProx();
            // imprime a mudanca de estado e tals
        }else {/* Msg q nao deu certo */ break;}
    }
}



#endif