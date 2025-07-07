#include <iostream>
#include <string>
#include "automato.h"

using namespace std;

void ENTER () {
    cout << "\nPressione ENTER para voltar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << "\n====== Menu ======\n" 
            " 1 - Pedir uma Palavra\n"
            " 2 - Imprimir a Gramatica\n"
            "-1 - Encerrar\n";
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
    cout << "\nDigite o arquivo para ser lido\n\n=>";
    cin >> arquivo; limparBuffer();

    Automato Aut(arquivo);

    while(abrirMenu(Aut) != -1);
    return 0;
}