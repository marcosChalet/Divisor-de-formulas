#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

//typedef struct no NO;
//typedef struct no No;

/*
typedef struct no{
    int complexidade;
	char *formula;
	char op;
    struct no *esq;
    struct no *dir;
}NO;
*/

void pre_ordem(NO* pt){

    if (pt == NULL) return;

    printf("%s, %c, %d\n", pt->formula, pt->op ,pt->complexidade);

    if(pt->esq != NULL){
        pre_ordem(pt->esq);
    }
    if(pt->dir != NULL){
       pre_ordem(pt->dir);
    }
}

void in_ordem(NO* pt){

	if (pt == NULL) return;

    if(pt->esq != NULL){
        in_ordem(pt->esq);
    }

    printf("%s, %c, %d\n", pt->formula, pt->op ,pt->complexidade);

    if(pt->dir != NULL){
       in_ordem(pt->dir);
    }
}

void pos_ordem(NO* pt){

    if (pt == NULL) return;

    if(pt->esq != NULL){
        pos_ordem(pt->esq);
    }

    if(pt->dir != NULL){
       pos_ordem(pt->dir);
    }

    printf("%s, %c, %d\n", pt->formula, pt->op ,pt->complexidade);
}

NO* busca_arvore (int x, NO* pt){
    if(pt == NULL){
        return NULL;
    }else if(x == pt->complexidade){
        return pt;
    }else if(x <= pt->complexidade){
        if(pt->esq == NULL){
            return pt;
        }else{
            return busca_arvore(x, pt->esq);
        }
    }else {
        if(pt->dir == NULL){
            return pt;
        }else{
            return busca_arvore(x, pt->dir);
        }
    }
}

void insercao_arvore(NO **raiz, int x, char* formula){

	NO* pt = busca_arvore(x, *raiz);

    if(pt == NULL || pt->complexidade != x){
        NO* novo = (NO*) malloc (sizeof(NO));
        novo->complexidade = x;
		novo->formula = formula;
        novo->esq = NULL;
        novo->dir = NULL;

        if(pt == NULL){
            (*raiz) = novo;
        }else if(x <= pt->complexidade){
            pt->esq = novo;
        }else{
            pt->dir = novo;
        }
    }else{
        printf("insercao invalida! :/");
    }
}

NO *remocao(NO* pt, int x){


    if (pt == NULL){
        puts("Árvore vazia");
        return pt;

    }else if (pt->complexidade > x){

        pt->esq = remocao(pt->esq, x);

    }else if(pt->complexidade < x){

        pt->dir = remocao(pt->dir, x);

    }else if(pt->complexidade == x){

        if (pt->dir == NULL && pt->esq == NULL){

            free(pt);
            pt = NULL;
        }else if (pt->dir == NULL){

            NO* aux = pt;
            pt = pt->esq;
            free(aux);
        }else if (pt->esq == NULL){

            NO* aux = pt;
            pt = pt->dir;
            free(aux);
        }else{

            NO* aux = pt->esq;

            while (aux->dir != NULL){

                aux = aux->dir;
            }

            pt->complexidade = aux->complexidade;
            aux->complexidade = x;
            pt->esq = remocao(pt->esq, x); //serve para excluir o nó.
        }
    }else{

        puts("nó não encontrado");
        return 0;
    }

    return pt;
}

