/**Por: Carla de Oliveira Barden*/
#ifndef ESTRUTURAS_H
#define ALFABETO 26
#define NOINDEX "naoindexar.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glob.h>

/*Estrutura que será usada tanto para criar uma lista de arquivos quanto para criar uma lista de palavras do arquivo*/
typedef struct lista {
	char str[256];
	struct lista *prox;
} LISTA_T;

/*Estrutura que armazenará dados relevantes sobre cada palavra*/
typedef struct end_word {
	int qtd;
	LISTA_T *arquivo;
	struct end_word *prox;
} END_WORD_T;

/*A própria posição do nó na estrutura representa a letra do alfabeto
Local != NULL indicará em qual arquivo a palavra está presente*/
typedef struct trie_nodo {
	struct trie_nodo *node[ALFABETO];
	END_WORD_T *local;
} TRIE_NODE_T;

/*Gera um elemento da lista*/
LISTA_T *geraElemento (char str[]);

/*Faz a busca pelos arquivos txt e gera a lista principal de arquivos*/
LISTA_T *geraListaArquivos (void);

/*Imprime lista */
void imprimirLista (LISTA_T *lista);

/*Procurar determinado nome de arquivo, se achar retorna o ponteiro para ele*/
LISTA_T *procurarArquivo (LISTA_T *lista, char arq[]);

/*Gera e retorna uma lista com todas as palavras encontradas no arquivo passado como parâmetro*/
LISTA_T *parser (char nomeArq[]);

/*Filtrar caracteres especiais da linha;  Deixa apenas palavras em letras minúsculas e espaços. Substitui caracteres especiais por 'x' */
void filtro (char str[]);

/*Procura palavra na trie. Se estiver presente, retorna 1, se não retorna 0*/
int procurarNodo (TRIE_NODE_T *raiz, char palavra[]);

/*Verifica se há o arquivo naoindexar.txt e constroi a trie. Caso não tenha, faz raiz = null*/
TRIE_NODE_T *geraTrieNI (void);

/*Gera novo nó na trie -- vazio*/
TRIE_NODE_T *geraNodo (void);

/*Insere a palavra na árvore indicada. */
void inserirNodo (TRIE_NODE_T *raiz, char palavra[],LISTA_T *arq);

/*Gera a TRIE preocupando-se com palavras repetidas. Se o ponteiro *naoindexar não for nulo, verifica se a palavra está nesta trie
antes de colocá-la aqui. */
TRIE_NODE_T *geraTrie (TRIE_NODE_T *naoindexar, LISTA_T *arquivos);

/*Aloca o espaço para a estrutura/lista que indicará o final da palavra e armazenará a qtd de vezes que ela aparece.*/
END_WORD_T *geraFimPalavra(LISTA_T *arq);

/*Gerencia a lista de ponteiros para arquivos onde a palavra aparece*/
void addPalavraArquivo(TRIE_NODE_T *node, LISTA_T *arq);

/* Retorna um ponteiro para o nó que contém a última letra da palavra
Consequentemente, retorna o primeiro elemento da lista de palavras de cada arquivo */
TRIE_NODE_T *retornarNode (TRIE_NODE_T *raiz, char palavra[]);

/*Imprime na tela em quais arquivos cada palavra está presente 
*imprime lista end_word*/
void imprimePalavraArquivo(TRIE_NODE_T *node);

/*Ordenar por maior quantidade*/
void ordenaPalavraArquivo(TRIE_NODE_T *node);

/*Gerar saída conforme as palavras fornecidas na entrada*/
void saida (TRIE_NODE_T *raiz, char str[]);

#define ESTRUTURAS_H
#endif
