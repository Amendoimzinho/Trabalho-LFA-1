#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "automato.h"

using namespace std;

// Pede Enter para o User
// Pré: nenhuma
// Pós: pede o Enter
void ENTER () {
    cout << "\nPressione ENTER para voltar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    limparTerminal();
}

// Confere se um Arquivo existe
// Pré: 'nomeArquivo' eh uma string valida
// Pós: retorna se o arquivo existe ou nao;
bool arquivoExiste(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    return arquivo.good();
}

int abrirMenu(Automato& Aut) {
    int op;
    cout << "========== Menu ==========\n" 
            " 1 - Ler uma Palavra\n"
            " 2 - Imprimir a Gramatica\n"
            "-1 - Encerrar\n"
            "==========================\n"
            "\n=> ";
    
    if(!(cin >> op)) {cin.clear(); limparBuffer(); return 0;}
    limparBuffer();
    limparTerminal();

    switch(op) {
        case 1 : Aut.conferirPalavra(); ENTER(); break;
        case 2 : Aut.imprimirGramatica(); ENTER(); break;
        default : return op;
    }

    return 0;
}

int main() {
    string arquivo;
    limparTerminal();
    cout << "Digite o arquivo para ser lido\n=> ";

    do {
        cin >> arquivo;
        limparBuffer();
        limparTerminal();
        if (!arquivoExiste(arquivo)) {
            cout << "\nErro! Digite novamente\n=> ";
        }
    } while (!arquivoExiste(arquivo));

    limparTerminal();
    Automato Aut(arquivo);

    while(abrirMenu(Aut) != -1);
    return 0;
}