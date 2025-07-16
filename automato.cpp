#include "Automato.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void trim(string& str, char rmv) {
    str.erase(remove(str.begin(), str.end(), rmv), str.end());
}

void ENTER () {
    cout << "\nPressione ENTER para voltar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    limparTerminal();
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/// @brief Tira os estados da linha recebida
///        colocando eles no vetor recebido
/// @param linha A string contendo os estados
/// @param Estados O vetor que recebera os estados
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

/// @brief Redimensiona a Tabela de acordo com a quantidade de estados na linha
/// @param linha A string contendo os estados
/// @param Tabela A Tabela do Automato a ser redimensionada
void lerEstados(const string& linha, vector<vector<Transicao>>& Tabela) {
    size_t inicio = linha.find('{');
    size_t fim = linha.find('}');
    if (inicio == string::npos || fim == string::npos) return;

    const string conteudo = linha.substr(inicio + 1, fim - inicio - 1);
    const size_t num_estados = count(conteudo.begin(), conteudo.end(), ',') + 1;
    Tabela.resize(Tabela.size() + num_estados);
}

/// @brief Le e atualiza a Tabela com uma Transicao
/// @param linha A string contendo a Transicao
/// @param Tabela A tabela do Automato a ser atualizada
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

char Automato::pegarLetra(int Estado) {
    return Estado == 0 ? 'S' : (Estado > 18 ? 'A' + Estado  : 'A' + (Estado - 1));
}

Transicao::Transicao(char c, int p){
    C = c;
    Prox = p;
}

Transicao::~Transicao(){}

Automato::Automato(const string& nomeArquivo) {
    ifstream Arq(nomeArquivo);
    if(!Arq.is_open()) throw "\nErro ao Abrir Arquivo!\n";

    string linha;
    while(getline(Arq,linha)){
        trim(linha, ' ');
        
        if (linha.find("estados") != string::npos) {
            lerEstados(linha,Tabela);
        }
        else if(linha.find("finais") != string::npos) {
            lerEstadosFinais(linha,Finais);
        }
        else if(linha.find("(") != string::npos) {
            lerTransicao(linha, Tabela);
        }
    }
}

Transicao* Automato::procurarTransicao(int E, char c) {
    for(int j = 0; j < Tabela[E].size(); j++) {
        if(Tabela[E][j].C == c) return &Tabela[E][j];
    }
    return nullptr;
}

void Automato::imprimirGramatica() {
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

bool Automato::ehFinal(int Pos) {
    return find(Finais.begin(), Finais.end(), Pos) != Finais.end();
}

void Automato::conferirPalavra() {
    string palavra;

    cout << "======== Digite a palavra ===========\n=> ";
    cin >> palavra; limparBuffer();
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

Automato::~Automato(){}