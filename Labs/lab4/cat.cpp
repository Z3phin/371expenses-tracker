#include "cat.h"
#include <iostream>
#include <string>

Cat::Cat() : name(DEFAULT_NAME), lives(DEFAULT_LIVES) {
    std::cout << "Default constructor called..." << std::endl;
}

Cat::Cat(std::string name) 
        : name(name), lives(DEFAULT_LIVES) {

    std::cout << "Constructor called with name..." << std::endl;
}

Cat::Cat(
    std::string name, 
    unsigned int lives) 
    : name(name), lives(lives) {

    std::cout << "Constructor called with name and lives..." << std::endl;
}

Cat::Cat(Cat&& other) 
    : name(std::move(other.name)), lives(std::move(other.lives)) {}

Cat::~Cat() {
    std::cout << "Destructor called..." << std::endl;
}

const std::string Cat::get_name() const {
    return this->name;
}

const unsigned int Cat::get_lives() const {
    return this->lives;
}

void Cat::set_name(const std::string name) {
    std::cout << "set_name called..." << std::endl;
    
    this->name = name;
}

void Cat::set_lives(const unsigned int lives) {
    std::cout << "set_lives called..." << std::endl;

    if (lives >= this->get_lives()) {
        return; 
    }

    this->lives = lives;

    if (lives == 0) {
        this->set_name("The Cat formerly known as " + this->get_name());
    }

}

Cat& Cat::operator=(Cat&& other) {

    if (this != &other) {
        std::swap(name, other.name);
        std::swap(lives, other.lives);
    }
    
    return *this;
}

