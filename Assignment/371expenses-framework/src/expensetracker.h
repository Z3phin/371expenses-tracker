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
        
        /// @brief Returns the category with the given identifier only if it is in the 
        /// ExpenseTracker object. 
        /// @param categoryIdentifier category to be found  
        /// @return Reference to category object with matching identifier
        /// @throws std::out_of_range exception if the category is not in the ExpenseTracker
        Category& getCategory(const std::string &categoryIdentifier) const;

        /// @brief Deletes the Category with the given identifier from the ExpenseTracker object if it exists,
        /// otherwise an exception is thrown if the identifier could not be found. 
        /// @param categoryIdentifier identifier of category to be deleted.     
        /// @return True only if the Category was deleted. 
        /// @throws std::out_of_range exception if the given category identifier could not be found.
        bool deleteCategory(const std::string &categoryIdentifier);

        /// @brief Returns the sum of all category expense sums, consisting of all individual 
        /// item amounts across all categories
        /// @return sum of all items across all categories. Returns 0 if there are no items. 
        double getSum() const noexcept;

        // ------------------------------------------------
        //               JSON File Operations
        // ------------------------------------------------ 

        /// @brief Opens a JSON file with the given file name and populates the ExpenseTracker 
        /// with its categories and items. Invalid JSON objects will be ignored.
        /// @param database JSON datbase filename.
        /// @throws exceptions may be thrown when parsing the JSON file (e.g. improper formatting)
        void load(const std::string &database);

        // ------------------------------------------------
        //               Operator Functions
        // ------------------------------------------------ 

        /// @brief Compares two ExpenseTracker objects. The two objects are equal if they have
        /// the same data, i.e. equivalent categories and items. 
        /// @param lhs left hand side object.
        /// @param rhs right hand side object.
        /// @return True if the objects are equal, otherwise false.
        friend bool operator==(const ExpenseTracker &lhs, const ExpenseTracker &rhs) noexcept;

        /// @brief Compares two ExpenseTracker objects. The two objects are not equal if they have
        /// differing data, i.e. different items or categories. 
        /// @param lhs left hand side object.
        /// @param rhs right hand side object.
        /// @return True if the objects are not equal, otherwise false.
        friend bool operator!=(const ExpenseTracker &lhs, const ExpenseTracker &rhs) noexcept;

        // ------------------------------------------------
        //               JSON Representation
        // ------------------------------------------------

        /// @brief Returns a JSON formatted string representation of the ExpenseTracker object.
        /// @return JSON formatted string representation of the object. 
        std::string str() const noexcept;

        // ------------------------------------------------
        //               Helper Functions
        // ------------------------------------------------
        
        
};

#endif // EXPENSETRACKER_H
