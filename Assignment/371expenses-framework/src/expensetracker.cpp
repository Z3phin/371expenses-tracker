// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
#include "expensetracker.h"
#include "lib_json.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <utility>

// ------------------------------------------------
//                  Constants
// ------------------------------------------------

const char NEW_CATEGORY_ERROR_MSG[] = "Could not add new category.";
const char ADD_CATEGORY_ERROR_MSG[] = "Could not add category.";
const char FILE_OPEN_ERROR_MSG[] = "File did not open successfully.";
const char CATEGORY_OUT_OF_RANGE[] = "category";


// ------------------------------------------------
//                  Constructor
// ------------------------------------------------

// Example:
//  ExpenseTracker etObj{};

/// @brief Constructs an ExpenseTracker object
ExpenseTracker::ExpenseTracker() : categoryMap({}) {}


// ------------------------------------------------
//                  Property Functions
// ------------------------------------------------ 


// Example:
//  ExpenseTracker etObj{};
//  auto size = etObj.size();

/// @brief Returns the size (number of categories) of the ExpenseTracker object. 
/// @return number of categories.
unsigned int ExpenseTracker::size() const noexcept {
    return this->categoryMap.size();
}


// ------------------------------------------------
//               Category Operations
// ------------------------------------------------ 


// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");

/// @brief Creates a new Category and adds it to the ExpenseTracker and returns it
/// as a reference, or returns a reference to an existing category if it has the 
/// same identifier. 
/// @param categoryIdent identifier of new category.
/// @return reference to new or already existing category. 
/// @throws std::runtime_error if adding the new Category was unsuccessful.
Category& ExpenseTracker::newCategory(const std::string &categoryIdent) {
    const auto it = categoryMap.find(categoryIdent);
    if (it != categoryMap.cend()) {
        return *(it->second);
    }

    try {
        const std::shared_ptr<Category> pNewCategory(new Category(categoryIdent));
        categoryMap.insert(std::make_pair(categoryIdent, pNewCategory));
        return *pNewCategory; 
    } catch (...) {
        throw std::runtime_error(NEW_CATEGORY_ERROR_MSG);
    }

}

// Example:
//  ExpenseTracker etObj{};
//  Category cObj{"categoryIdent"};
//  etObj.addCategory(cObj);

/// @brief Adds the given Category object to the ExpenseTracker. If the ExpenseTracker 
/// already contains a category with the same identifier, the contents of the given category
/// are merged with the existing one. 
/// @param category category object to be added. 
/// @return True if added successfully, otherwise false if merged. 
/// @throws std::runtime_error exception if the operation was unsuccessful for some reason.
bool ExpenseTracker::addCategory(const Category &category) {
    auto it = categoryMap.find(category.getIdent());
    if (it != categoryMap.end()) {
        it->second->mergeItems(category);
        return false;
    }

    try {
        const std::shared_ptr<Category> pNewItem(new Category(category));
        categoryMap.insert(std::make_pair(category.getIdent(), pNewItem));
        return true;
    } catch (...) {
        throw std::runtime_error(ADD_CATEGORY_ERROR_MSG);
    }

     
}      

// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  auto cObj = etObj.getCategory("categoryIdent");

/// @brief Returns the category with the given identifier only if it is in the 
/// ExpenseTracker object. 
/// @param categoryIdentifier category to be found  
/// @return Reference to category object with matching identifier
/// @throws std::out_of_range exception if the category is not in the ExpenseTracker
Category& ExpenseTracker::getCategory(const std::string &categoryIdentifier) const {
    const auto it = categoryMap.find(categoryIdentifier);
    if (it == categoryMap.cend()) {
        throw std::out_of_range(CATEGORY_OUT_OF_RANGE);
    }   

    return *(it->second);
}

// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  etObj.deleteCategory("categoryIdent");

/// @brief Deletes the Category with the given identifier from the ExpenseTracker object if it exists,
/// otherwise an exception is thrown if the identifier could not be found. 
/// @param categoryIdentifier identifier of category to be deleted. 
/// @return True only if the Category was deleted. 
/// @throws std::out_of_range exception if the given category identifier could not be found. 
bool ExpenseTracker::deleteCategory(const std::string &categoryIdentifier) {
    const auto it = categoryMap.find(categoryIdentifier);
    if (it == categoryMap.cend()) {
        throw std::out_of_range(CATEGORY_OUT_OF_RANGE);
    }   
    
    categoryMap.erase(it);
    return true; 
}


// TODO Write a function, getSum, that returns the sum of all Category expense
// sums. This consists of the sum of all individual item amounts across all categories.
// If no categories or no items exists return 0.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj = etObj.newCategory("categoryIdent");
//  Category cObj2 = etObj.newCategory("categoryIdent2");
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  cObj2.newItem("newItemName3", "Description", "3.0", Date(2024,12,25));
//  cObj2.newItem("newItemName4", "Description", "4.0", Date(2024,12,25));
//  auto sum = ejObj.getSum() // 10.0

