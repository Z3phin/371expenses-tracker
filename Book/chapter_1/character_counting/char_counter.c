#include <stdio.h>

main() {

    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
        ;
    
    prinf("%.0f\n", nc);

}