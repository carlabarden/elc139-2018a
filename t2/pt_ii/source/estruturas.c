/**Por: Carla de Oliveira Barden*/
#include "estruturas.h"

LISTA_T *geraElemento (char str[]){
	LISTA_T *new = NULL;
	new = (LISTA_T*)malloc(sizeof(LISTA_T));
	if (new){
		strcpy(new->str,str);
		new->prox = NULL;
	}
	return new;
}

LISTA_T *geraListaArquivos (void){
	int i;
	glob_t globbuf;
	LISTA_T *new = NULL, *lista = NULL, *ptr = NULL, *it = NULL;

	if (!glob("*.txt", 0, NULL, &globbuf)) {
        for (i=0;  i <globbuf.gl_pathc; i++)
        	if (i == 0)
        		lista = geraElemento(globbuf.gl_pathv[i]);
        	else{
        		ptr = lista;
        		it = lista->prox;
        		new = geraElemento(globbuf.gl_pathv[i]);
        		if (it)
        			while(it){
        				it = it->prox;
						ptr = ptr->prox;
        			}
        		ptr->prox = new;
        	}
        globfree(&globbuf);
    }
    else 
        printf("Error: glob()\n");

    return lista;
}

void imprimirLista (LISTA_T *lista){
	printf("\n");
	while (lista){
		printf("%s\n", lista->str);
		lista = lista->prox;
	}
	printf("\n");
	return;
}

LISTA_T *procurarArquivo(LISTA_T *lista, char arq[]){
	LISTA_T *ptr = lista;

	while(ptr){
		if(!(strcmp(ptr->str,arq)))
			return ptr;
		else
			ptr = ptr->prox;
	}
	return NULL;
}

LISTA_T *parser (char nomeArq[]){
	FILE *arq = fopen(nomeArq,"r");
	if (!arq){
		printf("\nErro ao abrir arquivo!\n");
		exit(1);
	}

	char linha[256], *tok;
	LISTA_T *new = NULL, *lista = NULL;
	while (fgets(linha,sizeof(linha),arq) != NULL){
		filtro(linha);
		tok = strtok(linha," ");
		while(tok){
			new = geraElemento(tok);
			new->prox = lista;
			lista = new;
			tok = strtok(NULL," ");
		}
	}
	fclose(arq);
	return lista;
}

void filtro (char str[]){
	char aux[256];
	aux[0]='\0';
	int i, j;
	char *tok = strtok(str, "&^,.;!?=\t\n\\(){}[]\"#<>*\%");
	while(tok){
		strcat(aux,tok);
		tok = strtok(NULL,"&^,.;!?=\t\n\\(){}[]\"#<>*\%");
	}
	/*Verificando caracteres especiais*/
	j = strlen(aux);

	for (i = 0; i < j; i++){
		if (!isalpha(aux[i]) && !isspace(aux[i]))
			aux[i] = 'x';
		else if (isupper(aux[i]))
			aux[i] = tolower(aux[i]);
	}
	strcpy(str,aux);
	aux[0] = '\0';
	return;
}

TRIE_NODE_T *geraNodo (void){
	TRIE_NODE_T *new = NULL;
	new = (TRIE_NODE_T*)malloc(sizeof(TRIE_NODE_T));
	if (new){
		int i;
		new->local = NULL;
		for (i = 0; i < ALFABETO; i++)
			new->node[i] = NULL;
	}
	return new;
}

int procurarNodo (TRIE_NODE_T *raiz, char palavra[]){
	int nivel;
	int profundidade = strlen(palavra);
	int index = 0;
	TRIE_NODE_T *ptr = raiz;

	for (nivel = 0; nivel < profundidade; nivel++){
		index = palavra[nivel];
		index -= 97;  /*num ascii para 'a', a aqui deve ser 0*/
		if (!ptr->node[index])
			return 0;
		ptr = ptr->node[index];
	}
	if(ptr != NULL && ptr->local != NULL)
		return 1;
	else
		return 0;
}

void inserirNodo (TRIE_NODE_T *raiz, char palavra[], LISTA_T *arq){
	int nivel;
	int profundidade = strlen(palavra);
	int index;
	TRIE_NODE_T *ptr = raiz;
	
	for (nivel = 0; nivel < profundidade; nivel++){
		index = palavra[nivel];
		index -= 97;  /*num ascii para 'a' == 97, a aqui deve ser 0*/
		if (!ptr->node[index])
			ptr->node[index] = geraNodo();
		ptr = ptr->node[index];
	}

	ptr->local = geraFimPalavra(arq);
	return;
}

