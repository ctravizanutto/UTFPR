#include "utils.h"

void save_blocks_to_file(blocks_store_handle *blocks_handle) {
    FILE *bin = fopen(BLOCKCHAIN_FILE_BIN, "ab");
    if (bin == NULL) exit(EXIT_FAILURE);

    FILE *txt = fopen(BLOCKCHAIN_FILE_TXT, "a");
    if (txt == NULL) exit(EXIT_FAILURE);

    fwrite(&(blocks_handle->block0), 1, sizeof(mined_block), bin);
    fprintf(bin, "\n");
    fwrite(&(blocks_handle->block1), 1, sizeof(mined_block), bin);
    fprintf(bin, "\n");

    fprintf(txt, "%10i%10i", blocks_handle->block0.block.index, blocks_handle->block0.block.nonce);
    for(int x = 0; x < 184; x++)
        fprintf(txt, "%3i", blocks_handle->block0.block.data[x]);
    for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
        fprintf(txt, "%02x", blocks_handle->block0.block.prev_hash[x]);
    for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
        fprintf(txt, "%02x", blocks_handle->block0.hash[x]);
    fprintf(txt, "\n");

    fprintf(txt, "%10i%10i", blocks_handle->block1.block.index, blocks_handle->block1.block.nonce);
    for(int x = 0; x < 184; x++)
        fprintf(txt, "%3i", (int) blocks_handle->block1.block.data[x]);
    for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
        fprintf(txt, "%02x", blocks_handle->block1.block.prev_hash[x]);
    for(int x = 0; x < SHA256_DIGEST_LENGTH; x++)
        fprintf(txt, "%02x", blocks_handle->block1.hash[x]);
    fprintf(txt, "\n");
    
    fclose(bin);
    fclose(txt);
}

void save_wallets_to_file(wallets_vec wallets) {
    FILE *bin = fopen(BLOCKCHAIN_FILE_BIN, "ab");
    if (bin == NULL) exit(EXIT_FAILURE);

    FILE *txt = fopen(BLOCKCHAIN_FILE_TXT, "a");
    if (txt == NULL) exit(EXIT_FAILURE);

    fwrite(wallets, sizeof(int), 256, bin);
    for (int i = 0; i < 256; i++)
        fprintf(txt, "%10i", wallets[i]);

    fclose(bin);
    fclose(txt);
}