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

        // ------------------------------------------------
        //                  Constructor
        // ------------------------------------------------

        /// @brief Constructs an ExpenseTracker object
        ExpenseTracker();

        // ------------------------------------------------
        //                  Deconstructor
        // ------------------------------------------------

        /// @brief Desconstructs the ExpenseTracker object
        ~ExpenseTracker();

        // ------------------------------------------------
        //                  Property Functions
        // ------------------------------------------------        

        /// @brief Returns the size (number of categories) of the ExpenseTracker object. 
        /// @return number of categories.
        unsigned int size() const noexcept;

        // ------------------------------------------------
        //               Category Operations
        // ------------------------------------------------ 

        /// @brief Creates a new Category and adds it to the ExpenseTracker and returns it
        /// as a reference, or returns a reference to an existing category if it has the 
        /// same identifier. 
        /// @param categoryIdent identifier of new category.
        /// @return reference to new or already existing category.
        Category& newCategory(const std::string &categoryIdent);

        /// @brief Adds the given Category object to the ExpenseTracker. If the ExpenseTracker 
        /// already contains a category with the same identifier, the contents of the given category
        /// are merged with the existing one. 
        /// @param category category object to be added. 
        /// @return True if added successfully, otherwise false if merged. 
        /// @throws std::runtime_error exception if the operation was unsuccessful for some reason.
        bool addCategory(const Category &category);        

        // ------------------------------------------------
        //               JSON File Operations
        // ------------------------------------------------ 

        // ------------------------------------------------
        //               Operator Functions
        // ------------------------------------------------ 

        // ------------------------------------------------
        //               JSON Representation
        // ------------------------------------------------

        // ------------------------------------------------
        //               Helper Functions
        // ------------------------------------------------
        
        
};

#endif // EXPENSETRACKER_H
