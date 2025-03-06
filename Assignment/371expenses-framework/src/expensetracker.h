// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// The root object that holds all data for 371expenses. This
// class contains Categories, which in turn hold Expense Items,
// which have a description, amount, and date
// -----------------------------------------------------

#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include "category.h"
#include <string>
#include <map>

class ExpenseTracker {
    private:
        std::map<std::string, Category*> categoryMap;
    public: 
        ExpenseTracker();
        ~ExpenseTracker();

};

#endif // EXPENSETRACKER_H
