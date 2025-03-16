// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
//
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <iostream>
#include <random>
#include "Shape.h"

int main(int argc , char *argv[]) {

    Shape **xs = new Shape*[10];

    xs[0] = new Circle(0, 0, 1);
    xs[1] = new Rectangle(0, 1, 1, 0);
    xs[2] = new Triangle(0, 0, 1, 1, 0, 1);

    for (int i = 3; i < 10; i++) {
        if (!(i % 3)) {
            xs[i] = new Triangle(
                rand(),
                rand(),
                rand(),
                rand(),
                rand(),
                rand()
            );
        } else if (!(i % 2)) {
            xs[i] = new Rectangle(
                rand(),
                rand(),
                rand(),
                rand()
            );
        } else {
            xs[i] = new Circle(
                rand(),
                rand(),
                rand()
            );
        }
          
    }

    for (int i = 0; i < 10; i++) {
        std::cout << xs[i]->to_string() << std::endl;
    }
   
    std::cout << "\n\n NEW RANDOM CENTRES \n" << std::endl;
    
    for (int i = 0; i < 10; i++) {
        xs[i]->centre_at(
            rand(),
            rand());
    }

    for (int i = 0; i < 10; i++) {
        std::cout << xs[i]->to_string() << std::endl;
    }

    
    for (int i = 0; i < 10; i++) {
        delete xs[i];
    }
    delete xs; 



    Shape *x = new Triangle(0,0,1,1,0,1); // x, y, r
    
    std::cout << x->to_string() << std::endl;
    x->centre_at(2, 3);
    
    std::cout << x->to_string() << std::endl;
    
    delete x;
    return 0;
}