/// @brief Returns the sum of all category expense sums, consisting of all individual 
/// item amounts across all categories
/// @return sum of all items across all categories. Returns 0 if there are no items. 
double ExpenseTracker::getSum() const noexcept {
    double sum = 0; 
    for (auto it = categoryMap.cbegin(); it != categoryMap.cend(); it++) {
        sum += it->second->getSum();
    }
    return sum; 
}

// ------------------------------------------------
//               JSON File Operations
// ------------------------------------------------ 

// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");

/// @brief Opens a JSON file with the given file name and populates the ExpenseTracker 
/// with its categories and items.
/// @param database JSON datbase filename.
/// @throws exceptions may be thrown when parsing the JSON file (e.g. improper formatting)
void ExpenseTracker::load(const std::string &database) {
    std::ifstream inputFileStream;
    inputFileStream.open(database, std::ifstream::in);

    if (!inputFileStream.good()) {
        inputFileStream.close();
        throw std::runtime_error(FILE_OPEN_ERROR_MSG);
    }

    const nlohmann::json j = nlohmann::json::parse(inputFileStream);
    from_json(j, *this);
    inputFileStream.close();
}

// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");
//  ...
//  etObj.save("database.json");

/// @brief Saves the ExpenseTracker object to the given file as JSON.
/// @param filepath file for date to be saved to. 
void ExpenseTracker::save(const std::string &filepath) const {
    std::ofstream output;
    output.open(filepath);
    if (!output.is_open()) {
        throw std::runtime_error(FILE_OPEN_ERROR_MSG);
    }

    output << this->str();
    output.close();
}


// ------------------------------------------------
//               Operator Functions
// ------------------------------------------------ 

// Example:
//  ExpenseTracker etObj1{};
//  ExpenseTracker etObj2{};
//  if(etObj1 == etObj2) {
//    ...
//  }

/// @brief Compares two ExpenseTracker objects. The two objects are equal if they have
/// the same data, i.e. equivalent categories and items. 
/// @param lhs left hand side object.
/// @param rhs right hand side object.
/// @return True if the objects are equal, otherwise false. 
bool operator==(const ExpenseTracker &lhs, const ExpenseTracker &rhs) noexcept {
    if (lhs.size() != rhs.size()) return false;

    // Check if each category in lhs is in rhs
    for (auto it = lhs.categoryMap.cbegin(); it != lhs.categoryMap.cend(); it++) {
        
        const Category &lCategory = *(it->second);
        const auto result = rhs.categoryMap.find(lCategory.getIdent());

        if (result == rhs.categoryMap.end()) return false; 

        const Category &rCategory = *(result->second);        
        if (lCategory != rCategory) return false;
    }
    return true; 
}

/// @brief Compares two ExpenseTracker objects. The two objects are not equal if they have
/// differing data, i.e. different items or categories. 
/// @param lhs left hand side object.
/// @param rhs right hand side object.
/// @return True if the objects are not equal, otherwise false.
bool operator!=(const ExpenseTracker &lhs, const ExpenseTracker &rhs) noexcept {
    return !(lhs == rhs);
}

// ------------------------------------------------
//               JSON Representation
// ------------------------------------------------ 


// Example:
//  ExpenseTracker etObj{};
//  std::string s = etObj.str();

/// @brief Returns a JSON formatted string representation of the ExpenseTracker object.
/// @return JSON formatted string representation of the object. 
std::string ExpenseTracker::str() const noexcept {
    nlohmann::json json = nlohmann::json::object();;

    to_json(json, *this);
    return json.dump();
}

/// @brief Converts the given ExpenseTracker object to JSON representation in the given JSON object.
/// @param json json object to hold ExpenseTracker JSON data.
/// @param et ExpenseTracker to be converted to JSON.
void to_json(nlohmann::json& json, const ExpenseTracker& et) noexcept {

    for (auto it = et.categoryMap.cbegin(); it != et.categoryMap.cend(); it++) {
        nlohmann::json categoryJson = nlohmann::json::object();

        to_json(categoryJson, *(it->second));
        json[it->second->getIdent()] = categoryJson; 
    }
}

/// @brief Takes the given JSON represented ExpenseTracker and populates the given 
/// ExpenseTracker object with the data. 
/// @param json ExpenseTracker JSON representation.
/// @param et ExpenseTracker to populate. 
void from_json(const nlohmann::json& json, ExpenseTracker& et) {
    for (auto it = json.cbegin(); it != json.cend(); it++) {

        const nlohmann::json& categoryJson = it.value();
        Category c = Category(it.key());

        from_json(categoryJson, c);
        et.addCategory(c);
    }
}


