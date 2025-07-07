#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

// Limpa o buffer de entrada
// Pré:  Nenhuma
// Pós:  Buffer stdin vazio até a próxima linha
void limparBuffer();
void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Limpa o Terminal
// Pré:  Nenhuma
// Pós:  Terminal limpo
void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

class Transicao { 
    public:
    char C;
    int Prox;

// Construtora de Transicao
// Pré:  Nenhuma
// Pós:  Transicao construida
    Transicao(char c = '\0', int p = -1){
        C = c;
        Prox = p;
    }
    ~Transicao(){}
};

// Tira o alfabeto de uma linha
// Pré: 'linha' string valida
//      'Alfabeto' string valida para ser alterada
// Pós:  'Alfabeto' contem o alfabeto encontrado em 'linha'
void lerAlfabeto(const string& linha, string& Alfabeto) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');

    if (inicio == string::npos || fim == string::npos) return;

    Alfabeto = linha.substr(inicio + 1, fim - inicio - 1);
    Alfabeto.erase(remove(Alfabeto.begin(), Alfabeto.end(), ','), Alfabeto.end());
}

// Tira os Estados Finais de uma linha
// Pré: 'linha' string valida
//      'Estados' um vetor valido para ser alterado
// Pós: 'Estados' contem os estados encontrados em 'linha'
void lerEstadosFinais(const string& linha, vector<int>& Estados) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');

    if (inicio == string::npos || fim == string::npos) return;

    stringstream ss(linha.substr(inicio + 1, fim - inicio - 1));

    string item;

    while (getline(ss, item, ',')) {
        item.erase(remove(item.begin(), item.end(), 'q'), item.end());
        if (!item.empty()) {
            Estados.push_back(stoi(item));
        }
    }
}

// Tira os Estados de uma linha
// Pré: 'linha' string valida
//      'Estados' um vetor valido para ser alterado
//      'Tabela' um vetor valido para ser alterado
// Pós: 'Estados' contem os estados encontrados em 'linha'
//      'Tabela' vai ter o tamanho correto de estados
void lerEstados(const string& linha, vector<int>& Estados, vector<vector<Transicao>>& Tabela) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');

    if (inicio == string::npos || fim == string::npos) return;

    stringstream ss(linha.substr(inicio + 1, fim - inicio - 1));

    string item;

    while (getline(ss, item, ',')) {
        item.erase(remove(item.begin(), item.end(), 'q'), item.end());
        if (!item.empty()) {
            Estados.push_back(stoi(item));
            Tabela.resize(Tabela.size() + 1);
        }
    }
}

// Tira a Transicao de uma linha
// Pré: 'linha' string valida
//      'Tabela' um vetor valido para ser alterado
// Pós: 'Tabela' sera atualizada com, a transicao encontrada em 'linha'
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

// Construtor de Automato
// Pré: 'nomeArquivo' eh um nome de um arquivo .txt valido
// Pós: informacoes de 'nomeArquivo' dentro do Automato construido
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
                lerEstadosFinais(linha,Finais);
            }
            else if(linha.find("(") != string::npos) {
                lerTransicao(linha, Tabela);
            }
        }
    }


// Encontra a transicao que contem 'c' no estado 'E'
// Pré: 'E' um indice valido de 'Tabela'
// Pós: retorna o ponteiro para a Transicao encontrada
//      ou nullptr se nao encontrar
    Transicao* procurarTransicao(int E, char c) {
        for(int j = 0; j < Tabela[E].size(); j++) {
            if(Tabela[E][j].C == c) return &Tabela[E][j];
        }
        return nullptr;
    }

// Imprime a Gramatica do Automato
// Pré: Automato corretamete construido
// Pós: Impresso no Terminal a Gramatica do Automato
 void imprimirGramatica() {
    char S = 'A'; // Começa em 'A' (B, C, D...)
    limpar_terminal();
    cout << "========== Gramatica ==========\n";
    for(int E = 0; E < Tabela.size(); E++) {
        if(E != 0) {
            if (S == 'S') S++; // Evita conflito com 'S' inicial
            cout << S << " -> ";
            for(int j = 0; j < Tabela[E].size(); j++) {  
                if(j > 0) cout << " | ";
                cout << Tabela[E][j].C;
                cout << (char)((S - (E - Tabela[E][j].Prox)) == '@' ? 'S' : (S - (E - Tabela[E][j].Prox)));
            }
            if (find(Finais.begin(), Finais.end(), E) != Finais.end()) {
                if(Tabela[E].size() > 0) cout << " | ";
                cout << "@";
            }
            S++;
            cout << endl;
        } 
        else if(E == 0) {
            cout << "S -> ";
            for(int j = 0; j < Tabela[E].size(); j++) {  
                if(j > 0) cout << " | ";
                cout << Tabela[E][j].C;
                cout << (char)(S - (E - Tabela[E][j].Prox) - 1);
            }
             if (find(Finais.begin(), Finais.end(), E) != Finais.end()) {
                if(Tabela[E].size() > 0) cout << " | ";
                cout << "@";
            }
            cout << endl;
        }
    }
    cout << "===============================\n";
}

// Pede e confere se uma palavra eh aceita pelo Automato
// Pré: Automato corretamete construido
// Pós: Palavra conferida pelo Terminal
int conferirPalavra() {
    string palavra;
    limpar_terminal();
    cout << "======== Digite a palavra ===========\n"
            "=> ";
    cin >> palavra; limparBuffer();
    palavra.erase(remove(palavra.begin(), palavra.end(), ' '), palavra.end());

    int estadoAtual = 0;
    bool rejeitada = false;
    int i = 0;

    for(;; i++) {
        cout << "[q" << estadoAtual << "] ";
        if(i >= palavra.size()) break;
        Transicao* L = procurarTransicao(estadoAtual, palavra[i]);

        if(!L && !(palavra.size() == 1 && palavra[0] == '@')) {
            rejeitada = true;
            break;
        }
        if ((palavra.size() == 1 && palavra[0] == '@')) {cout << "@\n[q0]";break;}
        cout << palavra.substr(i) << endl;

        estadoAtual = L->Prox;
    }

    if(!rejeitada && find(Finais.begin(), Finais.end(), estadoAtual) != Finais.end()) {
        cout << "\nACEITA\n";
    } else {
        cout << palavra.substr(i) << endl <<
                "REJEITA\n";
    }
    cout << "=====================================\n";
    return 0;
}

    ~Automato(){}
};

#endif