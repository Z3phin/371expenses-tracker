#include <stdio.h>

#define ARRAY_LENGTH 27
#define OTHER_INDEX 26

int main() {

    int c;
    // SETUP ARRAY
    int chars[ARRAY_LENGTH];
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        chars[i] = 0; 
    }

    //GET CHARS FROM FILE 

    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            ++chars[c - 'a'];
        } else if (c >= 'A' && c <= 'Z') {
            ++chars[c - 'A'];
        } else {
            ++chars[OTHER_INDEX];
        }

    }
    
    // PRINT OUT HISTOGRAM
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        int frequency = chars[i];

        if ( i < 26) 
            printf("%c |", i + 'a');
        else 
            printf("? |");

        for (int j = 0; j < frequency; j++ ) {
            printf("#");
        }
        printf("\n");
    }
}