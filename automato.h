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
void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void trim(string& str, char rmv) {
    str.erase(remove(str.begin(), str.end(), rmv), str.end());
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
    trim(Alfabeto, ',');
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
        trim(item, 'q');

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
        trim(item, 'q');
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

char pegarLetra(int Estado) {
    return Estado == 0 ? 'S' : (Estado > 18 ? 'A' + Estado  : 'A' + (Estado - 1));
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
        trim(linha, ' ');

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
    limpar_terminal();
    cout << "========== Gramatica ==========\n";

    for (int i = 0; i < Tabela.size(); i++) {
        cout << pegarLetra(i) << " -> ";
        for (int j = 0; j < Tabela[i].size(); j++) {
            cout << Tabela[i][j].C << pegarLetra(Tabela[i][j].Prox);
            if (j < Tabela[i].size() - 1) cout << " | ";
        }
        if (this->ehFinal(i)) cout << " | @";
        cout << endl; 
    }
    cout << "===============================\n";
}

bool ehFinal(int Pos) {
    return find(Finais.begin(), Finais.end(), Pos) != Finais.end();
}

void conferirPalavra() {
    string palavra;
    limpar_terminal();

    cout << "======== Digite a palavra ===========\n=> ";
    cin >> palavra; 
    limparBuffer();
    cout << endl;

    trim(palavra, ' ');

    int estadoAtual = 0;
    bool rejeitada = false;
    int i = 0;

    if (palavra == "@") {
        cout << "[q0] @\n";
    }

    if(palavra != "@")
    for (; i < palavra.size(); i++) {
        cout << "[q" << estadoAtual << "] " << palavra.substr(i) << endl;

        Transicao* T = this->procurarTransicao(estadoAtual, palavra[i]);
        if (!T) {
            rejeitada = true;
            break;
        }
        estadoAtual = T->Prox;
    }

    if (!rejeitada && this->ehFinal(estadoAtual)) {
        cout << "[q" << estadoAtual << "]\n\nACEITA\n";
    } else {
        if (i == palavra.size() ) cout << "[q" << estadoAtual << "]\n";
        cout << "\nREJEITA\n";
    }
    cout << "=====================================\n";
}

    ~Automato(){}
};

#endif