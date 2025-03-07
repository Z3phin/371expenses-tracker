#include <iostream>
#include <ctime>
#include <string>
#include <regex>
#include <list>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include "date.h"
#include "item.h"
#include "category.h"
#include "expensetracker.h"

int main() {


    ExpenseTracker etObj1{};
    const std::string cIdent1 = "Studies";
    const std::string cIdent2 = "Travel";

    const std::string iIdent1 = "1";
    const std::string iIdent2 = "2";

    const std::string iDesc1 = "C++ Book";
    const std::string iDesc2 = "Bus Pass";

    const double amount1 = 39.99;
    const double amount2 = 164.0;

    const std::string tag1 = "uni";
    const std::string tag2 = "programming";

    const int year = 2024;
    const int month = 12;
    const int day = 25;
    const int day2 = day + 1;
    const Date date1 = Date(year, month, day);
    const Date date2 = Date(year, month, day2);

    Item iObj1{iIdent1, iDesc1, amount1, date1};
    Item iObj2{iIdent2, iDesc2, amount2, date2};

    iObj1.addTag(tag1);
    iObj1.addTag(tag2);
    iObj2.addTag(tag1);

    Category cObj1{cIdent1};
    Category cObj2{cIdent2};

    cObj1.addItem(iObj1);
    cObj1.addItem(iObj1);
    cObj2.addItem(iObj2); 

    // etObj1.addCategory(cObj1);
    // etObj1.addCategory(cObj2);

    // etObj1.save("testdatabasealt.json");

    // std::string testStr = "{\"Studies\":{\"1\":{\"amount\":39.99,\"date\":\"2024-12-25\","
    //              "\"description\":\"C++ Book\","
    //              "\"tags\":[\"uni\"," "\"programming\"]}},\"Travel\":"
    //              "{\"2\":{\"amount\":164.0,\"date\":\"2024-12-26\",\"description\":\"Bus "
    //              "Pass\"," "\"tags\":[\"uni\"]}}}";

    // std::cout << etObj1.str().find(testStr) << std::endl;

    
}