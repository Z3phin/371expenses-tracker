#include <iostream>
#include <ctime>
#include <string>
#include <regex>
#include <list>
#include <set>
#include <map>
#include "date.h"
#include "item.h"
#include "category.h"

int main() {
    Category c{"categoryIdent"};    
    std::cout << c.size() << std::endl; 

    Item i = c.newItem("1", "test", 99.99, Date());
    std::cout << i.str() << std::endl;
    std::cout << c.size() << std::endl; 

    Item i1 = c.newItem("1", "new test", 99.99, Date());
    std::cout << i1.str() << std::endl;
    std::cout << c.size() << std::endl; 

    Item i2 = Item("2", "another test", 99.99, Date());
    bool r = c.addItem(i2);
    std::cout << c.size() << std::endl; 

    std::cout << c.getSum() << std::endl;
    
}