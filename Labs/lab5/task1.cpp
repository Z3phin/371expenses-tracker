// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
//
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <iostream>

#include "cat.h"

int main(int argc, char* argv []) {
  Cat a("Garfield" , 42);
  
  std::cout << std::hash<Cat>()(a) << " = " << a << std:: endl;

  // Note the double ()() syntax!

  // std::hash <Cat>() default constructs an
  // object of type std::hash<Cat>
  
  // std::hash<Cat>()(a) invokes the call
  // operator () on that object with parameter
  
  // std::hash<Cat>()(a) returns an unsigned long integer

  return 0;
}
