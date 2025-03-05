#ifndef CAT_H
#define CAT_H

#include <string>
#include <iostream>
#define DEFAULT_LIVES 9
#define DEFAULT_NAME "Tom"

class Cat {
    private:
        std::string name;
        unsigned int lives;

    public:
        Cat();
        Cat(const std::string &_name); 
        Cat(const std::string &_name, const unsigned int &_lives);

        const std::string get_name() const;
        const unsigned int get_lives() const;
        void set_name(const std::string &name);
        void set_lives(const unsigned int &lives);
        friend std::ostream &operator<<(std::ostream &os, const Cat& cat);
        friend bool operator==(const Cat& lhs, const Cat& rhs);
        friend bool operator<(const Cat& lhs, const Cat& rhs);
};

namespace std {
    template<>
    struct hash <Cat>  {
        size_t operator()(const Cat &obj) const;
    };
}



#endif