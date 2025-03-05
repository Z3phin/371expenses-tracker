#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

struct Constituency {
    char *name;
    unsigned int *neighbours;
    unsigned int numNeighbours;

} typedef Constituency_t;

void constructConstituency(Constituency_t * const c,
                           char * const name,
                           const unsigned int * const neighbours,
                           unsigned int const numNeighbours);
void destructConstituency(Constituency_t * const c);
void printConstituency(Constituency_t * const c);
void copyConstituency(
    Constituency_t * const c, 
    Constituency_t * const c_other);
    
Constituency_t* copyConstituencies(
        Constituency_t * const constituencies, 
        const unsigned int numConstituencies);

#endif