#include "intvector.h"

void main() {
    intvector_t x; 
    intvector_construct(&x, 5);
    intvector_push(&x, 9);

    intvector_t y;
    intvector_copy_construct(&y, &x);

    intvector_push(&x, 8);
    intvector_destruct(&x);
    intvector_print(&y);
    //intvector_print(&x);
}