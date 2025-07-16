#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <vector>
#include <string>

class Transicao {
public:
    char C;
    int Prox;
    Transicao(char c = '\0', int p = -1);
    ~Transicao();
};

class Automato {
private:
    std::vector<int> Finais;
    std::vector<std::vector<Transicao>> Tabela;

    char pegarLetra(int Estado);

public:
    Automato(const std::string& nomeArquivo);
    Transicao* procurarTransicao(int E, char c);
    void imprimirGramatica();
    bool ehFinal(int Pos);
    void conferirPalavra();
    ~Automato();
};

void limparBuffer();
void trim(std::string& str, char rmv);
void limparTerminal();

#endif 