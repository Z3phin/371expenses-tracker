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


const char TAG_EXCEPTION[] = "tag";
const char DATE_JSON_ELEMENT[] = "date";
const char TAGS_JSON_ELEMENT[] = "tags";
const char AMOUNT_JSON_ELEMENT[] = "amount";
const char DESCRIPTION_JSON_ELEMENT[] = "description";

// ------------------------------------------------
//                  Constructors
// ------------------------------------------------

/// @brief Constructs an Item with an identifier, description, amount and date. 
/// @param _identifier identifier of this item.
/// @param _description description of this item.
/// @param _amount amount belonging to this expense item (e.g £42.11)
/// @param _date date of this item. 
Item::Item(const std::string& _identifier, 
           const std::string& _description, 
           const double& _amount, 
           const Date& _date) noexcept

            : identifier(_identifier), 
            description(_description), 
            amount(_amount), 
            date(_date), 
            tags({}) {}


// ------------------------------------------------
//                      Ident
// ------------------------------------------------

/// @brief Returns the identifier for this Item.
/// @return identifier of this item.
std::string Item::getIdent() const noexcept {
    return this->identifier;
}

// ------------------------------------------------
//                    Description
// ------------------------------------------------

/// @brief Returns the description of this item.
/// @return the description of this item. 
std::string Item::getDescription() const noexcept {
    return this->description;
}

/// @brief Sets the description of this Item.
/// @param _description new description.
void Item::setDescription(const std::string& _description) noexcept {
    this->description = _description; 
}

// ------------------------------------------------
//                       Tags
// ------------------------------------------------

/// @brief Adds the provided tag to the tags attached to this Item, only if it not already an existing tag.
/// @param tag tag to tbe added
/// @return True if the tag was added, otherwise false 
bool Item::addTag(const std::string& tag) noexcept {
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
bool Item::deleteTag(const std::string& tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it == tags.end()) {
        throw std::out_of_range(TAG_EXCEPTION);
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
bool Item::containsTag(const std::string& tag) const noexcept {
    return std::find(tags.cbegin(), tags.cend(), tag) != tags.end(); 
}

/// @brief Merges the tags of another Item object with this object.
/// @param other Item with tags to be merged into this object.
void Item::mergeTags(const Item& other) noexcept {
    for (auto it = other.tags.cbegin(); it != other.tags.cend(); it ++ ) {
        this->addTag(*it);
    }    
}

// ------------------------------------------------
//                      Amount
// ------------------------------------------------

/// @brief Returns the amount for this Item.
/// @return the amount for this Item.
double Item::getAmount() const noexcept {
    return this->amount; 
}

/// @brief Updates the amount for this item.
/// @param _amount new amount. 
void Item::setAmount(const double& _amount) noexcept {
    this->amount = _amount;  
}

// ------------------------------------------------
//                       Date
// ------------------------------------------------

/// @brief Gets the date belonging to this item.
/// @return Date object belonging to this item
Date Item::getDate() const noexcept {
    return this->date;
}

/// @brief Updates the date belonging to this Item.
/// @param _date new date for this item. 
void Item::setDate(const Date& _date) noexcept {
    this->date = _date; 
}

// ------------------------------------------------
//            String and JSON Representation 
// ------------------------------------------------

/// @brief Returns a std::string of the JSON representation of the data in this Item in the format:
///
/// {"amount": xx.xx,"date":YYYY-MM-DD,"description":xxxxxxx,"tags":["tag","tag1",...,"tagN"]}
///
/// @return std::string of the JSON representation of the data in this Item.
std::string Item::str() const noexcept {
    nlohmann::json json; 
    to_json(json, *this);
    return json.dump();
}

/// @brief Converts the given item into a JSON representation using the given JSON object.
/// @param json json object to load item data into. 
/// @param item item to be converted to JSON.
void to_json(nlohmann::json& json, const Item& item) noexcept {
    json = nlohmann::json{{AMOUNT_JSON_ELEMENT, item.amount},
                          {DATE_JSON_ELEMENT, item.date},
                          {DESCRIPTION_JSON_ELEMENT, item.description},
                          {TAGS_JSON_ELEMENT, item.tags}};
}

/// @brief Sets the given item to contain the data in the given JSON object
/// @param json JSON object representing an Item.
/// @param item Item to be set with the JSON data.
/// @throws exception if JSON is invalid for an Item. 
void from_json(const nlohmann::json& json, Item& item) {
    json.at(AMOUNT_JSON_ELEMENT).get_to(item.amount);
    json.at(DATE_JSON_ELEMENT).get_to(item.date);
    json.at(DESCRIPTION_JSON_ELEMENT).get_to(item.description);

    // Get the tags and add them to the item.
    std::vector<std::string> jsonTags;
    json.at(TAGS_JSON_ELEMENT).get_to(jsonTags);

    for (auto it = jsonTags.cbegin(); it != jsonTags.cend(); it++) {
        item.addTag(*it);
    }
    
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




