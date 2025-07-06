#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Puxei do meu trabalho de AED
}

class Letra {
    // private:
    
    public:
    char C;
    int Prox;

    Letra(char c = '\0', int p = -1){
        C = c;
        Prox = p;
    }
    ~Letra(){}

    // char getC(){
    //     return this->C;
    // }

    // int getProx(){
    //     return this->Prox;
    // }

    // void setC(char c) {
    //     this->C = c;
    // }

    // void setProx(int p) {
    //     this->Prox = p;
    // }
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

        L.C = A;
        L.Prox = E;
        Tabela[E].emplace_back(L);

        // fim do Loop quando acaba as transicoes
    }


    // No estado(i) ve se a letra(c)
    Letra* procurarLetra(int E, char c) {
        for(int j = 0; j < Tabela[E].size(); j++) {
            if(Tabela[E][j].C == c) return &Tabela[E][j];
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
                    std::cout << Tabela[E][j].C;
                    std::cout << (E <= Tabela[E][j].Prox
                                    ? S - (E - Tabela[E][j].Prox) // Se o proximo estiver antes 
                                    : S + (E - Tabela[E][j].Prox)); // Se o proximo estiver Depois
                    std::cout << " | " << std::endl; // Arrumem isso pq vai ta bugado
            }
            if (std::find(Finais.begin(), Finais.end(), E) != Finais.end()) std::cout << "@"; // Se eh estado Final
            S++; // Aumenta o S (A++ == B)
            }
            else if(E == 0){ // Se for o primeiro (pq tem q ser S)
                std::cout << "S -> ";
                for(int j = 0; j < Tabela[E].size(); j++){
                    std::cout << Tabela[E][j].C; // A letra a ser lida
                    std::cout << (S + (E - Tabela[E][j].Prox)); // O proximo estado
                    std::cout << " | " << std::endl; // O '|' mas tem q arrumar
            }
            if (std::find(Finais.begin(), Finais.end(), E) != Finais.end()) std::cout << "@";
        }       /* ^^^ Criem uma Funcao ou uma macro pra isso? ^^^ */
    }
}
~Automato(){}
};
    
int conferirPalavras(Automato& Aut) { // A criacao do Automato vai ter q ser na main
    std::string palavra;
    // Pede e le a Palavra

    int posAtual = 0;
    Letra* L;

    for(int i = 0; i < palavra.size(); i++){
        L = Aut.procurarLetra(posAtual, palavra[i]);
        if (L != NULL && palavra[i] == L->C){
            posAtual = L->Prox;
            // imprime a mudanca de estado e tals
        }else {/* Msg q nao deu certo */ break;}
    }

    // return 0 para repetir
    return -1; // para acabar
}

#endif