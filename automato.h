#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Puxei do meu trabalho de AED
}

class Transicao { 
    public:
    char C;
    int Prox;

    Transicao(char c = '\0', int p = -1){
        C = c;
        Prox = p;
    }
    ~Transicao(){}
};


void lerAlfabeto(const string& linha, string& Alfabeto) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');

    if (inicio == string::npos || fim == string::npos) return;

    Alfabeto = linha.substr(inicio + 1, fim - inicio - 1);
    Alfabeto.erase(remove(Alfabeto.begin(), Alfabeto.end(), ','), Alfabeto.end());
}

void lerEstados(const string& linha, vector<int>& Estados) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');

    if (inicio == string::npos || fim == string::npos) return;

    stringstream ss(linha.substr(inicio + 1, fim - inicio - 1));

    string item;

    while (getline(ss, item, ',')) {
        item.erase(remove(item.begin(), item.end(), 'q'), item.end());
        if (!item.empty()) {
            Estados.push_back(std::stoi(item));
        }
    }
}

void lerEstados(const string& linha, vector<int>& Estados, vector<vector<Transicao>>& Tabela) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');

    if (inicio == string::npos || fim == string::npos) return;

    stringstream ss(linha.substr(inicio + 1, fim - inicio - 1));

    string item;

    while (getline(ss, item, ',')) {
        item.erase(remove(item.begin(), item.end(), 'q'), item.end());
        if (!item.empty()) {
            Estados.push_back(std::stoi(item));
            Tabela.resize(Tabela.size() + 1);
        }
    }
}

void lerTransicao(const string& linha, vector<vector<Transicao>>& Tabela) {
    size_t inicioEstado = linha.find('q') + 1;
    size_t fimEstado = linha.find(',');

    int estadoAtual = stoi(linha.substr(inicioEstado, fimEstado - inicioEstado));

    char simbolo = linha[fimEstado + 1];

    size_t iniProx = linha.rfind('q') + 1;

    int proxEstado = stoi(linha.substr(iniProx));

    Transicao T(simbolo,proxEstado);

    Tabela[estadoAtual].emplace_back(T);
}
    

class Automato {
    private:
    string Alfabeto;
    vector<int> Estados;
    vector<int> Finais;
    vector<vector<Transicao>> Tabela;

    public:

    // Construtora vai pedir OBRIGATORIAMENTE o arquivo antes de criar
    // o Automato (pra poder iniciar a Tabela)
    Automato(const string& nomeArquivo) {

        ifstream Arq(nomeArquivo);
        if(!Arq.is_open()) throw "\nErro ao Abrir Arquivo!\n";

        string linha;
        while(getline(Arq,linha)){
            linha.erase(remove(linha.begin(), linha.end(), ' '), linha.end());
            if(linha.find("alfabeto") != string::npos) {
                lerAlfabeto(linha, Alfabeto);
            }
            else if (linha.find("estados") != string::npos) {
                lerEstados(linha,Estados,Tabela);
            }
            else if(linha.find("finais") != string::npos) {
                lerEstados(linha,Finais);
            }
            else if(linha.find("(") != string::npos) {
                lerTransicao(linha, Tabela);
            }
        }
    }


    // No estado(i) ve se a Transicao(c)
    Transicao* procurarTransicao(int E, char c) {
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
                cout << S << " -> ";
                for(int j = 0; j < Tabela[E].size(); j++){  
                    cout << Tabela[E][j].C;
                    cout << (E <= Tabela[E][j].Prox
                                    ? S - (E - Tabela[E][j].Prox) // Se o proximo estiver antes 
                                    : S + (E - Tabela[E][j].Prox)); // Se o proximo estiver Depois
                    cout << " | " << endl; // Arrumem isso pq vai ta bugado
            }
            if (find(Finais.begin(), Finais.end(), E) != Finais.end()) cout << "@"; // Se eh estado Final
            S++; // Aumenta o S (A++ == B)
            }
            else if(E == 0){ // Se for o primeiro (pq tem q ser S)
                cout << "S -> ";
                for(int j = 0; j < Tabela[E].size(); j++){
                    cout << Tabela[E][j].C; // A Transicao a ser lida
                    cout << (S + (E - Tabela[E][j].Prox)); // O proximo estado
                    cout << " | " << endl; // O '|' mas tem q arrumar
            }
            if (find(Finais.begin(), Finais.end(), E) != Finais.end()) cout << "@";
            }       /* ^^^ Criem uma Funcao ou uma macro pra isso? ^^^ */
        }
    }

    int conferirPalavra() {
    string palavra;
    cout << "\nDigite a palavra para ser lida\n\n=>";
    cin >> palavra; limparBuffer();

    int estadoAtual = 0;
    bool rejeitada = false;

    for(int i = 0; i < palavra.size(); i++) {
        Transicao* L = procurarTransicao(estadoAtual, palavra[i]);
        cout << "[q" << estadoAtual << "] " << palavra.substr(i) << endl;

        if(!L) {
            rejeitada = true;
            break;
        }
        estadoAtual = L->Prox;
    }

    // Verifica aceitação após processar todos os caracteres
    if(!rejeitada && find(Finais.begin(), Finais.end(), estadoAtual) != Finais.end()) {
        cout << "ACEITA\n";
    } else {
        cout << "REJEITA\n";
    }

    return 0;
}

    ~Automato(){}
};

#endif