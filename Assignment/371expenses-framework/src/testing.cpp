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
    c.newItem("1", "test", 99.99, Date()); 
    c.newItem("1", "WHAT", 10.99, Date());
    c.addItem(Item("2", "another test", 45.01, Date()));

    c.getItem("2").addTag("hi");
    Item i = Item("2", "Updated add item test", 45.01, Date());
    i.addTag("hello");

    c.addItem(i);

    Category c1{"categoryIdent"};  
    c1.newItem("1", "test", 99.99, Date()); 
    c1.newItem("1", "WHAT", 10.99, Date());
    c1.addItem(Item("2", "another test", 45.01, Date()));

    std::cout << c.str() << std::endl;

    
}