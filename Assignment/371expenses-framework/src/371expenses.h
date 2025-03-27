// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// This file contains declarations for the helper functions used for
// initialising and running 371expenses.
// -----------------------------------------------------

#ifndef _371EXPENSES_H
#define _371EXPENSES_H

#include <string>

#include "lib_cxxopts.hpp"
#include "expensetracker.h"

namespace App {

const std::string STUDENT_NUMBER = "2212805";

// This enum specifies the five different values we support in the action
// program argument.
enum Action { CREATE, SUM, JSON, DELETE, UPDATE };

/// @brief Runs the 371Expenses program program. This program allows users to 
/// create a tracker of various categories that each contain various items.
/// Using various arguments, json, create, sum, delete, update, users are 
/// able to manipulate and inspect their expense trackers. 
/// 
/// The user's expenses can be read from and saved to a json file. 
///
/// @param argc arguments for program i.e. json, create, sum, delete, update, item, 
/// category, date, tags and description. 
/// @param argv number of arguements.
/// @return status code.
int run(int argc, char *argv[]);

/// @brief Create a cxxopts instance with the appropriate 
/// arguments for this app.
/// @return cxxopts instance.
cxxopts::Options cxxoptsSetup();

/// @brief Case-insensitively checks the action argument retrieved from cxxopts
/// and converts this to a value from the Action enum.
/// @param args arguments from cxxopts.
/// @return Action value based on action argument. 
/// @throws std::invalid_argument exception if an invalid value is given. 
App::Action parseActionArgument(const cxxopts::ParseResult& args);

// ------------------------------------------------
//                      JSON 
// ------------------------------------------------


/// @brief Returns a std::string containing the JSON representation of a
/// ExpenseTracker object. 
/// @param etObj 
/// @return JSON representation of ExpenseTracker as a string. 
std::string getJSON(const ExpenseTracker& et);

/// @brief Returns a std::string containing the JSON representation of a 
/// specific Category in an ExpenseTracker object. 
/// @param etObj ExpenseTracker object.
/// @param c Category identifier
/// @return JSON represenation of Category in ExpenseTracker as a string. 
/// @throws std::out_of_range if Category is not in ExpenseTracker object.
std::string getJSON(const ExpenseTracker& et, const std::string& c);

/// @brief Returns a std::string containing the JSON representation of a 
/// specific Item in a ExpenseTracker object.
/// @param etObj ExpenseTracker object.
/// @param c Category identifier
/// @param id Item identifier.
/// @return JSON representation of Item as a string.
/// @throws std::out_of_range if Category or Item is not in ExpenseTracker.
std::string getJSON(const ExpenseTracker& et, const std::string& c, const std::string& id);

/// @brief Performs the JSON action. According to the arguments:
///
/// If both category and item arguments are present, then the Item
/// JSON is printed. 
///
/// If only category is given, then the Category JSON is printed.
///
/// If neither category or item is given, the entire ExpenseTracker
/// JSON is given 
///
/// @param et ExpenseTracker 
/// @param args Command line arguments that may include "category" or "item"
/// @throws std::invalid_argument if an invalid category, item or combination
/// of the two is given (i.e. item without a category).
/// std::out_of_range if the category or item are not in the ExpenseTracker
/// or Category respectively.
void performJsonAction(const ExpenseTracker& et, const cxxopts::ParseResult& args);

// ------------------------------------------------
//                      SUM
// ------------------------------------------------

/// @brief Returns the sum of all the Items in the ExpenseTracker object.
/// @param et ExpenseTracker object.
/// @return Sum of all items. 
double getSum(const ExpenseTracker& et) noexcept;

/// @brief Returns the sum of all the Items in the Category contained
/// in the ExpenseTracker object. 
/// @param et ExpenseTracker object.
/// @param c Category identifier. 
/// @return Sum of all Items in the Category
/// @throws std::out_of_range if Category is not in ExpenseTracker object.
double getSum(const ExpenseTracker& et, const std::string& c);

/// @brief Performs the Sum action. Accordingly to the arguments,
/// either the sum of all items in the whole ExpenseTracker is printed,
/// or if a category is given, the sum of the items only in that
/// category.  
/// @param et ExpenseTracker object.
/// @param args Command line arguments that may include "category"
/// @throws std::out_of_range if the Category is not in the ExpenseTracker.
void performSumAction(const ExpenseTracker& et, const cxxopts::ParseResult& args);

// ------------------------------------------------
//                     CREATE
// ------------------------------------------------

/// @brief Creates a new Category with the given identifier in the 
/// ExpenseTracker object.
/// @param et ExpenseTracker object.
/// @param c Identifier of Category to create
/// @return Reference to Category created.  
Category& create(ExpenseTracker& et, const std::string& c);      

/// @brief Creates a new Item in the given Category only if it does not exist
/// already.
/// @param et ExpenseTracker object. 
/// @param c Identifier of Category to add Item into.
/// @param id Identifier of Item to create.
/// @param desc Description of Item.
/// @param amount Amount (£) of Item.
/// @return Reference to the created or already existing Item.
Item& create(ExpenseTracker& et, 
                const std::string& c,
                const std::string& id,
                const std::string& desc,
                const double& amount);

/// @brief Adds a list of comma separated tags to the item.
/// @param item Item to add tags to.
/// @param tagList List of tags to add.
void addTags(Item& item, const std::string& tagList);

/// @brief Performs corresponding actions for "create" according to the arguments, i.e. 
/// either creating a category or an item, using the given ExpenseTracker. If 
/// required properties are missing, for example --description for item, an error occurs. 
/// @param et ExpenseTracker object
/// @param args arguments including --category, --item and item's properties
void performCreateAction(ExpenseTracker& et, const cxxopts::ParseResult& args);

/// @brief Performs the actions for creating an item specifically. An item requires
/// an identifier, a description, an amount (£), and the category it belongs to 
/// minimally. Optionally, a date and tags can be specified. If date is not 
/// specified, today's date is attached to the created item.
/// @param et ExpenseTracker to add the item to.
/// @param args arguments including category, item, description, amount, date and tags.
void performCreateItem(ExpenseTracker& et, const cxxopts::ParseResult& args);

// ------------------------------------------------
//                     DELETE
// ------------------------------------------------

/// @brief Attempts to delete the given category from the ExpenseTracker
/// If the category is not in the ExpenseTracker, outputs an error.
/// @param et ExpenseTracker object
/// @param category Identifier of Category to be deleted
/// @return True only if category was deleted.
bool remove(ExpenseTracker& et, const std::string& category);

/// @brief Attempts to delete the given item from the given category.
/// If the item does not exist in the category, outputs an error. 
/// @param et ExpenseTracker object.
/// @param catIdent Identifier of Category possibly containing item. 
/// @param item Identifier of Item to delete. 
/// @return True only if the Item was deleted. 
bool remove(ExpenseTracker& et, const std::string& category, const std::string& item);

/// @brief Attempts to delete the given tag from an Item in a Category.
/// If the tag does not exist on the Item, outputs an error message. 
/// @param et ExpenseTracker object
/// @param category Identifier of Category.
/// @param id Identifier of Item.
/// @param tag Tag to be deleted
/// @return True only if Tag was deleted.
bool remove(ExpenseTracker& et, const std::string& category, const std::string& item, const std::string &tag);

/// @brief Performs the action for deleting either a category, an item or a tag. 
/// If an invalid combination of arguments, e.g. no arguments, tag without an item,
/// or an item without a category, an error is output.
/// @param et ExpenseTracker objects
/// @param args arguments that may include category, item and tag.
void performDeleteAction(ExpenseTracker& et, const cxxopts::ParseResult& args);

// ------------------------------------------------
//                     UPDATE
// ------------------------------------------------

/// @brief Updates the given Category with the new identifier.
/// If the given Category does not exist in the ExpenseTracker,
/// an error is output.
/// @param et ExpenseTracker object.
/// @param oldCategoryIdent Old Category identifier to be updated.
/// @param newCategoryIdent New Category identifier to update to. 
void update(ExpenseTracker& et, const std::string& oldCategoryIdent, const std::string& newCategoryIdent);

/// @brief Updates the given Item according to the given arguments, 
/// either date, amount, and description. These can be updated 
/// simulataneously 
/// @param item Item whose properties may be updated.
/// @param args arguments that may include description, amount or date.
void update(Item& item, const cxxopts::ParseResult& args);

/// @brief Performs the action for updating either the identifier of category,
/// or the properties, data, description or amount, of a specified item. 
/// If an item is specified without a category, an error is output. 
/// Similarly, if a category, item or erroneous data is given, an 
/// an appropriate error is output. 
/// @param et ExpenseTracker object
/// @param args Arguments that may include category, item, description, 
/// amount or date. 
void performUpdateAction(ExpenseTracker& et, const cxxopts::ParseResult& args);

/// @brief Perform the action of updating a category identifier. 
/// A category identifier can be updated with the argument 
/// --category oldIdentifier:newIdentifier.
/// If this pattern is malformed or oldIdentifier is not a valid 
/// category, an error is output.
/// In the case that the newIdentifier is the same as an existing 
/// category, the existing category will be overwritten/merged 
/// with the updated category. (see addCategory()).
/// @param et ExpenseTracker object
/// @param args Arguments that contains --category
void performUpdateCategory(ExpenseTracker& et, const cxxopts::ParseResult& args);

/// @brief Performs the update action on item specifically. Updating an item 
/// requires at least one of description, amount or date arguments to be specified
/// otherwise an error is output.
/// Additional error messages may be output if erroneous data is given. 
/// Otherwise, the item's properties will be updated to reflect the 
/// specified arguments. 
/// @param et ExpenseTracker object. 
/// @param args Arguments that may include description, amount or date. 
void performUpdateItem(ExpenseTracker& et, const cxxopts::ParseResult& args);

// ------------------------------------------------
//                HELPER FUNCTIONS
// ------------------------------------------------

/// @brief Tries to get hte given category from the ExpenseTracker.
/// If not successful, outputs an error message and an exception is thrown.
/// @param et ExpenseTracker object.
/// @param category Category identifer. 
/// @return Refernence to the Category only if successful. 
Category& tryGetCategory(const ExpenseTracker& et, const std::string& category);

/// @brief Tries to get the given item from the ExpenseTracker Category.
/// If not successful, outputs an error message and an exception is thrown. 
/// @param et ExpenseTracker object.
/// @param category Category identifier. 
/// @param item Item identifier.
/// @return Reference to the Item only if successful. 
Item& tryGetItem(const ExpenseTracker& et, const std::string& category, const std::string& item);

/// @brief Tries to parse the given string to an amount.
/// If not successful, outputs an error message and throws the exception.
/// @param amountStr String to be parsed.
/// @return amount only if successful. 
double tryParseAmount(const std::string& amountStr);

/// @brief Tries to parse the given string to a Date.
/// If not successful, outputs an error message and throws the exception.
/// @param dateStr String to be parsed.
/// @return Date only if parse was successful. 
Date tryParseDate(const std::string& dateStr);


} // namespace App

#endif // _371EXPENSES_H
