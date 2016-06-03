# README #
** Visão Geral**
O objetivo deste projeto é implementar a estrutura de dados árvore binária, assim como suas principais funções de manipulação.

### MEMBBROS DA EQUIPE ###
* Igor A. Brandão
* José Carlos Emídio

### COMO COMPILAR ###
* Use o makefile digitando o comando **'make'** pelo terminal, após ter navegado para a pasta do projeto.

### COMO EXECUTAR O PROGRAMA ###
Para executar o projeto é necessário chamar o arquivo executável após compilar com o comando **'make'** pelo terminal,
assim:\n
* ./bin/binary_tree\n <'arquivo_criação_arvore'>

Caso o arquivo de criação da árvore não for informado, o sistemá irá utilizar um arquivo com configurações default

### LISTA DE CLASSES ###
As classes utilizadas pelo programa são as seguintes:

**Tree.h** 		=> Provê a definição geral da estrutura de dados árvore binária.
*Tree.inl* 		=> Implementa as funções definidas na classe tree.h.
*drive.cpp* 	=> Realiza as chamadas aos métodos da classe tree.h. É a ignição do sistema.

### ITENS NÃO DESENVOLVIDOS ###
Por questões de dificuldades técnicas e de entendimento durante o desenvolvimento do projeto, não foi possível
implementar a função toString que tem como finalidade converter a estrutura de árvore em um única arquivo de texto.

Além disso, a função que realiza o parse do arquivo de comandos ficou inacabada, apenas realizando a leitura do arquivo
de comandos em si, mas não direcionando as funções previamente implementadas na classe tree.h.

### OBSERVAÇÕES ###
Utilize a pasta assets/data para adicionar novos arquivos de geração da árvore ou de comandos.