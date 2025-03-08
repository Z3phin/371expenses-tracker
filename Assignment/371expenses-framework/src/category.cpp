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
#include <set>
#include <sstream>

// -----------------------------------------------------
//                  Category Class Functions
// -----------------------------------------------------

// ------------------------------------------------
//                  Constructors
// ------------------------------------------------

// A constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};

/// @brief Constructor for category. 
/// @param _ident Category identifier.
Category::Category(const std::string &_ident) noexcept : ident(_ident), itemMap({}) {}

// ------------------------------------------------
//                  Deconstructor
// ------------------------------------------------

/// @brief Deconstructor for category object. 
Category::~Category() {
    // Delete all the pointers to items contained in the map.
    for (auto it = itemMap.begin(); it != itemMap.end(); it++) {
        delete it->second;
        it->second = nullptr;
    }
}

// ------------------------------------------------
//          Category Properties Functions
// ------------------------------------------------

// A function, size, that takes no parameters and returns an unsigned
// int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();

/// @brief Returns number of Items in the category. 
/// @return Numer of Items in the Category. 
unsigned int Category::size() const noexcept {
    return itemMap.size();
}


// A function, getIdent, that returns the identifier for the Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();

/// @brief Returns the identifier for the category.
/// @return Category identifier. 
std::string Category::getIdent() const noexcept {
    return this->ident;
}

// ------------------------------------------------
//                     Setters
// ------------------------------------------------

// A function, setIdent, that takes one parameter, a string for a new
// Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

/// @brief Updates the category identifier to a new identifier. 
/// @param _ident New identifier for category.  
void Category::setIdent(const std::string &_ident) noexcept {
    this->ident = _ident;
}

// ------------------------------------------------
//                  Item Operations
// ------------------------------------------------

// A function, newItem, that takes four parameters, an Item
// identifier (string), description (string), amount (double), and date (Date)
// and returns the Item object as a reference.  If an object with the same
// identifier already exists, then the existing object should be overwritten by
// the new Item. Throw a std::runtime_error if the Item object cannot be
// inserted into the container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");

/// @brief Creates a new Item object with the given properties and adds it to the category.
/// If an item with the given identifier already exists, it will will be overwritten by the new object. 
/// @param _identifier identifier of the new Item object. 
/// @param _description description of the new Item object. 
/// @param _amount amount of the new Item object. 
/// @param _date date of the new Item object. 
/// @return Reference to the new Item object. 
Item& Category::newItem(const std::string &_identifier, 
                        const std::string &_description, 
                        const double &_amount,
                        const Date &_date) {
    

        Item* pNewItem = new Item(_identifier, _description, _amount, _date);
        
        try {
            
            auto result = itemMap.emplace(std::make_pair(_identifier, pNewItem));

            auto it = itemMap.find(_identifier);
            if (result.second == false) {
                delete it->second; 
                it->second = pNewItem;
            }
            return *(it->second);

        } catch (...) { // What would go wrong? 
            delete pNewItem;
            throw std::runtime_error("Something went wrong");
        }

}

// A function, addItem, that takes one parameter, an Item object, and
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

/// @brief Adds the given Item object to the Category or merges with an existing
/// Item in the Category if it shares the same identifier.  
///
/// If a merge occurs, the tags of the objects will be merged, and the description,  
/// amount and date of the new Item will be overwrite the exising item. 
/// @param item item to be added
/// @return True if the item was added, false if it was merged with an existing object. 
bool Category::addItem(const Item &item) noexcept {

    auto it = itemMap.find(item.getIdent());
    bool contains = (it != itemMap.end());
    
    if (contains) {
        auto pItem = it->second; 

        pItem->mergeTags(item);
        pItem->setDescription(item.getDescription());
        pItem->setAmount(item.getAmount());
        pItem->setDate(item.getDate());
    } else {
        Item* pNewItem = new Item(item.getIdent(), 
                                  item.getDescription(),
                                  item.getAmount(),
                                  item.getDate());
        pNewItem->mergeTags(item);
        itemMap.insert(std::make_pair(item.getIdent(), pNewItem));
    }

    return !contains;
}

// A function, getItem, that takes one parameter, an Item identifier
// (a string) and returns the Item as a reference. If no Item exists, throw an
// appropriate exception.
//
// Hint: See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  auto iObj = cObj.getItem("newItemName");

/// @brief Attempts to find an Item in the Category with the given identifier 
/// @param identifier identifier of Item to be retrieved
/// @return Reference to the Item only if it is in this Category. 
/// @throws std::out_of_range exception if an Item with a matching identifier
/// could not be found.
Item& Category::getItem(const std::string identifier) const {
    auto result = itemMap.find(identifier);

    if (result == itemMap.cend()) {
        throw std::out_of_range("Could not find item with identifier \'" + identifier + "\'");
    } 

    auto pair = *result;
    return *pair.second; 
   
}

// A function, getSum, that returns the sum of all Item amounts in
// the category. If no Item exists return 0.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0

