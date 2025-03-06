// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// A Category contains one or more Expense Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include "item.h"
#include "date.h"
#include <string>
#include <map>

class Category {
    private:
        std::string ident;  
        std::map<const std::string, Item*> itemMap;      
    
    public:

        // ------------------------------------------------
        //                  Constructors
        // ------------------------------------------------

        /// @brief Constructor for category. 
        /// @param _ident Category identifier.
        Category(const std::string &_ident) noexcept; 

        // ------------------------------------------------
        //                  Deconstructor
        // ------------------------------------------------

        /// @brief Deconstructor for category object. 
        ~Category(); 

        // ------------------------------------------------
        //          Category Property Functions
        // ------------------------------------------------

        /// @brief Returns number of Items in the category. 
        /// @return Numer of Items in the Category. 
        unsigned int size() const noexcept;

        /// @brief Returns the identifier for the category.
        /// @return Category identifier. 
        std::string getIdent() const noexcept;

        // ------------------------------------------------
        //                     Setters      
        // ------------------------------------------------

        /// @brief Updates the category identifier to a new identifier. 
        /// @param _ident New identifier for category. 
        void setIdent(const std::string &_ident) noexcept;

        // ------------------------------------------------
        //                  Item Operations
        // ------------------------------------------------

        /// @brief Creates a new Item object with the given properties and adds it to the category.
        /// If an item with the given identifier already exists, it will will be overwritten by the new object. 
        /// @param _identifier identifier of the new Item object. 
        /// @param _description description of the new Item object. 
        /// @param _amount amount of the new Item object. 
        /// @param _date date of the new Item object. 
        /// @return Reference to the new Item object.
        Item& newItem(const std::string &_identifier, 
                      const std::string &_description, 
                      const double &_amount,
                      const Date &_date);

        /// @brief Adds the given Item object to the Category or merges with an existing
        /// Item in the Category if it shares the same identifier.  
        ///
        /// If a merge occurs, the tags of the objects will be merged, and the description,  
        /// amount and date of the new Item will be overwrite the exising item. 
        /// @param item item to be added
        /// @return True if the item was added, false if it was merged with an existing object. 
        bool addItem(const Item &_item) noexcept;

        /// @brief Attempts to find an Item in the Category with the given identifier 
        /// @param identifier identifier of Item to be retrieved
        /// @return Reference to the Item only if it is in this Category. 
        /// @throws std::out_of_range exception if an Item with a matching identifier
        /// could not be found.
        Item& getItem(const std::string _identifier) const;

        /// @brief Returns the sum of all Item amounts in the Category
        /// @return sum of all amounts. If no items are in this category, returns 0.
        double getSum() const noexcept;  

        /// @brief Deletes the Item with the matching identifier from the Category. 
        /// @param _identifier Identifier of item to be deleted. 
        /// @return True only if the item was deleted.
        /// @throws std::out_of_range exception if the Item with the given identifier
        /// could not be found in the category.
        bool deleteItem(const std::string &_identifier);
    
        // ------------------------------------------------
        //              Operator Functions
        // ------------------------------------------------
        
        /// @brief Compares two Category objects based on their identifier and Item objects 
        /// they contain and returns if they are equal or not. 
        /// @param lhs left hand side Category object. 
        /// @param rhs right hand side Category object. 
        /// @return True if the two categories have the same identifier and equal Items, otherwise false.
        friend bool operator==(const Category &lhs, const Category &rhs) noexcept;

        /// @brief Compares two Category objects based on their identifier and Item objects 
        /// they contain returns if they are not equal. 
        /// @param lhs left hand side Category object. 
        /// @param rhs right hand side Category object. 
        /// @return True if the two categories do not have the same identifier and equal Items, otherwise false.
        friend bool operator!=(const Category &lhs, const Category &rhs) noexcept;

        // ------------------------------------------------
        //              JSON Representation
        // ------------------------------------------------

        /// @brief Returns a JSON representation string of this Category.
        ///
        /// {"item1Identifer":--ITEM JSON --,"item1Identifer":--ITEM JSON --, ... , "itemNIdentifer":--ITEM JSON --}
        ///
        /// @return JSON representation of this Category
        std::string str() const noexcept;
};

#endif // CATEGORY_H
