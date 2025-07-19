#include <iostream>
#include <fstream>
#include <string>
#include "automato.h"

using namespace std;

/// @author @Amendoimzinho
/// @file main.cpp

/// @brief Testa se um arquivo existe
/// @param nomeArquivo 'string' diretorio do arquivo
/// @return 'true' se o arquivo existe
///         'false' se nao encontrar (para abertura)
bool arquivoExiste(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo); // Abre o arquivo
    return arquivo.good(); // Retorna se deu certo ou nao
}

/// @brief Menu de opcoes do programa
/// @param Aut Um 'Automato' ja construido
/// @return O valor de funcionamento (0 para encerrar)
int abrirMenu(Automato& Aut) {
    int op;
    cout << "========== Menu ==========\n" 
            " 1 - Ler uma Palavra\n"
            " 2 - Imprimir a Gramatica\n"
            " 0 - Encerrar\n"
            "==========================\n"
            "\n=> ";
    
    if(!(cin >> op)) {cin.clear(); limparBuffer(); return 0;} // Se for colocado um nao 'int' encerra;
    limparBuffer();
    limparTerminal();

    switch(op) { // Switch da operacao do usuario
        case 1 : Aut.conferirPalavra(); ENTER(); break;
        case 2 : Aut.imprimirGramatica(); ENTER(); break;
        default : return op;
    }

    return 1;
}

int main() {
    string arquivo;
    limparTerminal();
    cout << "Digite o arquivo para ser lido\n=> ";

    // Enquanto o usuario nao der um arquivo valido ele pede um novo
    do {
        cin >> arquivo; limparBuffer();
        limparTerminal();
        if (!arquivoExiste(arquivo)) {
            cout << "\nErro! Digite novamente\n=> ";
        }
    } while (!arquivoExiste(arquivo));

    limparTerminal();
    Automato Aut(arquivo); // Constroi o Automato

    while(abrirMenu(Aut)); // Abre o menu
    return 0;
}