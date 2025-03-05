// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
//
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "constituency.h"

#define NUM_CONSTITUENCIES 5

int main()
{
  Constituency_t constituencies[NUM_CONSTITUENCIES];

  constructConstituency(
      &constituencies[0], 
      "Swansea East", 
      (unsigned int[]) {1, 2, 3, 4},
      4
  );

  constructConstituency(
      &constituencies[1], 
      "Swansea West", 
      (unsigned int[]) {0, 2},
      2
  );

  constructConstituency(
      &constituencies[2], 
      "Gower", 
      (unsigned int[]) {0, 1, 3},
      3
  );

  constructConstituency(
      &constituencies[3], 
      "Neath", 
      (unsigned int[]) {0, 2, 4},
      3
  );

  constructConstituency(
      &constituencies[4], 
      "Aberavon", 
      (unsigned int[]) {0, 3},
      2
  );

    // Make copies
  Constituency_t * copy = copyConstituencies(constituencies, NUM_CONSTITUENCIES);  

  // Destroy originals
  int i;
  for (i = 0; i < NUM_CONSTITUENCIES; i++) {
    destructConstituency(&constituencies[i]);      
  }  

  unsigned int mostNeighboursIndex = 0; 
  unsigned int maxNeighbours = copy[0].numNeighbours;
  unsigned int leastNeighboursIndex = 0;
  unsigned int minNeighbours = copy[0].numNeighbours;

  for (i = 0; i < NUM_CONSTITUENCIES; i++) {
      printConstituency(&copy[i]);

      if (copy[i].numNeighbours > maxNeighbours) { 
          mostNeighboursIndex = i;
          maxNeighbours = copy[i].numNeighbours;        
      } 
      if (copy[i].numNeighbours < minNeighbours) {
          leastNeighboursIndex = i;
          minNeighbours = copy[i].numNeighbours;
      }
     
  }
  printf("\n");


  int j;
  // Most neighbours
  printf("%s has the most bordering constituencies:\n", 
          copy[mostNeighboursIndex].name);   

  for (j = 0; j < copy[mostNeighboursIndex].numNeighbours; j++) {
      unsigned int neighbour = copy[mostNeighboursIndex].neighbours[j];
      printf("\t%s\n", copy[neighbour].name);
  } 

  printf("\n");

  // least neighbours
  printf("%s has the least bordering constituencies:\n", 
          copy[leastNeighboursIndex].name);    

  for (j = 0; j < copy[leastNeighboursIndex].numNeighbours; j++) {
      unsigned int neighbour = copy[leastNeighboursIndex].neighbours[j];
      printf("\t%s\n", copy[neighbour].name);
  }   
  
  // destruct each constituency
  for(i = 0; i < NUM_CONSTITUENCIES; i++) {
      destructConstituency(&copy[i]);   
  }

  free(copy);

  return 0;
}