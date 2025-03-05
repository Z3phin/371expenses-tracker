#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

void fahrToCelsius() {
    int fahr;
    
    printf("%3s\t%7s", "fahr", "celsius\n");
    for (fahr = LOWER; fahr <= UPPER; fahr += STEP) {
        printf("%3d\t%7.1f\n", fahr, (5.0/9.0) * (fahr-32));
    }
}

void celsiusToFahr() {
    int celsius;
    
    printf("%3s\t%7s", "celsius", "fahr\n");
    for (celsius = -160; celsius <= 160; celsius += 20) {
        printf("%3d\t%7.1f\n", celsius, celsius / (5.0 / 9.0) + 32);
    }
}


int main() {
    
    fahrToCelsius();
    celsiusToFahr();

}

