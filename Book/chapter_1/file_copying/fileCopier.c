#include <stdio.h>

int main() {
    int c; 

    while ((c = getchar()) != EOF) {
        putchar(c);
    }

}


// 1.6
// getchar() != EOF is 0 or 1 confirmed, I confirmed it, yep 

// 1.7
// EOF == -1