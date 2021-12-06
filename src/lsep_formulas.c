#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"
#include "heap_sort.h"

typedef struct no Node;

int complexidade(char *formula);
void verifica_subformula(Node **arv, char *sub_formula, int x, int op_externo);

char *limpa_espacos(char *f){

    char *aux = malloc(strlen(f)+1);
    int cont = 0;

    for (int i = 0; f[i] != '\0'; i++){
        if (f[i] != ' '){
            aux[cont] = f[i];
            cont++;
        }
    }

	aux[cont] = '\0';
    aux = realloc(aux, strlen(aux)+1);

    return aux;
}

int e_atomo(char *formula){

	/*
	 * Função que verifica se a fórmula tem apenas um caractere,
	 * pois em caso positivo ela será um átomo.
	 * */

	if(formula[1] == '\0')
		return true;
	else
		return false;
}

int verifica_pares_parenteses(char *formula){

	/*
	 * Esta função é responsável apenas por definir se a fórmula se encaixa
	 * ou não no quesito quantidade de parenteses que abre e que fecham, ou seja,
	 * a fórmula ainda pode não ser bem formada por outros quesitos.
	 * */

	/*
  	 * Um dos pontos a ser verificado em uma fórmula é a quantidade de parentese que
	 * que há nela, porque caso a quantidade de parênteses que abre '(' seja diferente
	 * da quantidade de parênteses que fecha ')', a formula automáticamente pode ser
	 * considerada como sendo NÃO BEM FORMADA.
	 * */

    int qtd = 0;

    for (int i = 0; formula[i] != '\0'; i++)
		if(formula[i] == ')')
			qtd++;
		else if(formula[i] == '(')
			qtd--;
		else if((formula[i] == '&' || formula[i] == '#' || formula[i] == '>') && qtd == 0)
			return false;

	/*
	 * Ao fim do laço a variável qtd terá a diferença da quantidade
	 * de parenteses abrindo pela quantidade dos que estão fechando.
	 * */

	if(qtd == 0)
		return true;
	else
		return false;
}

bool bloco_invalido(char *formula){

	/*
	 * Função que verifica se há blocos vazios ou sem um operador
	 * lógico binário dentro.
	 *
	 * EX:. (), (a), (--a)...
	 * */

	bool x;
	int bloco=0;

	x = true;
	for(int i = 0; formula[i] != '\0'; i++){
		if(formula[i] == '(')
			bloco++;
		else if(formula[i] == ')')
			bloco--;

		if(bloco >= 1){
			if(formula[i] == '(')
				x = false;
			if(formula[i] == '#' || formula[i] == '&' || formula[i] == '>')
				x = true;
		}

		if(bloco == 0 && x == false)
			return x;
	}

	return x;
}

bool verifica_formula(char *formula){

	/*
	 * Caso a quantidade de parênteses que abre e que fecha seja
	 * igual e não haja incoerência na formula, ela é considerada
	 * uma formua bem formada, então esta função retornará true,
	 * caso contrário irá entrar em um condicional e retornará false
	 * indicando que não é bem formada.
	 * */

	formula = limpa_espacos(formula);
	if (verifica_pares_parenteses(formula) == false)
		return false;

	if(bloco_invalido(formula) == false)
		return false;

    for (int i = 0; formula[i] != '\0'; i++){

		if(formula[i] >= 'a' && formula[i] <= 'z'){
			if(formula[i+1] == '-'){
				return false;
			}
		}

		if(formula[i] < 'a' || formula[i] > 'z'){
			if(formula[i] != '-' && formula[i] != '&' && formula[i] != '#' &&
			formula[i] != '>' && formula[i] != '(' && formula[i] != ')'){
				return false;
			}
		}

		if(formula[i] == '('){
			if(formula[i+1] != '-' && formula[i] != '('){
				return false;
			}
			if(formula[i+1] == ')'){
				return false;
			}
		}

		if(formula[i] == ')'){
			if(formula[i+1] != '&' && formula[i+1] != '#' && formula[i+1] != '>'
			&& formula[i+1] != ')' && formula[i+1]!='\0'){
				return false;
			}
		}

		if(formula[i] == '-'){
			if(formula[i+1] != '-' && formula[i+1] != '(' && (formula[i+1] < 'a'
			|| formula[i] > 'z')){
				return false;
			}
		}

		if(formula[i] == '&' || formula[i] == '#' || formula[i] == '>'){
			if(formula[i+1] == '&' || formula[i+1] == '#' || formula[i+1] == '>'
			|| formula[i+1] == ')'){
				return false;
			}
			if(formula[i+2] == '&' || formula[i+2] == '#' || formula[i+2] == '>'){
				return false;
			}
		}
	}

	return true;
}

