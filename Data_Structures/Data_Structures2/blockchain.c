#include <stdlib.h>
#include <stdio.h>
#include "libs/utils.h"

int main(void) {
    MTRand rand_number = seedRand(123456);

    unmined_block *main_block = calloc(1, sizeof(unmined_block));

    for (int i = 0; i < 10000; i++) {
        
    }


    free(main_block);
    return 0;
}   