#include <stdio.h>

#define ARRAY_LENGTH 9

int main() {
    int an_array[ARRAY_LENGTH];

    int i;
    for  (i = 0; i < ARRAY_LENGTH; i++) {
        an_array[i] = i * 2;
    }

    printf("Value at index 2 is %d\n", an_array[2]);

    int *ptr = (int*) an_array;
    printf("Starting address of array is %p\n", ptr);
    printf("Value at index 2 is %d\n", (int) *(ptr+2));
    printf("Value at index 11 is %d\n", (int) ptr[11]);

    

}