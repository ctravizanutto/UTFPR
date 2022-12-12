#ifndef _H_BLOCKCHAIN
#define _H_BLOCKCHAIN

#include "openssl/crypto.h"
#include "openssl/sha.h"

struct unmined_block {
    unsigned int index;
    unsigned int nonce;
    unsigned char data[184];
    unsigned char prev_hash[SHA256_DIGEST_LENGTH];
};
typedef struct unmined_block unmined_block;

struct mined_block {
	unmined_block block;
	unsigned char hash[SHA256_DIGEST_LENGTH];
};
typedef struct mined_block mined_block;

#endif // _H_BLOCKCHAIN