char **divide_formula_negacao(char *formula){

	/*
	 * Função que divide uma formula que tem uma negação na primeira
	 * posição.
	 * EX:. A divisão de -(p&q) resulta em - e (p&q).
	 *
	 * Após este processo de divisão retorna um vetor com cada parte dividida.
	 * */

    int i = 0;
    char **s  = malloc(sizeof(char*) *  3);
    char *esq = malloc(sizeof(char)  * strlen(formula)+1);
    char *dir = malloc(sizeof(char)  * strlen(formula)+1);
    char *ope = malloc(sizeof(char)  *  2);

    if (formula[0] == '-')
        for (i = 1; formula[i] != '\0'; i++)
            esq[i - 1] = formula[i];

    dir[0] = ' ';
    ope[0] = '-';
    dir[1] = ope[1] = esq[i - 1] = '\0';

	esq = realloc(esq, sizeof(char)*strlen(esq)+1);
	dir = realloc(dir, sizeof(char)*strlen(dir)+1);

    s[0] = esq;
    s[1] = dir;
    s[2] = ope;

    return s;
}

char **divide_formula(char *formula, const int pos){

	/*
	 * Função que divide uma formula e retorna um vetor com suas
	 * partes, o lado esquerdo e o direito da divisão, e o operador lógico
	 * que separa estes dois lados na fórmula original.
	 * */

    int i=0, j=0;
	int pos_esq=0, pos_dir=0;

    char **s  = malloc(sizeof(char*) * 3);
    char *esq = malloc(sizeof(char)  * strlen(formula)+1);
    char *dir = malloc(sizeof(char)  * strlen(formula)+1);
    char *ope = malloc(sizeof(char)  * 2);

    for (i = 1; formula[i+1] != '\0'; i++){
        if (i < pos){
            esq[i-1] = formula[i];
		}else if (i == pos){
            ope[0] = formula[pos];
		}else{
            dir[j] = formula[i];
            j++;
		}
	}

    dir[j] = esq[(i-j)-2] = ope[1] = '\0';

    s[0] = esq;
    s[1] = dir;
    s[2] = ope;

    return s;
}

void separa_op_binario(Node **arv, char *sub_formula, int tam){

	/*
	 * Esta função auxilia a separção de formulas que tem um operador binário
	 * no local da divisão (sub_formula[tam]), coloca cada subfórmula
	 * na árvore e chama a função que continua separando as próximas subfórmulas.
	 * */

	Node *aux = (*arv);
    char **s = divide_formula(sub_formula, tam);


	/* adiciona o operador usado para a divisão, e cada subfórmula na árvore. */

	(*arv)->op = *s[2];
	arv = &(aux->esq);
	insercao_arvore(arv, complexidade(s[0]), s[0]);
	arv = &(aux->dir);
	insercao_arvore(arv, complexidade(s[1]), s[1]);

	/*
	 * Como em cada lado da árvore terá uma subfórmula que possivelmente
	 * pode ser dividida, temos que voltar para o nó principal para pode
	 * chamar verifica_subformula em cada lado.
	 * */

	arv = &aux;

	/*
	 * verifica se tem mais subfórmulas para cada subfórmula
	 * achada anteriormente.
	 * */

	arv = (&(*arv)->esq);
    tam = strlen(s[0]);
    verifica_subformula(arv, s[0], tam, 0);

	arv = &aux;
	arv = (&(*arv)->dir);
    tam = strlen(s[1]);
    verifica_subformula(arv, s[1], tam, 0);
}

void separa_op_unario(Node **arv, char *sub_formula, int tam){

	/*
	 * Esta função separa fórmulas que tem um operador unário
	 * no local da divisão, e continua separando a subfórmula
	 * resultante.
	 * */

	Node *aux = (*arv);
    char **s = divide_formula_negacao(sub_formula);

	/* adiciona o operador usado para a divisão e cada subfórmula na árvore. */
	(*arv)->op = *s[2];
	arv = &(aux->esq);
	insercao_arvore(arv, complexidade(s[0]), s[0]);


	/* Verifica se tem mais subfórmulas */
    tam = strlen(s[0]);
    verifica_subformula(arv, s[0], tam, 0);
}

