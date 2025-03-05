#include "cat.h"
#include <iostream>
#include <string>
#include <functional>
#include <sstream>

Cat::Cat() : name(DEFAULT_NAME), lives(DEFAULT_LIVES) {}

Cat::Cat(const std::string &_name) 
        : name(_name), lives(DEFAULT_LIVES) {}

Cat::Cat(const std::string &_name, const unsigned int &_lives) 
    : name(_name), lives(_lives) {}

const std::string Cat::get_name() const {
    return this->name;
}

const unsigned int Cat::get_lives() const {
    return this->lives;
}

void Cat::set_name(const std::string &name) {
    this->name = name;
}

void Cat::set_lives(const unsigned int &lives) {
    if (lives >= this->get_lives()) {
        return; 
    }

    this->lives = lives;

    if (lives == 0) {
        this->set_name("The Cat formerly known as " + this->get_name());
    }

}

bool operator==(const Cat& lhs, const Cat& rhs) {
    return (lhs.name == rhs.name && lhs.lives == rhs.lives);
}

bool operator<(const Cat& lhs, const Cat& rhs) {
    if (lhs.name == rhs.name) {
        return (lhs.lives < rhs.lives);
    }
    return (lhs.name < rhs.name);
}



std::ostream &operator<<(std::ostream &os, const Cat& cat) {
    os << cat.name << " has " << cat.lives << " lives...";
    return os; 
}

std::size_t std::hash<Cat>::operator()(const Cat &obj) const {
    std::stringstream ss;
    ss << obj;

    std::size_t computed_hash; 
    computed_hash = std::hash<std::string>()(obj.get_name());
    computed_hash ^= std::hash<unsigned int>()(obj.get_lives());
    computed_hash ^= std::hash<std::string>()(ss.str());

    return computed_hash;
}




