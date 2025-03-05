#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "intvector.h"

// Construct/allocate memory
void intvector_construct(
                        intvector_t * const iv, 
                        const unsigned int length) {
    iv->pData = NULL;
    iv->pos = 0;
    iv->length = 0;

    intvector_resize(iv, length);
}

// destruct/deallocate memory
void intvector_destruct(intvector_t * const iv) {
    if (iv->pData != NULL) {
        free(iv->pData);
        iv->pData = NULL;
    }
    iv->pos = 0;
    iv->length = 0;
}

// push/add an item
void intvector_push(intvector_t * const iv, const int value) {
    if (iv->pos > iv->length - 1) {
        intvector_resize(iv, iv->length * 2);
    }

    iv->pData[iv->pos++] = value;
}

// pop/delete an item
int intvector_pop(intvector_t * const iv) {
    if (iv->pos <= 0) {
        printf("Cannot pop item from vector!\n");
        return 0; 
    }
    return iv->pData[--(iv->pos)];
}

// resize function (to grow or shrink)
void intvector_resize(intvector_t * const iv, const unsigned int new_length) {
    if (new_length > 0) {
        iv->pData = (int*) realloc(iv->pData, sizeof(int) * new_length);
        iv->length = new_length;
    } else {
        intvector_destruct(iv);
    }
        
}

//print function
void intvector_print(const intvector_t * const iv) {
    printf("[");
    for (int i = 0; i < iv->pos; i++) {
        printf("%d, ", iv->pData[i]);
    }

    printf("]\n (used capacity = %d, spare %d, total = %d)\n",
        iv->pos,
        iv->length - iv->pos,
        iv->length
    );

}

// Copies contents of x_other to x, assuming x has not been initialised
void intvector_copy_construct(intvector_t * const x, const intvector_t * const x_other){

    intvector_construct(x, x_other->length);
    memcpy(x->pData, x_other->pData, x->length * sizeof(int));
    x->pos = x_other->pos;
}

void intvector_copy_assign(intvector_t * const x, const intvector_t * const x_other) {

    intvector_resize(x, x_other->length);
    memcpy(x->pData, x_other->pData, x->length * sizeof(int));
    x->pos = x_other->pos;
}