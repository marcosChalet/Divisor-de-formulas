#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lsep_formulas.h"
#include "arvore.h"

typedef struct no Node;

int menu();
void msgError();

//limpa buffer
void flush_in(){
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n');
}

void msgError(){
	//mensagem para caso o usuário não coloque uma entrada inválida.
    printf("Resposta inválida! Entre com um número entre 0 e 2\n\n");
    flush_in();
    if(system("clear||cls")){
    	printf("Erro na chamada de sistema!\n");
    }
    menu();
}

int menu(){

    int op = 0;

    printf("************* Verdade # Consequência *************\n");
    printf("* [0] Sair                                       *\n");
    printf("* [1] Verificar se é uma fórmula bem formada     *\n");
    printf("* [2] Verificar quais são as subfórmulas         *\n");
    printf("**************************************************\n");

    printf("Entre com a resposta: ");

    if (!scanf("%d", &op))
        msgError();

    else if (op < 0 || op > 2)
        msgError();

    flush_in();
    return op;
}

int main(){

	Node *raiz = NULL;
	char *formula;
	char form[1000];

	int op = menu();
	system("clear||cls");

	if(op == 0){
		printf("Saindo do programa\n");
		exit(0);
	}

	printf("Entre com a formula:\n-> ");
	scanf("%[^\n]s", form);
	puts("");

	formula = malloc(strlen(form)+1);
	strcpy(formula, form);

	if(op == 1){
		if(verifica_formula(formula))
			printf("É uma fórmula bem formada [%s]\n\n", formula);
		else
			printf("NÃO É uma fórmula bem formada [%s]\n\n", formula);
	}else if(op == 2){
		raiz = separa_formula(formula);
		printf("\n[FÓRMULA VÁLIDA!]\n\n");
		mostra_arv(raiz);
		free(raiz);
		raiz = NULL;
	}

	return 0;
}
