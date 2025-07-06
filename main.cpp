#include <iostream>
#include <string>
#include "automato.h"



int abrirMenu() {
    std::string arquivo; // Le o nome do arquivo
    Automato Aut(arquivo);

    // Printf e tals
    int op;
    std::cin >> op; limparBuffer();

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