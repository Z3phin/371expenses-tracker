// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "item.h"
#include "lib_json.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

// ------------------------------------------------
//                  Constructors
// ------------------------------------------------

/// @brief Constructs an Item with an identifier, description, amount and date. 
/// @param _identifier identifier of this item.
/// @param _description description of this item.
/// @param _amount amount belonging to this expense item (e.g £42.11)
/// @param _date date of this item. 
Item::Item(const std::string &_identifier, 
           const std::string &_description, 
           const double &_amount, 
           const Date &_date) noexcept
            : identifier(_identifier), 
            description(_description), 
            amount(_amount), 
            date(_date), 
            tags({}) {}


// ------------------------------------------------
//                      Getters
// ------------------------------------------------

/// @brief Returns the identifier for this Item.
/// @return identifier of this item.
std::string Item::getIdent() const noexcept {
    return this->identifier;
}

/// @brief Returns the description of this item.
/// @return the description of this item. 
std::string Item::getDescription() const noexcept {
    return this->description;
}

/// @brief Returns the amount for this Item.
/// @return the amount for this Item.
double Item::getAmount() const noexcept {
    return this->amount; 
}

/// @brief Gets the date belonging to this item.
/// @return Date object belonging to this item
Date Item::getDate() const noexcept {
    return this->date;
}

// ------------------------------------------------
//                     Setters
// ------------------------------------------------

/// @brief Sets the description of this Item.
/// @param _description new description.
void Item::setDescription(const std::string &_description) noexcept {
    this->description = _description; 
}

/// @brief Updates the amount for this item.
/// @param _amount new amount. 
void Item::setAmount(const double &_amount) noexcept {
    this->amount = _amount;  
}

/// @brief Updates the date belonging to this Item.
/// @param _date new date for this item. 
void Item::setDate(Date _date) noexcept {
    this->date = _date; 
}

// ------------------------------------------------
//                 Tag Functions
// ------------------------------------------------

/// @brief Adds the provided tag to the tags attached to this Item, only if it not already an existing tag.
/// @param tag tag to tbe added
/// @return True if the tag was added, otherwise false 
bool Item::addTag(const std::string &tag) noexcept {
    bool contains = containsTag(tag);
    if (!contains) {
        tags.push_back(tag);
    }
    return !contains;
}

/// @brief Deletes the provided tag from this Item's tags
/// @param tag tag to be deleted
/// @return True if this tag was deleted. 
/// @throw std::out_of_range - thrown when the given tag does not exist.
bool Item::deleteTag(const std::string &tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it == tags.end()) {
        throw std::out_of_range("ERROR: Cannot delete " + tag + " from item " + this->identifier);
    }
    
    tags.erase(it);
    return true; 
}

/// @brief Returns the number of tags belonging to this item
/// @return number of tags.
unsigned int Item::numTags() const noexcept {
    return this->tags.size();
}

/// @brief Checks whether the provided string is a tag attached to this object. 
/// @param tag string to be checked. 
/// @return True if the tag exists. Otherwise return false.
bool Item::containsTag(const std::string &tag) const noexcept {
    return std::find(tags.cbegin(), tags.cend(), tag) != tags.end(); 
}

/// @brief Merges the tags of another Item object with this object.
/// @param other Item with tags to be merged into this object.
void Item::mergeTags(const Item& other) noexcept {
    for (auto it = other.tags.cbegin(); 
              it != other.tags.cend();
              it ++ ) {
        this->addTag(*it);
    }    
}


// ------------------------------------------------
//               JSON Representation 
// ------------------------------------------------

/// @brief Returns a std::string of the JSON representation of the data in this Item in the format:
///
/// {"amount": xx.xx,"date":YYYY-MM-DD,"description":xxxxxxx,"tags":["tag","tag1",...,"tagN"]}
///
/// @return std::string of the JSON representation of the data in this Item.
std::string Item::str() const noexcept {
    return to_json().dump();
}

nlohmann::json Item::to_json() const noexcept {
    nlohmann::json json = nlohmann::json::object();
    json["amount"] = amount;
    json["date"] = date.str();
    json["description"] = description;
    nlohmann::json jsonTags = nlohmann::json::array();
    for (auto it = tags.cbegin(); it != tags.cend(); it++) {
        jsonTags.push_back(*it);
    }
    json["tags"] = jsonTags;
    return json; 
}


// ------------------------------------------------
//                    Operators
// ------------------------------------------------

/// @brief Compares two Item objects. 
///        Two Item objects are equal only if they have the same identifier, date, amount, description, and tags.
/// @param lhs left hand side item.
/// @param rhs right hand side item.
/// @return True if lhs identifier, date, amount and tags are the same as rhs. Otherwise false.
bool operator==(const Item& lhs, const Item& rhs) noexcept {
    return (lhs.identifier == rhs.identifier
            && lhs.date == rhs.date
            && lhs.amount == rhs.amount
            && lhs.tags == rhs.tags);
}

/// @brief Compares two Item objects. 
///        Two Item objects are equal only if they have the same identifier, date, amount, description, and tags.
/// @param lhs left hand side item.
/// @param rhs right hand side item.
/// @return True if lhs identifier, date, amount and tags are the same as rhs. Otherwise false.
bool operator!=(const Item& lhs, const Item& rhs) noexcept {
    return !(lhs == rhs);
}




