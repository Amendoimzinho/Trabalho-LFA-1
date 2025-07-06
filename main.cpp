#include <iostream>
#include "automato.h"



int abrirMenu() {
    std::string arquivo; // Le o nome do arquivo
    Automato Aut(arquivo);

    // Printf e tals
    int op;
    std::cin >> op; limparBuffer();

    switch(op) {
        case 1 : while(conferirPalavras(Aut) != -1); break;
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