/// @brief Returns the sum of all Item amounts in the Category
/// @return sum of all amounts. If no items are in this category, returns 0.
double Category::getSum() const noexcept {
    double sum = 0;
    for (const auto pair: itemMap) {
        Item* pItem = pair.second;
        sum += pItem->getAmount();
    }
    return sum; 
}

// A function, deleteItem, that takes one parameter, an Item
// identifier (a string), deletes the item with that identifier from the
// container, and returns true if the Item was deleted. If no Item exists, throw
// an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  bool result = cObj.deleteItem("newItemName");

/// @brief Deletes the Item with the matching identifier from the Category. 
/// @param _identifier Identifier of item to be deleted. 
/// @return True only if the item was deleted.
/// @throws std::out_of_range exception if the Item with the given identifier
/// could not be found in the category.
bool Category::deleteItem(const std::string &_identifier) {
    auto it = itemMap.find(_identifier);
    if (it == itemMap.end()) {
        throw std::out_of_range(_identifier + " does not exist in Category " + this->getIdent());
    }

    delete it->second; // Delete item pointer
    it->second = nullptr; 
    itemMap.erase(it);
    return true; 
}

void Category::mergeItems(const Category &other) {
    for (auto it = other.itemMap.cbegin(); 
              it != other.itemMap.cend();
              it ++ ) {
        this->addItem(*(it->second));
    }
}


// ------------------------------------------------
//              Operator Functions
// ------------------------------------------------

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

/// @brief Compares two Category objects based on their identifier and Item objects 
/// they contain and returns if they are equal or not. 
/// @param lhs left hand side Category object. 
/// @param rhs right hand side Category object. 
/// @return True if the two categories have the same identifier and equal Items, otherwise false.
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

/// @brief Compares two Category objects based on their identifier and Item objects 
/// they contain returns if they are not equal. 
/// @param lhs left hand side Category object. 
/// @param rhs right hand side Category object. 
/// @return True if the two categories do not have the same identifier and equal Items, otherwise false.
bool operator!=(const Category &lhs, const Category &rhs) noexcept {
    return !(lhs == rhs);
}


// ------------------------------------------------
//              JSON Representation
// ------------------------------------------------

// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();

/// @brief Returns a JSON representation string of this Category.
///
/// {"item1Identifer":--ITEM JSON --,"item1Identifer":--ITEM JSON --, ... , "itemNIdentifer":--ITEM JSON --}
///
/// @return JSON representation of this Category
std::string Category::str() const noexcept {
    return to_json().dump();
}

nlohmann::json Category::to_json() const noexcept {
    nlohmann::json json = nlohmann::json::object();
    for (auto it = itemMap.cbegin(); it != itemMap.cend(); it++) {
        json[it->first] = it->second->to_json();   
    }
    return json; 
}

/// @brief Attempts to load a json object of Items into this category. 
/// Any item objects that are not of the expected format and types are ignored.
/// @param json json object to load items from.
void Category::from_json(const nlohmann::json &json) {
    if (!json.is_object()) {
        return;
    }

    for (auto it = json.cbegin(); it != json.cend(); it++) {
        loadJsonItem(it.key(), it.value());
    }
}

/// @brief Loads an Item into the Category based on the json object given with the given
/// identifier, only if the json object is of expected format with valid types, otherwise 
/// it is not added
/// @param itemIdent 
/// @param json 
void Category::loadJsonItem(const std::string &itemIdent, const nlohmann::json &json) {
    if (!json.is_object()) {
        return; // Possibly throw error (or this could return a bool)
    }

    if (json.size() != 4 
    || !json.contains("amount") 
        || !json.contains("date") 
        || !json.contains("description")
        || !json.contains("tags")) {
            return; // Possibly throw error or return false
    }

    auto amountJson = json.at("amount");
    auto dateStrJson = json.at("date");
    auto descriptionJson = json.at("description");
    auto tagsJson = json.at("tags");

    if (!amountJson.is_number() 
        || !dateStrJson.is_string() 
        || !descriptionJson.is_string()
        || !tagsJson.is_array()) {
            return; // possibly throw error or return false
    }

    for (auto tagsJsonIt = tagsJson.cbegin();
         tagsJsonIt != tagsJson.cend();
         tagsJsonIt++) {

        if (!tagsJsonIt->is_string()) {
            return; // Ignore invalid data
        }
    }

    auto amount = amountJson.get<double>();
    auto dateStr = dateStrJson.get<std::string>();
    auto description = descriptionJson.get<std::string>();
    auto tags = tagsJson.get<std::set<std::string>>();

    Date date;
    try {
        date = Date(dateStr);
    } catch (std::invalid_argument &ex) {
        return; // Ignore object
    }
    Item& i = this->newItem(itemIdent, description, amount, date);

    // Add each tag to the item.
    for (auto tagIt = tags.cbegin(); tagIt != tags.cend(); tagIt++) {
        i.addTag(*tagIt);
    }
}