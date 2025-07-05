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
    Letra(char c = '\0', int p = -1){
        C = c;
        // Ant = -1;
        Prox = p;
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
        Letra L;

        L.setC(A);
        L.setProx(E);
        Tabela[E].emplace_back(L);

        // fim do Loop quando acaba as transicoes
    }


    // No estado(i) ve se a letra(c)
    Letra* procurarLetra(int E, char c) {
        for(int j = 0; j < Tabela[E].size(); j++) {
            if(Tabela[E][j].getC() == c) return &Tabela[E][j];
        }
        return NULL;
    }

    void imprimirGramatica() {
        char S = 'A'; // Como vai de A -> B -> C
        for(int E = 0; E < Tabela.size(); E++){
            if(E != 0){
                if (S = 'S') S++; // Se S for 'S'
                std::cout << S << " -> ";
                for(int j = 0; j < Tabela[E].size(); j++){  
                    std::cout << Tabela[E][j].getC();
                    std::cout << (E <= Tabela[E][j].getProx()
                                    ? S - (E - Tabela[E][j].getProx()) // Se o proximo estiver antes 
                                    : S + (E - Tabela[E][j].getProx())); // Se o proximo estiver Depois
                    std::cout << " | " << std::endl; // Arrumem isso pq vai ta bugado
            }
            if (std::find(Finais.begin(), Finais.end(), E) != Finais.end()) std::cout << "@";
            S++;
            }
            else if(E == 0){
                std::cout << "S -> ";
                for(int j = 0; j < Tabela[E].size(); j++){
                    std::cout << Tabela[E][j].getC();
                    std::cout << (S + (E - Tabela[E][j].getProx()));
                    std::cout << " | " << std::endl;
            }
        }
    }
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