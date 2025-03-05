#include <stdio.h>

#define MAXLINE 1000

int max;
char line[MAXLINE];
char longest[MAXLINE];


int getline(void);
void copy(void);

int main() {
    int len;

    // The use of extern is redundant as the variables are declared earlier in the file.
    extern int max;
    extern char longest[MAXLINE];

    max = 0;
    while ((len = getline() > 0)) {
        if (len > max) {
            max = len;
            copy();
        }
    }

    if (max > 0) {
        printf("%s", longest);
    }
    return 0;
}

int getline(void) {
    int c;
    int i;

    extern char line[];

    for (i = 0; i < MAXLINE - 1 
        && ((c=getchar()) != EOF && c !='\n');
        ++i ) {

            line[i] = c;

    } 

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i; 

}

void copy (void) {
    int i;

    extern char line[];
    extern char longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0') {
        i++;
    }
}