#include <iostream>
#include <string>
#include "automato.h"

using namespace std;

int abrirMenu() {
    string arquivo; // Le o nome do arquivo
    cout << "\nDigite o arquivo para ser lido\n\n=>";
    cin >> arquivo; limparBuffer();
    Automato Aut(arquivo);

    // Printf e tals
    int op;
    cout << "eae? 1";
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
    while(abrirMenu() != -1);
    return 0;
}