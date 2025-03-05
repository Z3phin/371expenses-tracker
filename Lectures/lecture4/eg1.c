#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int main() {

    // Request for 40 bytes of memory
    int *A = (int*) malloc(ARRAY_SIZE * sizeof(int));

    int i;

    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("A[%d] is at %p\n", i, A+i);
        A[i] = i * 2;
    }

    free(A);
    A = NULL;

}
