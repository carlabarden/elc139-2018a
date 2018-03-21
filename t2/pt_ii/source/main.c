#include "estruturas.h"

int main(){

	LISTA_T *arquivos = geraListaArquivos();
	TRIE_NODE_T *rootNoIndex = geraTrieNI();
	TRIE_NODE_T *raiz = geraTrie(rootNoIndex,arquivos);
	char words[300];

	do{
		words[0] = '\0';
		printf("Pesquisar:    (0 p/ sair)\n");
		fgets(words,300,stdin);
		if (words[0] != '0')
			saida(raiz,words);	
	}while(words[0] != '0');

	return 0;
}
