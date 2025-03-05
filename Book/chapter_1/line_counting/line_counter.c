#include <stdio.h>

int main() {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            printf("[NEWLINE]");
        } else if (c == '\t') {
            printf("[TAB]");
        } else if (c == ' ') {
            printf("[BLANK]");
        } else {
            putchar(c);
        }
    }
    
}