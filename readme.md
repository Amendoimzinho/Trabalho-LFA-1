
### Consideracoes

- Usem o Alfabeto como se fosse um vetor se char
- O vetor de Estados eh pra guardar como se fosse um enum, ou seja, apenas o numero de cada estado (q1 -> 1, q2 -> 2)
    - Isso pq pra mexer na matriz fica mais facil
- Msm coisa para o vetor de Finais
- A Tabela eh uma Matriz (vetor de vetores)
    - Nela o numero do estado eh seu indice (Linha) na Matriz
    - ~~A posicao de uma Letra na string Alfabeto vai ser o indice da Coluna na Tabela~~
    - Cada Linha tem suas Transicoes (Letra)
    - ~~a Ultima Coluna eh para guardar a Flag de se eh final ou nao~~


### A fazer

~~- [ ] Sobrecarregar '=' para 'Letra'~~
- [x] Implementar o Construtor de 'Automato'
    - [x] Ver como vai abrir o Arquivo
    - [x] Fazer as leituras
    - [x] Fazer o loop das Transicoes
    - [ ] Testar
- [x] Terminar 'conferirPalavras'
    - [x] Pedir e Ler a palavra
    - [x] Fazer as Impressoes como o prof pediu
    - [ ] Testar
- [ ] terminar 'imprimirGramatica'
    - [ ] Arrumar o " | " pq ta errado
    - [ ] Testar
- [ ] Terminar o menu
    - [ ] Pedir o arquivo (para leitura)
    - [ ] O print do menu


