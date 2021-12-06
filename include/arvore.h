#ifndef ARVORE_H
#define ARVORE_H

typedef struct no{
    int complexidade;
	char *formula;
	char op;
    struct no *esq;
    struct no *dir;
}NO;

typedef struct no NO;

void insercao_arvore(NO **raiz, int x, char* formula);
void in_ordem(NO* pt);
void pre_ordem(NO* pt);
void pos_ordem(NO* pt);

#endif
