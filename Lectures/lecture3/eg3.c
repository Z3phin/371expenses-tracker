#include <stdio.h>

int main() {
    char arr[] = {'H', 'e', 'l', 'l', 'o',',','\0'};
    char *str = "World";

    printf("%s %s\n", arr, str);
}