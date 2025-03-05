#include <stdio.h>
#include <stdlib.h>
#define ROWS 2
#define COLS 10

int main() {
    int *val[ROWS]; // Stack
    int r, c;

    for (r = 0; r < ROWS; r++) {
        val[r] = (int*) malloc(COLS * sizeof(int));
        for (c = 0; c < COLS; c++) {
            val[r][c] = r * c;
        }
        for (c = 0; c < COLS; c++) {
            printf("[%d][%d]: %d\n", r, c, val[r][c]);
        }
        free(val[r]);
    }

}