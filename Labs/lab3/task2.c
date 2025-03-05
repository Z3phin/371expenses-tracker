// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
//
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <stdio.h>

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
  
  int i;
  unsigned int mostNeighboursIndex = 0; 
  unsigned int maxNeighbours = constituencies[0].numNeighbours;
  unsigned int leastNeighboursIndex = 0;
  unsigned int minNeighbours = constituencies[0].numNeighbours;

  for (i = 0; i < NUM_CONSTITUENCIES; i++) {
      printConstituency(&constituencies[i]);

      if (constituencies[i].numNeighbours > maxNeighbours) { 
          mostNeighboursIndex = i;
          maxNeighbours = constituencies[i].numNeighbours;        
      } 
      if (constituencies[i].numNeighbours < minNeighbours) {
          leastNeighboursIndex = i;
          minNeighbours = constituencies[i].numNeighbours;
      }
     
  }
  printf("\n");


  int j;
  // Most neighbours
  printf("%s has the most bordering constituencies:\n", 
          constituencies[mostNeighboursIndex].name);   

  for (j = 0; j < constituencies[mostNeighboursIndex].numNeighbours; j++) {
      unsigned int neighbour = constituencies[mostNeighboursIndex].neighbours[j];
      printf("\t%s\n", constituencies[neighbour].name);
  } 

  printf("\n");

  // least neighbours
  printf("%s has the least bordering constituencies:\n", 
          constituencies[leastNeighboursIndex].name);    

  for (j = 0; j < constituencies[leastNeighboursIndex].numNeighbours; j++) {
      unsigned int neighbour = constituencies[leastNeighboursIndex].neighbours[j];
      printf("\t%s\n", constituencies[neighbour].name);
  }   
  
  // destruct each constituency
  for(i = 0; i < NUM_CONSTITUENCIES; i++) {
      destructConstituency(&constituencies[i]);   
  }
  
  return 0;
}