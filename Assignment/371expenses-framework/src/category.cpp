// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "category.h"
#include <iostream>
#include <map>
#include <sstream>

// TODO Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};
Category::Category(const std::string &_ident) noexcept : ident(_ident), itemMap({}) {}


// TODO Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
unsigned int Category::size() const noexcept {
    return itemMap.size();
}


// TODO Write a function, getIdent, that returns the identifier for the Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
std::string Category::getIdent() const noexcept {
    return this->ident;
}


// TODO Write a function, setIdent, that takes one parameter, a string for a new
// Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(const std::string &_ident) noexcept {
    this->ident = _ident;
}


// TODO Write a function, newItem, that takes four parameters, an Item
// identifier (string), description (string), amount (double), and date (Date)
// and returns the Item object as a reference.  If an object with the same
// identifier already exists, then the existing object should be overwritten by
// the new Item. Throw a std::runtime_error if the Item object cannot be
// inserted into the container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
Item& Category::newItem(const std::string &_identifier, 
                        const std::string &_description, 
                        const double &_amount,
                        const Date &_date) {
    

        Item* pNewItem = new Item(_identifier, _description, _amount, _date);
        
        try {
            
            auto result = itemMap.emplace(std::make_pair(_identifier, pNewItem));
            auto pair = *result.first;
            if (!result.second) {
                pair.second = pNewItem;
            }

            return *pair.second;

        } catch (const std::exception &ex) {
            delete pNewItem; // necessary? could this cause issues
            throw std::runtime_error(ex.what());
        }

}

// TODO Write a function, addItem, that takes one parameter, an Item object, and
// returns true if the object was successfully inserted. If an object with the
// same identifier already exists, then:
//  - the tags should be merged
//  - description should be overwritten by the item being added
//  - amount should be overwritten by the item being added
//  - date overwritten by the item being added
//  - false should be returned.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);

void mergeTags(Item &target, const Item &other) {
    auto otherTags = other.getTags();
    for (const std::string& tag : otherTags) {
        target.addTag(tag);
    }
}

bool Category::addItem(const Item &item) noexcept {

    auto it = itemMap.find(item.getIdent());
    bool contains = it != itemMap.end();
    if (contains) {
        auto pItem = it->second; 

        mergeTags(*pItem, item);
        pItem->setDescription(item.getDescription());
        pItem->setAmount(item.getAmount());
        pItem->setDate(item.getDate());
    } else {
        Item* pNewItem = new Item(item);
        mergeTags(*pNewItem, item);
        itemMap.emplace(std::make_pair(item.getIdent(), pNewItem));
    }

    return !contains;
}

// TODO Write a function, getItem, that takes one parameter, an Item identifier
// (a string) and returns the Item as a reference. If no Item exists, throw an
// appropriate exception.
//
// Hint: See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  auto iObj = cObj.getItem("newItemName");
Item& Category::getItem(const std::string identifier) const {
    auto result = itemMap.find(identifier);

    if (result == itemMap.cend()) {
        throw std::out_of_range("Could not find item with identifier \'" + identifier + "\'");
    } 

    auto pair = *result;
    return *pair.second; 
   
}

// TODO Write a function, getSum, that returns the sum of all Item amounts in
// the category. If no Item exists return 0.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0
double Category::getSum() const noexcept {
    double sum;
    for (const auto pair: itemMap) {
        Item* pItem = pair.second;
        sum += pItem->getAmount();
    }
    return sum; 
}

// TODO Write a function, deleteItem, that takes one parameter, an Item
// identifier (a string), deletes the item with that identifier from the
// container, and returns true if the Item was deleted. If no Item exists, throw
// an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  bool result = cObj.deleteItem("newItemName");
bool Category::deleteItem(const std::string &_identifier) {
    auto it = itemMap.find(_identifier);
    if (it == itemMap.end()) {
        throw std::out_of_range(_identifier + " does not exist in Category " + this->getIdent());
    }

    Item* pItem = it->second;
    delete pItem; 
    itemMap.erase(it);
    return true; 
}


// TODO Write an == operator overload for the Category class, such that two
// Category objects are equal only if they have the same identifier and same
// Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj.newItem("newItemName");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }

bool operator==(const Category &lhs, const Category &rhs) noexcept {
    if (lhs.ident != rhs.ident) return false;
    if (lhs.size() != rhs.size()) return false; 
    for (auto pair : lhs.itemMap) {
        Item lItem = *pair.second;
        
        auto result = rhs.itemMap.find(lItem.getIdent());
        if (result == rhs.itemMap.end()) return false;
        
        Item rItem = rhs.getItem(lItem.getIdent());
        if (rItem != lItem) return false; 

    }

    return true; 
}

// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
std::string Category::str() const noexcept {
    std::stringstream output;
    
    output << "{";


    for (auto it = itemMap.cbegin(); it != itemMap.cend(); it++) {
        std::string itemIdent = it->first;
        Item* pItem = it->second; 

        output << "\"" << itemIdent << "\":"
               << pItem->str();
        if (it != std::prev(itemMap.cend())) {
            output << ",";
        } 
    }

    output << "}";
    return output.str();
}
