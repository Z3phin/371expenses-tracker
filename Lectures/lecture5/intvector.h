#ifndef IV_H
#define IV_H

struct intvector {
    int *pData;
    unsigned int pos;
    unsigned int length;

} typedef intvector_t ;

void intvector_construct(intvector_t * const iv, 
                         const unsigned int length);

void intvector_destruct(intvector_t * const iv);

void intvector_push(intvector_t * const iv, 
                    const int value);

int intvector_pop(intvector_t * const iv);

void intvector_resize(intvector_t * const iv, 
                      const unsigned int new_length);

void intvector_print(const intvector_t * const iv);

void intvector_copy_construct(intvector_t * const x, 
                              const intvector_t * const x_other);

void intvector_copy_assign(intvector_t * const x, 
                              const intvector_t * const x_other);

#endif

