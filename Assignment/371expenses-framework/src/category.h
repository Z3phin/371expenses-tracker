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

        Category(const std::string &_ident) noexcept; 

        unsigned int size() const noexcept;

        std::string getIdent() const noexcept;

        void setIdent(const std::string &_ident) noexcept;

        Item& newItem(const std::string &_identifier, 
                      const std::string &_description, 
                      const double &_amount,
                      const Date &_date);

        bool addItem(Item &_item) noexcept;

        Item& getItem(const std::string _identifier) const;

        double getSum() const noexcept;  
};

#endif // CATEGORY_H
