#include <iostream>
#include <string>
#include "automato.h"

using namespace std;

int abrirMenu(Automato& Aut) {

    // Printf e tals
    int op;
    cout << "eae?";
    cin >> op; limparBuffer();

    switch(op) {
        case 1 : Aut.conferirPalavra(); break;
        case 2 : Aut.imprimirGramatica(); break;
        /* ... */
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