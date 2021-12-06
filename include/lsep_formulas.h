#ifndef PARTE_I_H
#define PARTE_I_H

typedef struct no Node;

int complexidade(char *formula);
void mostra_arv(Node *arv);
Node *separa_formula(char formula[]);
int verifica_formula(char *formula);

#endif
