// Augusto Padilha - 2374960
// Cainan Travizanutto e Silva - 2407248
// Caio Furlan - 2407256
// Gabriel Maestre - 2422611

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "libs/utils.h"

void prompt(wallets_vec wallets);
void print_block_info(unsigned char block_index);
int get_richer_wallet(wallets_vec wallets);

int main(void) {
    FILE *txt = fopen(BLOCKCHAIN_FILE_TXT, "r");
    if (txt == NULL) exit(EXIT_FAILURE);
    wallets_vec wallets = { 0 };
    fseek(txt, -2560, SEEK_END);
    for (int i = 0; i < 256; i++) {
        char buf[11] = {0};
        fscanf(txt, "%10s", buf);
        wallets[i] = (int) atoi(buf);
    }
    fclose(txt);
    prompt(wallets);

    return EXIT_SUCCESS;
}

void prompt(wallets_vec wallets) {
    unsigned int option = 0;
    
    while(1) {
        printf("\n1. Imprimir informacoes bloco\n2. Imprimir quantidade na carteira\n3. Carteira com mais bitcoins\n4. Listagem geral\n5. Sair\n");
        scanf("%i", &option);
        switch (option) {
            case 1:
                printf("Digite o endereco do bloco: ");
                scanf("%i", &option);
                print_block_info(option);
                break;
            case 2:
                printf("Digite o endereço da carteira: ");
                scanf("%i", &option);
                if (option < 0 || option > 256) break;
                printf("%i bitcoins\n", (int) wallets[option - 1]);
                break;
            case 3:
                option = get_richer_wallet(wallets);
                printf("Carteira %i com %i bitcoins", option + 1, wallets[option]);
                break;
            case 4:
                printf("--------------------------------------------------------\n");
                for (int i = 0; i < 256; i++) 
                    printf("Carteira %i: %i bitcoins\n", i + 1, wallets[i]);
                break;
            case 5:
                return;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
}

void print_block_info(unsigned char block_index) {
    FILE *txt = fopen(BLOCKCHAIN_FILE_TXT, "r");
    if (txt == NULL) exit(EXIT_FAILURE);
    
    fseek(txt, (long) -700 * (block_index - 1), SEEK_SET);
    char buffer[700] = { 0 };
    fscanf(txt, "%700s", buffer);
    
    printf("id %4s\n", buffer);
    printf("data ");
    for (int i = 0; i < 184 * 3; i++) 
        printf("%02x", buffer[20]);
    printf("\n");
    printf("hash bloco anterior ");
    for (int i = 0; i < 65; i++) 
        printf("%02x", buffer[572]);
    printf("\n");
    printf("hash block ");
    for (int i = 0; i < 65; i++) 
        printf("%02x", buffer[637]);
    printf("\n");

    fclose(txt);
}

int get_richer_wallet(wallets_vec wallets) {
    int val = wallets[0], pos = 0;
    for (int i = 0; i < 256; i++) {
        if (val < wallets[i]) {
            val = wallets[i];
            pos = i;
        }
    }
    return pos;
}