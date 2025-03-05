#include <stdio.h>

#define MAX_CHARS_PER_LINE 20
#define MAX_CHAR_OVERFLOW 5

int main() {
    int c;
    int n;

    n = 0;
    while ((c = getchar()) != EOF) {
        if (n >= MAX_CHARS_PER_LINE) {
            if ((c == ' ' || c == '\t')) {
                putchar('\n');
                n = 0;
            } else if (n >= MAX_CHARS_PER_LINE + MAX_CHAR_OVERFLOW){
                printf("-\n");
                n = 0;
            }
        }

        putchar(c);
        ++n;
    }
}