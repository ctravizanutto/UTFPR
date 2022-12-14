// Augusto Padilha - 2374960
// Cainan Travizanutto e Silva - 2407248
// Caio Furlan - 2407256
// Gabriel Maestre - 2422611

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libs/utils.h"

int main(void) {
    unmined_block main_block = { 0 };
    blocks_store_handle blocks_handle = { 0 };
    unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };
    wallets_vec wallets = { 0 };
    MTRand rand_number = seedRand(1234567);
    
    for (int iteration = 0; iteration < 100; iteration++) {
        // initialize block
        main_block.index = iteration + 1;
        main_block.nonce = 0;
        unsigned char transaction_count = (unsigned char) (1 + (genRandLong(&rand_number) % 61));
        for (int i = 0; i < (3 * transaction_count); i += 3) {
            int src_addr = genRandLong(&rand_number) % 256;
            int dest_addr = genRandLong(&rand_number) % 256;
            int coin_amount = (1 + (genRandLong(&rand_number) % 50));

            main_block.data[i] = (unsigned char) src_addr;
            main_block.data[i + 1] = (unsigned char) dest_addr;
            main_block.data[i + 2] = (unsigned char) coin_amount;
        
            wallets[src_addr] = (wallets[src_addr] - coin_amount) < 0 ? 0 : (wallets[src_addr] - coin_amount);
            wallets[dest_addr] += coin_amount;
        }
        for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
            main_block.prev_hash[x] = hash[x];

        // mine block
        while(1) {
            SHA256((unsigned char*)&main_block, sizeof(main_block), hash);
            if (hash[0] == 0 && hash[1] == 0 && hash[2] == 0) 
                break;
            main_block.nonce++;
        }
        
        // store block
        if (blocks_handle.size == 0) {
            blocks_handle.block0.block = main_block;
            for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
                blocks_handle.block0.hash[x] = hash[x];
            blocks_handle.size++; 
        } else {
            blocks_handle.block1.block = main_block;
            for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
                blocks_handle.block1.hash[x] = hash[x];
            blocks_handle.size = 0;
            save_blocks_to_file(&blocks_handle);
        }
    }
    save_wallets_to_file(wallets);

    return 0;
}   
