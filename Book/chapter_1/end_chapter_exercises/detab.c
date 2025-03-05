#include <stdio.h>

#define NUM_SPACES 4

int main() {
    int c; 

    while ((c=getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < NUM_SPACES; i++)
                putchar(' ');
        } else {
            putchar(c);
        }       
    }
}