TRIE_NODE_T *geraTrieNI (void){
	LISTA_T *arqnaoindexar = procurarArquivo(geraListaArquivos(),NOINDEX);
	LISTA_T *palavras = NULL;
	if(!arqnaoindexar)
		return NULL;
	else{
		TRIE_NODE_T *raiz = geraNodo();
		palavras = parser(arqnaoindexar->str);
		LISTA_T *it = palavras;
		while(it){
			inserirNodo(raiz,it->str,arqnaoindexar);
			it = it->prox;
		}
		return raiz;
	}
}

TRIE_NODE_T *geraTrie (TRIE_NODE_T *naoindexar, LISTA_T *arquivos){
	LISTA_T *itArquivos = arquivos;
	TRIE_NODE_T *raiz = geraNodo();

	while(itArquivos){
		LISTA_T *palavras = parser(itArquivos->str);
		LISTA_T *itPalavras = palavras;

		if (naoindexar)
			while (itPalavras){
				if (!procurarNodo(naoindexar,itPalavras->str)){
					if (!procurarNodo(raiz,itPalavras->str))
						inserirNodo(raiz,itPalavras->str,itArquivos);
					else
						addPalavraArquivo(retornarNode(raiz,itPalavras->str),itArquivos);
				}
				itPalavras = itPalavras->prox;				
			}
		else
			while (itPalavras){
				if (!procurarNodo(raiz,itPalavras->str))
					inserirNodo(raiz,itPalavras->str,itArquivos);
				else
					addPalavraArquivo(retornarNode(raiz,itPalavras->str),itArquivos);
				itPalavras = itPalavras->prox;				
			}
		itArquivos = itArquivos->prox;
		palavras = NULL;
		itPalavras = NULL;
	}
	return raiz;
}

END_WORD_T *geraFimPalavra(LISTA_T *arq){
	END_WORD_T *new = NULL;
	new = (END_WORD_T*)malloc(sizeof(LISTA_T));
	if(new){
		new->arquivo = arq;
		new->qtd = 1;
		new->prox = NULL;
	}
	return new;
}

TRIE_NODE_T *retornarNode (TRIE_NODE_T *raiz, char palavra[]){
	TRIE_NODE_T *ptr = raiz;
	int profundidade = strlen(palavra);
	int index;
	int nivel;

	for (nivel = 0; nivel < profundidade; nivel++){
		index = palavra[nivel];
		index -= 97;  /*num ascii para 'a' == 97, a aqui deve ser 0*/
		if(!ptr->node[index])
			return NULL;
		ptr = ptr->node[index];
	}
	if (ptr != NULL && ptr->local != NULL)
		return ptr;
	else
		return NULL;
}

void addPalavraArquivo(TRIE_NODE_T *node, LISTA_T *arq){
	END_WORD_T *it = node->local;
	END_WORD_T *ptr = node->local->prox;
	END_WORD_T *new = NULL;

	while (it){
		if(it->arquivo == arq){
			node->local->qtd += 1;
			return;
		}
		it = it->prox;
	}

	it = node->local;
	if (ptr)
		while(ptr){
			ptr = ptr->prox;
			it = it->prox;
		}
	new = geraFimPalavra(arq);
	it->prox = new;
	return;
}

void imprimePalavraArquivo(TRIE_NODE_T *node){
	END_WORD_T *ptr = node->local;
	printf("\n");
	while(ptr){
		printf("%3dx -- %s\n",ptr->qtd ,ptr->arquivo->str);
		ptr = ptr->prox;
	}
	printf("\n");
}

void ordenaPalavraArquivo(TRIE_NODE_T *node){
	END_WORD_T *ptr = node->local;
	END_WORD_T *aux = NULL;
	END_WORD_T tmp;

	while(ptr){
		aux = ptr->prox;
		if (aux)
			while(aux){
				if(ptr->qtd < aux->qtd){
					tmp.qtd = aux->qtd;
					tmp.arquivo = aux->arquivo;

					aux->qtd = ptr->qtd;
					aux->arquivo = ptr->arquivo;

					ptr->qtd = tmp.qtd;
					ptr->arquivo = tmp.arquivo;
				}
				aux = aux->prox;
			}
		ptr = ptr->prox;
	}
	return;
}

void saida (TRIE_NODE_T *raiz, char str[]){
	TRIE_NODE_T *resultado = NULL;
	char *tok;

	filtro(str);
	tok = strtok(str," ");
		while(tok){
			resultado = retornarNode(raiz,tok);
			if(resultado){
				printf("\n%s:",tok);
				ordenaPalavraArquivo(resultado);
				imprimePalavraArquivo(resultado);
			}
			else{
				printf("\n%s:",tok);
				printf("\n Não encontrado!\n\n");
			}
			tok = strtok(NULL," ");
		}
	return;
}