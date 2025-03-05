// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
//
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <iostream>
#include "cat.h"

void printCat(Cat& cat) {
    std::cout << cat.get_name() << " has "
              << cat.get_lives() << " lives." << std::endl;
}

int main(int argc, char* argv[]) {
    Cat a("Garfield");
    
    printCat(a);
              
    Cat b("Mog" , 10);
    printCat(b);

    b.set_lives(42);
    printCat(b);

    b.set_name("Prince");
    printCat(b);

    b.set_lives(8);
    printCat(b);

    b.set_lives(0);
    printCat(b);

    b.set_lives(0);
    printCat(b);

    return 0;
}