void verifica_subformula(Node **arv, char *sub_formula, int x, int op_externo){

    if (e_atomo(sub_formula))
        return;

    if (verifica_formula(sub_formula) == false){
		/* Verifica se cada subfórmula foi dividida corretamente */
        printf("Fórmula invalida!!!\n");
        exit(0);
    }

	/*
	 * Para dividir uma fórmula, tem-se que ter uma forma de dividi-la no
	 * local correto.
	 *
	 * EX:. (((p&q) # (p&s)) > (p#s))
	 * A fórmula a cima será dividida nas partes ((p&q) # (p&s)) e em (p#s),
	 * sendo errada qualquer outra forma de dividir a fórmula. Dado isto,
	 * devemos dividir a fórmula apenas no OPERADOR LÓGICO que pertence
	 * somente aos parênteses mais EXTERNOS, que neste exemplo é o operador '>'.
	 *
	 * A variável que fará esse papel de mapear o operador mais externo será op_externo,
	 * incrementando a cada vez que encontra '(' e decrementando quando tem ')' na fórmula
	 * passada. Ou seja, teremos a certeza que podemos dividir a fórmula apenas quando
	 * encontrar um operador lógico e a variável op_externo for igual a 1.
	 * */

    if (sub_formula[x] == ')')
        op_externo++;
    else if (sub_formula[x] == '(')
        op_externo--;

    if (sub_formula[0] == '-'){
		separa_op_unario(arv, sub_formula, x);
    }
    else if (sub_formula[x] == '>' && op_externo == 1){
		separa_op_binario(arv, sub_formula, x);
    }
    else if (sub_formula[x] == '&' && op_externo == 1){
		separa_op_binario(arv, sub_formula, x);
    }
    else if (sub_formula[x] == '#' && op_externo == 1){
		separa_op_binario(arv, sub_formula, x);
   	}else{
        x--;
        verifica_subformula(arv, sub_formula, x, op_externo);
    }

	return;
}

Node *separa_formula(char formula[]){

	/*
	 * Funçãoa auxiliar que limpa os espaços da fórmula, cria uma árvore para
	 * armazenar cada subfórmula e chama verifica_subformulaulas para
	 * de fato separar as fórmulas.
	 * */

	Node *raiz = NULL;
	char *formula_limpa = limpa_espacos(formula);
	int complexi = complexidade(formula_limpa);
	int ultima_posicao = strlen(formula_limpa);

	insercao_arvore(&raiz, complexi, formula_limpa);
	verifica_subformula(&raiz, formula_limpa, ultima_posicao, 0);

	return raiz;
}

int complexidade(char *formula){

	/* Função que calcula a complexidade da fórmula passada */

    int comp = 0;

    for(int i = 0; formula[i] != '\0'; i++)
        if(formula[i] != '(' && formula[i] != ')')
            comp++;
    return comp;
}

void cp_arv(char **lista, Node *arv, int *qtd_lista, int *dir_arv){

	/*
	 * Função que copia uma árvore com fórmulas para um vetor.
	 * */

	if(arv == NULL)
		return;

	lista[(*qtd_lista)] = malloc(sizeof(char)*strlen(arv->formula)+1);

	strcpy(lista[(*qtd_lista)++],arv->formula);

	cp_arv(lista, arv->esq, qtd_lista, dir_arv);
	if((*dir_arv) == 0)
		(*dir_arv) = (*qtd_lista)+1;

	cp_arv(lista, arv->dir, qtd_lista, dir_arv);
}

void mostra_arv(Node *arv){
	int dir_arv=0;
	int qtd_lista=0;

	char **lista_formulas;
	lista_formulas = malloc(sizeof(char *)*1000);

	cp_arv(lista_formulas, arv, &qtd_lista, &dir_arv);
	lista_formulas[qtd_lista] = NULL;

	//ordenando as fórmulas por complexidade com o heap sort.
	heap_sort(lista_formulas,qtd_lista);

	printf("\t\tSubfórmulas\n\n");
	for(int i = 0; i < qtd_lista; i++){
		printf("-> [%s]\n", lista_formulas[i]);
	}

	for(int i = 0; i < qtd_lista; i++)
		free(lista_formulas[i]);
	free(lista_formulas);
}
