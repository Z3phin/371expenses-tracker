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

int main()
{
  struct Constituency test;
  constructConstituency(
      &test,
      "Swansea East",
      (unsigned int[]){1, 2, 3, 4},
      4);
  printConstituency(&test);

  printf("\n");

  destructConstituency(&test);
  return 0;
}