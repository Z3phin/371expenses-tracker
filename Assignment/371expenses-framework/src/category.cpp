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

// ------------------------------------------------
//                  Constants
// ------------------------------------------------

const char NEW_ITEM_RUNTIME_ERROR[] = "Could not create new item.";
const char ITEM_OUT_OF_RANGE[] = "item";

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
Category::Category(const std::string &identifier) noexcept : ident(identifier), itemMap({}) {}

// ------------------------------------------------
//          Category Properties Functions
// ------------------------------------------------

// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();

/// @brief Returns number of Items in the category. 
/// @return Numer of Items in the Category. 
unsigned int Category::size() const noexcept {
    return itemMap.size();
}

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

// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

/// @brief Updates the category identifier to a new identifier. 
/// @param _ident New identifier for category.  
void Category::setIdent(const std::string &identifier) noexcept {
    this->ident = identifier;
}

// ------------------------------------------------
//                  Item Operations
// ------------------------------------------------

// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");

/// @brief Creates a new Item object with the given identifier, description, 
/// amount and date and adds it to the category.
/// If an item with the given identifier already exists, it will will be
/// overwritten by the new object. 
/// @param identifier identifier of the new Item object. 
/// @param description description of the new Item object. 
/// @param amount amount of the new Item object. 
/// @param date date of the new Item object. 
/// @return Reference to the new Item object. 
/// @throws std::runtime_error if the item could not be added for whatever reason.
Item& Category::newItem(const std::string &identifier, 
                        const std::string &description, 
                        const double &amount,
                        const Date &date) {
    
        try {
            std::shared_ptr<Item> pNewItem(new Item(identifier, description, amount, date));
            const auto result = itemMap.emplace(std::make_pair(identifier, pNewItem));

            auto it = itemMap.find(identifier);
            if (result.second == false) {
                it->second = pNewItem;
            }
            return *(it->second);

        } catch (...) {
            throw std::runtime_error(NEW_ITEM_RUNTIME_ERROR);
        }

}

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
    const bool contains = (it != itemMap.end());
    
    if (contains) { // Merge with existing
        auto pItem = it->second; 

        pItem->mergeTags(item);
        pItem->setDescription(item.getDescription());
        pItem->setAmount(item.getAmount());
        pItem->setDate(item.getDate());
    } else { // Create a new map entry
        std::shared_ptr<Item> pNewItem(new Item(item));
        itemMap.insert(std::make_pair(item.getIdent(), pNewItem));
    }

    return !contains;
}

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
    const auto result = itemMap.find(identifier);

    if (result == itemMap.cend()) {
        throw std::out_of_range(ITEM_OUT_OF_RANGE);
    } 

    // extract the item from the map
    const auto pair = *result;
    return *pair.second; 
   
}

// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0

/// @brief Returns the sum of all Item amounts in the Category
/// @return Sum of all amounts. If no items are in this category, returns 0.
double Category::getSum() const noexcept {
    double sum = 0;
    for (const auto pair: itemMap) {
        sum += pair.second->getAmount();
    }
    return sum; 
}


// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  bool result = cObj.deleteItem("newItemName");

/// @brief Deletes the Item with the matching identifier from the Category. 
/// @param _identifier Identifier of item to be deleted. 
/// @return True only if the item was deleted.
/// @throws std::out_of_range exception if the Item with the given identifier
/// could not be found in the category.
bool Category::deleteItem(const std::string &identifier) {
    auto it = itemMap.find(identifier);
    if (it == itemMap.end()) {
        throw std::out_of_range(ITEM_OUT_OF_RANGE);
    }

    itemMap.erase(it);
    return true; 
}

/// @brief Adds all the items in the given Category object to this Category. 
/// If this category already contains an item, it is merged/overwritten by the
/// item. (see addItem)
/// @param other Category with items to be added to this Category. 
void Category::mergeItems(const Category &other) noexcept {
    for (auto it = other.itemMap.cbegin(); 
              it != other.itemMap.cend();
              it ++ ) {
        this->addItem(*(it->second));
    }
}

/// @brief Returns whether or not the given Item identifier is in the Category. 
/// @param itemIdent item to find. 
/// @return True if in the Category, otherwise false.
bool Category::containsItem(const std::string& itemIdent) const noexcept {    
    return itemMap.find(itemIdent) != itemMap.cend();
}


// ------------------------------------------------
//              Operator Functions
 // ------------------------------------------------


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

    // Check if each item in lhs has an equal in rhs. 
    for (auto pair : lhs.itemMap) {
        Item& lItem = *pair.second;
        
        const auto result = rhs.itemMap.find(lItem.getIdent());
        if (result == rhs.itemMap.cend()) return false;
        
        Item& rItem = *result->second;
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

// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();

/// @brief Returns a JSON representation string of this Category.
///
/// {"item1Identifer":--ITEM JSON --,"item1Identifer":--ITEM JSON --, ... , "itemNIdentifer":--ITEM JSON --}
///
/// @return JSON representation of this Category
std::string Category::str() const noexcept {
    nlohmann::json categoryJson = nlohmann::json::object();;

    to_json(categoryJson, *this);
    return categoryJson.dump();
}

/// @brief Converts the given Category to a JSON object using the json object to store the data.
/// @param json json object to hold Category data.
/// @param category Category object to be coverted to JSON.
void to_json(nlohmann::json& json, const Category& category) noexcept {

    // Add each item, as its JSON representation, to the object 
    for (auto it = category.itemMap.cbegin(); it != category.itemMap.cend(); it++) {
        nlohmann::json itemJson = nlohmann::json::object();

        to_json(itemJson, *(it->second));
        json[it->second->getIdent()] = itemJson; 
    }
 }

/// @brief Takes a JSON represented Category and populates the given category with its items.
/// @param json JSON represented Categeory.
/// @param category Category to populate with JSON data. 
void from_json(const nlohmann::json &json, Category& category) {
    for (auto it = json.cbegin(); it != json.cend(); it++) {

        const nlohmann::json& jsonItem = it.value();

        Item item = Item(it.key(), "", 0, Date()); // Some "default" item whose data will be overwritten 
        from_json(jsonItem, item);

        category.addItem(item);
    }    
}