#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <openssl/crypto.h>
#include <openssl/sha.h>
#include "mtwister.h"

#define BLOCKCHAIN_SIZE 256
#define BLOCKCHAIN_FILE "blockchain.bin"

typedef struct unmined_block {
    unsigned int index;
    unsigned int nonce;
    unsigned char data[184];
    unsigned char prev_hash[SHA256_DIGEST_LENGTH];
} unmined_block;

typedef struct mined_block {
	unmined_block block;
	unsigned char hash[SHA256_DIGEST_LENGTH];
} mined_block;





#endif // _BLOCKCHAIN_H_