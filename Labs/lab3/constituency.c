#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constituency.h"

void constructConstituency(Constituency_t * const c,
                           char * const name,
                           const unsigned int * const neighbours,
                           unsigned int const numNeighbours){

    if (c == NULL || name == NULL || neighbours == NULL) {
        return; 
    }

    c->name = NULL;
    c->neighbours = NULL;
    c->numNeighbours = 0;

    int nameLength = strlen(name);
    c->name = (char *) malloc(sizeof(char) * (nameLength + 1));
    strcpy(c->name, name);

    if (numNeighbours > 0) {
        c->neighbours = (unsigned int *) malloc(sizeof(unsigned int) * numNeighbours);
        memcpy(c->neighbours, neighbours, sizeof(unsigned int) * numNeighbours);
    }

    c->numNeighbours = numNeighbours;


}

void destructConstituency(Constituency_t * const c) {
    if (c == NULL) {
        return; 
    }
    
    if (c->name != NULL) {
        free(c->name);
        c->name = NULL;
    }
    if (c->neighbours != NULL) {
        free(c->neighbours);
        c->neighbours = NULL;
    }
    c->numNeighbours = 0; 
}

void printConstituency(Constituency_t * const c) {
    if (c == NULL || c->name == NULL || c->neighbours == NULL) {
        return;
    }

    printf("%-12s | %d neighbours | [ ", c->name, c->numNeighbours);
    int i;
    for (i = 0; i < c->numNeighbours; i++) {
        printf("%d ", c->neighbours[i]);
    } 
    printf("]\n");
}

void copyConstituency(Constituency_t * const c, Constituency_t * const c_other) {
    if (c == NULL || c_other == NULL) {
        return;
    }

    constructConstituency(
        c, 
        c_other->name, 
        c_other->neighbours, 
        c_other->numNeighbours);    
}

Constituency_t* copyConstituencies(Constituency_t * const constituencies, const unsigned int numConstituencies) {
    if (numConstituencies == 0) {
        return NULL;
    }

    Constituency_t * constituencies_copy = (Constituency_t*) malloc(sizeof(Constituency_t) * numConstituencies);

    int i;
    for (i = 0; i < numConstituencies; i++) {
        copyConstituency(&constituencies_copy[i], &constituencies[i]);
    }

    return constituencies_copy;
}