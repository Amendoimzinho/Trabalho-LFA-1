#include <iostream>
#include <fstream>
#include <string>
#include "automato.h"

using namespace std;

void ENTER () {
    cout << "\nPressione ENTER para voltar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool arquivoExiste(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    return arquivo.good();
}

void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int abrirMenu(Automato& Aut) {
    limpar_terminal();

    int op;
    cout << "======= Menu =======\n" 
            " 1 - Pedir uma Palavra\n"
            " 2 - Imprimir a Gramatica\n"
            "-1 - Encerrar\n"
            "\n=> ";
    if(!(cin >> op)) {cin.clear(); limparBuffer(); return 0;}
    limparBuffer();
    switch(op) {
        case 1 : Aut.conferirPalavra(); ENTER(); break;
        case 2 : Aut.imprimirGramatica(); ENTER(); break;
        default : return op;
    }

    return 0;
}

int main() {
    string arquivo;
    cout << "\nDigite o arquivo para ser lido\n\n=> ";

    do {
        cin >> arquivo;
        limparBuffer();
        limpar_terminal();
        if (!arquivoExiste(arquivo)) {
            cout << "\nErro! Digite novamente\n=> ";
        }
    } while (!arquivoExiste(arquivo));

    Automato Aut(arquivo);

    while(abrirMenu(Aut) != -1);
    return 0;
}