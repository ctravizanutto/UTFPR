#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef uint64_t i64;

// time measurement variables
clock_t start, end;
double ex_time;

struct pix {
    i64 R, G, B;
};
typedef struct pix pix;

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const i64 SIZE = (i64) strtol(argv[1], NULL, 10);
    
    
    pix *color[SIZE];
    for (i64 i = 0; i < SIZE; i++)
        color[i] = malloc(SIZE * sizeof(pix));
    
    
    // benchmark start
    start = clock();
    

    // code to be tested
    for (i64 i = 0; i < SIZE; i++) 
        for (i64 j = 0; j < SIZE; j++) {
            color[i][j].R = color[i][j].R + color[i][j].G + color[i][j].B;
        }

    // benchamark end
    end = clock();
    ex_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf\n", ex_time);
    
    for (i64 i = 0; i < SIZE; i++)
        free(color[i]);

    return 0;
}