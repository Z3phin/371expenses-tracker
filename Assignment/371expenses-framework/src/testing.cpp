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
    c.newItem("1", "new test", 99.99, Date()).addTag("hi"); 
    c.addItem(Item("2", "another test", 99.99, Date()));

    Category c1{"categoryIdent"}; 
    c1.newItem("1", "new test", 99.99, Date()).addTag("hi");
    c1.addItem(Item("2", "another test", 99.99, Date()));

    std::cout << ((c == c1) ? "true" : "false") << std::endl;
}