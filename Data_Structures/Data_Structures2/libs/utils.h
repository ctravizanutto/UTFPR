// Augusto Padilha - 2374960
// Cainan Travizanutto e Silva - 2407248
// Caio Furlan - 2407256
// Gabriel Maestre - 2422611

#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <openssl/crypto.h>
#include <openssl/sha.h>
#include "mtwister.h"

#define BLOCKCHAIN_SIZE 256
//#define BLOCKCHAIN_FILE_BIN "files/blockchain.bin"
//#define BLOCKCHAIN_FILE_TXT "files/blockchain.txt"
#define BLOCKCHAIN_FILE_BIN "../files/blockchain.bin"
#define BLOCKCHAIN_FILE_TXT "../files/blockchain.txt"


typedef int wallets_vec[BLOCKCHAIN_SIZE];

typedef struct unmined_block {
    unsigned int index;
    unsigned int nonce;
    unsigned char data[184];
    unsigned char prev_hash[SHA256_DIGEST_LENGTH];
} unmined_block;

typedef struct mined_block {
	struct unmined_block block;
	unsigned char hash[SHA256_DIGEST_LENGTH];
} mined_block;

typedef struct blocks_store_handle {
    unsigned int size;
    struct mined_block block0;
    struct mined_block block1;
} blocks_store_handle;

void save_blocks_to_file(blocks_store_handle *blocks_handle);
void save_wallets_to_file(wallets_vec wallets);

#endif // _BLOCKCHAIN_H_