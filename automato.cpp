#include "Automato.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora todos os 'char' restantes ate o prox '\n'
}

void trim(string& str, char rmv) {
    str.erase(remove(str.begin(), str.end(), rmv), str.end()); // Tira TODOS 'rmv' e joga o resto para frente depois d
}

void ENTER () {
    cout << "\nPressione ENTER para voltar...";
    limparBuffer(); // Prescisa de um '\n' para continuar
    limparTerminal(); // Limpa o Terminal
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls"); // 'cls' para windows
    #else
        system("clear"); // 'clear' para os outros SO
    #endif
}

/// @brief Tira os estados da linha recebida
///        colocando eles no vetor recebido
/// @param linha A string contendo os estados
/// @param Estados O vetor que recebera os estados
void lerEstadosFinais(const string& linha, vector<int>& Estados) {
    size_t inicio = linha.find('{'); // Procura o inicio 
    size_t fim = linha.find('}');    // e o fim para pegar a substring  

    if (inicio == string::npos || fim == string::npos) return; // Se der erro retorna

    stringstream ss(linha.substr(inicio + 1, fim - inicio - 1)); // Cria a stringstream com a substring encontrada

    string item;

    while (getline(ss, item, ',')) { // Pega a cada elemento ate a proxima ',' e coloca em 'item'
        trim(item, 'q'); // Tira os 'q'
        if (!item.empty()) { // Se nao der erro 
            Estados.push_back(stoi(item)); // Adiciona o novo estado
        }
    }
}

/// @brief Redimensiona a Tabela de acordo com a quantidade de estados na linha
/// @param linha A string contendo os estados
/// @param Tabela A Tabela do Automato a ser redimensionada
void lerEstados(const string& linha, vector<vector<Transicao>>& Tabela) {
    size_t inicio = linha.find('{'); // Procura o inicio
    size_t fim = linha.find('}');    // e o fim para pegar a substring

    if (inicio == string::npos || fim == string::npos) return; // Se der erro retorna

    stringstream ss(linha.substr(inicio + 1, fim - inicio - 1)); // Cria a stringstream com a substring encontrada
    string item; // Uma string auxiliar
    size_t qntEstados = 0; // Contador de Estados

    while (getline(ss, item, ',')) { // Pega cada "entre virgulas"
        trim(item, 'q');  // Remove os 'q' da string
        trim(item, ' ');  // Remove espaços
        
        if (!item.empty()) { // Se nao der erro 
            qntEstados++; // Aumenta o contador
        }
    }

    Tabela.resize(Tabela.size() + qntEstados); // Redimenciona Tabela com a quantidade de estados 
}

/// @brief Le e atualiza a Tabela com uma Transicao
/// @param linha A string contendo a Transicao
/// @param Tabela A tabela do Automato a ser atualizada
void lerTransicao(const string& linha, vector<vector<Transicao>>& Tabela) {
     // Encontra o numero do estado ATUAL
    size_t inicioEstado = linha.find('q') + 1;
    size_t fimEstado = linha.find(',');
    int estadoAtual = stoi(linha.substr(inicioEstado, fimEstado - inicioEstado));

    char simbolo = linha[fimEstado + 1]; // Como nao precisa se procupar com ' '

    size_t iniProx = linha.rfind('q') + 1; // Encontra o 'q' para o Proximo estado
    int proxEstado = stoi(linha.substr(iniProx)); // Como o numero sempre vai ser o resto

    Transicao T(simbolo,proxEstado); // Cria a Transicao

    Tabela[estadoAtual].emplace_back(T); // Coloca no estado de origem
}

char Automato::pegarLetra(int Estado) {
    return Estado == 0 ? 'S' : (Estado > 18 ? 'A' + Estado  : 'A' + (Estado - 1)); // Caucula a letra que o estado representa
}

Transicao::Transicao(char chr, int prx){
    this->C = chr;
    this->Prox = prx;
}

Transicao::~Transicao(){}

Automato::Automato(const string& nomeArquivo) {
    ifstream Arq(nomeArquivo); // Abre o arquivo para leitura
    if(!Arq.is_open()) throw "\nErro ao Abrir Arquivo!\n";

    string linha;
    while(getline(Arq,linha)){ // Para cada linha do arquivo
        trim(linha, ' '); // Limpa os ' '
        
        if (linha.find("estados") != string::npos) { // Se tiver estados
            lerEstados(linha,Tabela);
        }
        else if(linha.find("finais") != string::npos) { // Se tiver finais
            lerEstadosFinais(linha,Finais);
        }
        else if(linha.find("(") != string::npos) { // Se for uma transicao
            lerTransicao(linha, Tabela);
        }
    }
}

Transicao* Automato::procurarTransicao(int E, char c) {
    for(int j = 0; j < Tabela[E].size(); j++) { // Para cada Transicao no estado
        if(Tabela[E][j].C == c) return &Tabela[E][j]; // Se encontrar a Transicao retorna o ponteiro
    }
    return nullptr; // Senao retorna NULL
}

void Automato::imprimirGramatica() {
    cout << "========== Gramatica ==========\n";

    for (int i = 0; i < Tabela.size(); i++) { // Para cada estado
        cout << pegarLetra(i) << " -> "; // Imprime o estado atual
        for (int j = 0; j < Tabela[i].size(); j++) { // Para cada Transicao no estado
            cout << Tabela[i][j].C << pegarLetra(Tabela[i][j].Prox); // Imprime a Transicao
            if (j < Tabela[i].size() - 1) cout << " | "; // Se ainda tiver Transicoes imprime o '|'
        }
        if (this->ehFinal(i)) cout << (Tabela[i].size() ? " | @" : "@"); // Se for um estado final adiciona a transicao final
        cout << endl; 
    }
    cout << "===============================\n";
}

bool Automato::ehFinal(int Pos) {
    return find(Finais.begin(), Finais.end(), Pos) != Finais.end(); // retorna se encontrar 'Pos' em 'Finais'
}

void Automato::conferirPalavra() {
    cout << "======== Digite a palavra ===========\n=> ";
    // Le a palavra
    string palavra;
    cin >> palavra; limparBuffer();
    cout << endl;
    trim(palavra, ' ');

    int estadoAtual = 0;
    bool rejeitada = false;
    int i = 0;

    // Se a palavra for a palavra vazia
    if (palavra == "@") {
        cout << "[q0] @\n";
    }

    if(palavra != "@")
    for (; i < palavra.size(); i++) { // Para cada letra
        cout << "[q" << estadoAtual << "] " << palavra.substr(i) << endl; // Imprime a situacao atual

        Transicao* T = this->procurarTransicao(estadoAtual, palavra[i]); // Procura a transicao

        if (!T) { // Se nao encontrar rejeita
            rejeitada = true;
            break;
        }

        estadoAtual = T->Prox; // Senao continua
    }

    if (!rejeitada && this->ehFinal(estadoAtual)) { // Se leu tudo e o estado eh final ACEITA
        cout << "[q" << estadoAtual << "]\n\nACEITA\n";
    } else { // Senao REJEITA
        if (i == palavra.size() ) cout << "[q" << estadoAtual << "]\n";
        cout << "\nREJEITA\n";
    }
    cout << "=====================================\n";
}

Automato::~Automato(){}