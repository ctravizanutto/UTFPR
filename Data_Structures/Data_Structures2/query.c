#include <stdlib.h>
#include <stdio.h>
#include "libs/utils.h"

void prompt();

int main(void) {
    unsigned int wallets[BLOCKCHAIN_SIZE] = {0};
}

void prompt() {
    unsigned int option = 0;
    printf("\e[1;1H\e[2J"); // regex to clean ASNI terminal
    printf("1. Imprimir informacoes bloco\n2. Imprimir quantidade de bitcoins\n3. Bloco com mais bitcoins\n4. Listagem geral\n5. Sair\n");
    scanf("%i", &option);

    switch (option) {
        case 1:
            printf("Digite o indice do bloco: ");
            scanf("%i", &option);
            // todo
            break;
        case 2:
            // todo
            printf("Digite o endereço do bloco: ");
            scanf("%i", &option);
            break;
        case 3:
            // todo  
            break;
        case 4:
            printf("--------------------------------------------------------\n");
            // todo
            break;
        case 5:
            exit(0);
        default:
            printf("Opcao invalida\n");
            break;
    }
}
