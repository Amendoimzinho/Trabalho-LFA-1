#ifndef AUTOMATO_H
#define AUTOMATO_H

/// @author @Amendoimzinho
/// @file automato.h
/// @brief Header da classe Automato

#include <iostream>
#include <vector>
#include <string>

/// @brief Classe usada para deixar mais facil mexer com as transicoes
class Transicao {
public:
    char C;
    int Prox;
    Transicao(char chr = '\0', int prx = -1);
    ~Transicao();
};

/// @brief Classe que implementa um AFD
class Automato {
private:
    std::vector<int> Finais;
    std::vector<std::vector<Transicao>> Tabela;

protected:
    /// @brief Pega a letra que 'Estado' representa
    /// @param Estado Um 'int' > 0
    /// @return O caractere equivalente ao estado
    char pegarLetra(int Estado);

public:
    /// @brief Contrutora do 'Automato'
    /// @param nomeArquivo 
    /// @throws Um 'const char*' quando nao conseguir acessar o arquivo
    Automato(const std::string& nomeArquivo);

    /// @brief Procura uma 'Transicao' para o estado
    /// @param E Estado atual
    /// @param c 'char' da 'Transicao' procurada
    /// @return Ponteiro transicao se encontrar
    ///         ou nullptr se nao encontrar
    Transicao* procurarTransicao(int E, char c);

    /// @brief Imprime a gramatica do Automato
    void imprimirGramatica();

    /// @brief Testa se um estado eh final para esse Automato
    /// @param Pos O estado a ser testado
    /// @return true se for um estado final
    ///         e false se nao for
    bool ehFinal(int Pos);

    /// @brief Pede e processa uma palavra dentro do Automato
    void conferirPalavra();
    
    ~Automato();
};

/// @brief Limpa o buffer do 'cin'
void limparBuffer();

/// @brief Tira todos os char 'rmv' e arruma o tamanho de uma string
/// @param str A string a ser "aparada"
/// @param rmv O 'char' a ser removido
void trim(std::string& str, char rmv);

/// @brief Limpa o Terminal
void limparTerminal();

/// @brief Pausa o programa e pede um ENTER para o usuario
void ENTER();

#endif 