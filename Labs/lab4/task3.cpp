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

bool is_digits(std::string& string) {
    for (char c : string) {
        if (!(c >= 48 && c <= 57)) {
            return false;
        }
    }
    return true; 
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0; 
    }

    const unsigned int numCats = argc / 2;

    std::cout << "Allocating clowder of size " << numCats << std::endl;
    Cat *clowder = new Cat[numCats]();

    for (int i = 0; i < numCats; i++) {
        
        std::string name = argv[i * 2 + 1];
    
        if (i == numCats - 1 && argc % 2 == 0) {
            clowder[i] = std::move(Cat(name));    
        } else {
            std::string livesStr = argv[(i+1) * 2];
            
            // Handle invalid lives data by 
            if (!is_digits(livesStr)) {
                std::cerr << "ERROR: " << livesStr 
                          << " is an invalid value for lives" 
                          << " for the cat " << name
                          << std::endl;
                delete [] clowder;
                return -1;  
            }

            unsigned int lives = std::stoul(livesStr);
 
            clowder[i] = std::move(Cat(name, lives));    
        }        
    }

    // Print out each cat in clowder
    for (int i = 0; i < numCats; i++) {
        printCat(clowder[i]);
    }

    delete [] clowder;

    return 0;
}
