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
#include "expensetracker.h"

int main() {
    ExpenseTracker e{};
    e.load("testdatabasealt.json");

    std::cout << e.str() << std::endl;

    
}