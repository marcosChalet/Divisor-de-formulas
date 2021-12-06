#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lsep_formulas.h"

/*
 * Biblioteca que cria e ordena heap minimro.
 * */

#define SWAP(a, b, size)			\
	do									\
	{									\
    	size_t __size = (size);					\
    	char *__a = (a), *__b = (b);			\
	    do										\
		{										\
    		char __tmp = *__a;						\
    		*__a++ = *__b;							\
    		*__b++ = __tmp;							\
		}while(--__size > 0);					\
	}while(0)

void descer(char **tabela, int qtd, int i){
	int filho;

	filho = 2*i+1;

	if(filho <= qtd){
		if(filho < qtd){
			if(complexidade(tabela[filho]) > complexidade(tabela[filho+1]))
				filho++;
		}

		if(complexidade(tabela[i]) > complexidade(tabela[filho])){
			SWAP((char*)&tabela[i], (char*)&tabela[filho], sizeof(char*));
			descer(tabela, qtd, filho);
		}
	}
}

void construir(char **lista, int qtd){
	qtd--;
	for(int i = qtd/2; i >= 0; i--)
		descer(lista, qtd, i);
}

void heap_sort(char **lista, int qtd){
	construir(lista, qtd);

	qtd--;
	for(int i = qtd; i >= 0; i--){
		SWAP((char*)&lista[0], (char*)&lista[i], sizeof(char*));
		qtd--;
		descer(lista, qtd, 0);
	}
}
