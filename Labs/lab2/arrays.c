#include "arrays.h"

double mean(int length, int* arr) {

    int i;
    double sum = 0.0;
    for (i = 0; i < length; i++) {
        sum += arr[i]; 
    }

    return sum / length;
}