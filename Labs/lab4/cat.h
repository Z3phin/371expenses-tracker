#ifndef CAT_H
#define CAT_H

#include <string>
#define DEFAULT_LIVES 9
#define DEFAULT_NAME "Tom"

class Cat {
    private:
        std::string name;
        unsigned int lives;

    public:
        Cat();
        Cat(std::string name); 
        Cat(std::string name, unsigned int lives);
        Cat(Cat&& other);
        ~Cat();

        const std::string get_name() const;
        const unsigned int get_lives() const;
        void set_name(const std::string name);
        void set_lives(const unsigned int lives);
        Cat& operator=(Cat&& other);
};

#endif