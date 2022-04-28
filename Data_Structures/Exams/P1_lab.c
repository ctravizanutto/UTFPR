#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct funcionario {
    char nome[20];
    int  idade; 
    int  sexo; 
} TFuncionario;

TFuncionario *load_file(char *file);
void free_(TFuncionario *v);
void distribute(TFuncionario *v);
void handle_error(int err);

int line_count = 1;

int main()
{
    int op=1;
    char file_name[255];
    TFuncionario *v = NULL;

    while(op!=3)
    {
	    printf("\n1-Carrega arquivo\n2-Distribui funcionario\n3-Sair\nInforme opcao:");
        scanf("%d",&op);
        switch(op)
        {
            case 1: {
                printf("Nome do arquivo: \n"); scanf("%s", file_name);
                v = load_file(file_name);
            } continue;
            case 2: distribute(v);
        }
    }
    
	free_(v);
    return 0;
}

TFuncionario *load_file(char *file) 
{
    FILE *f = fopen(file, "r");
    if (!f) handle_error(1);

    char c;
    while (!feof(f)) {
        fread(&c, 1, 1, f);
        if (c == '\n') line_count++;
    }

    fseek(f, 0, SEEK_SET);

    TFuncionario *tmp = (TFuncionario*) calloc(line_count, sizeof(TFuncionario));
    if (!tmp) handle_error(2);

    char buf[20];
    for (int i = 0; i < line_count; i++) {
        fscanf(f, "%s", buf);
        strcpy(tmp[i].nome, buf);

        fscanf(f, "%i", &(tmp[i].idade));
        fscanf(f, "%i", &(tmp[i].sexo));
    }
    
    fclose(f);
    return tmp;
}

void distribute(TFuncionario *v) 
{
    float team_size = (float) line_count / 3.0;
    if ((int) (team_size * 10) % 10 == 0) {
		int t1 = team_size;
        int t2 = team_size;
        int t3 = team_size;
    }
    
    int t1 = team_size + 1;
    int t2 = team_size;
    int t3 = team_size;

    FILE *ft1 = fopen("equipe1.txt", "w");
    FILE *ft2 = fopen("equipe2.txt", "w");
    FILE *ft3 = fopen("equipe3.txt", "w");

    // nao deu tempo de implementar as regras de divisao :(

    for (int i = 0; i < t1 - 1; i++) {
        fprintf(ft1, "%s %i %i\n", v[i].nome, v[i].idade, v[i].sexo);
    }
    for (int i = t1; i < t1 + t2 - 1; i++) {
        fprintf(ft2, "%s %i %i\n", v[i].nome, v[i].idade, v[i].sexo);
    }
    for (int i = t1 + t2; i < t1 + t2 + t3 - 1; i++) {
        fprintf(ft3, "%s %i %i\n", v[i].nome, v[i].idade, v[i].sexo);
    }

    fclose(ft1);
    fclose(ft2);
    fclose(ft3);
}

void free_(TFuncionario *v)
{
    free(v);
}

void handle_error(int err)
{
    if (err == 1) {
        printf("Nao foi possivel abrir esse abrir esse arquivo.\n");
        exit(0);
    }
    
    printf("Nao foi possivel alocar os funcionarios\n");
    exit(0);
}