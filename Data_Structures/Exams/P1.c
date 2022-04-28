#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto {
char nomeproduto[20];
float valor;
} TProduto;

typedef struct setor {
    char nomesetor[10];
    int qtde; 
    TProduto *prod;
} TSetor;


TSetor *aloca_setor(int tam);
void armazena_setor_produto(TSetor *paux, int index);
TSetor *desaloca_setor(TSetor *p, int tam);

TProduto *armazena_produto(int qtd, int index);
void handle_error();

int main()
{
    int tam = 0, op;
	TSetor *p = NULL;
    
	do {
	    printf("\n------------------------------------");
	    printf("\n1-Aloca Setor\n2-Armazena Produto\n3-Desaloca Setor\n0-Sair\nInforme Opcao: ");
    	scanf("%d", &op);
	    switch(op) {
	    	case 1: {
			    printf("Informe numero de setores do supermercado: ");
	    		scanf("%d",&tam);
	    		p=aloca_setor(tam);
	    	} continue;
	    	case 2: {
	    		for (int i = 0; i < tam; i++) {
	    			armazena_setor_produto(p + i, i + 1);
	    		}
	    	} continue;
	    	case 3: {
	    		p=desaloca_setor(p,tam);
	    	} continue;
			case 0: break;
	    	default: {
				printf("\nOpcao invalida");
			} continue;
		}
	} while (op != 0);
    return 0;
}

TSetor *aloca_setor(int tam)
{
    TSetor *paux;
    paux = (TSetor *) malloc(tam*sizeof(TSetor));
    if(paux == NULL) handle_error();    
    return paux;
}

void armazena_setor_produto(TSetor *paux, int index) 
{
    int qtd;

	printf("Informe o nome do setor %i: ", index);
	scanf("%s", paux->nomesetor);
	
	printf("Informe a quantidade de produtos do setor %i: ", index);
	scanf("%i", &qtd);
	paux->qtde = qtd;
	
	paux->prod = armazena_produto(qtd, index);
    printf("\n");
}

TProduto *armazena_produto(int qtd, int index)
{
	TProduto *aux = (TProduto*) calloc(qtd, sizeof(TProduto));
	if (!aux) handle_error();

    char buf[20];

	for (int i = 0; i < qtd; i++) {
		printf("\nNome do produto %i do setor %i: ", i + 1, index);
		scanf("%s", buf);
        strcpy((aux + i)->nomeproduto, buf);

		printf("Valor do produto %i do setor %i: ", i + 1, index);
		scanf("%f", &(aux + i)->valor);
	}
    printf("\n");
	return aux;
}

TSetor *desaloca_setor(TSetor *p, int tam) 
{
	for (int i = 0; i < tam; i++) free((p + i)->prod);
	free(p);

	return NULL;
}

void handle_error() 
{
    printf("Ma alocacao\n");
    exit(EXIT_FAILURE);
}
