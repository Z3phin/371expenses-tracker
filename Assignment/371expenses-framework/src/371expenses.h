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

// Enums (short for enumerations) are similar to their Java implementation. It
// is a user-defined type, used to assign names to internal constants in code,
// instead of simply passing in integers/strings etc.
//
// For example, functions can take a value/constant from a specific enum and use
// it in a switch statement, doing different things
//
// As such, it is a useful way for us to specify information in both a machine
// and human-readable format.
//
// Unlike Java, enums in C++ only map to integer values. You can either let the
// compiler generate the values automatically, in which it allocates a unique
// integer (0-indexed). Or, you can set the value by giving the name followed by
// = <value> (e.g. CREATE=0).
//
// This enum specifies the five different values we support in the action
// program argument.
enum Action { CREATE, SUM, JSON, DELETE, UPDATE };

int run(int argc, char *argv[]);

cxxopts::Options cxxoptsSetup();

App::Action parseActionArgument(cxxopts::ParseResult &args);

std::string getJSON(ExpenseTracker &et);
std::string getJSON(ExpenseTracker &et, const std::string &c);
std::string getJSON(ExpenseTracker &et, const std::string &c, const std::string &id);

// ------------------------------------------------
//                      SUM
// ------------------------------------------------

/// @brief Returns the sum of all the Items in the ExpenseTracker object.
/// @param et ExpenseTracker object.
/// @return Sum of all items. 
double getSum(ExpenseTracker &et) noexcept;

/// @brief Returns the sum of all the Items in the Category contained
/// in the ExpenseTracker object. 
/// @param et ExpenseTracker object.
/// @param c Category identifier. 
/// @return Sum of all Items in the Category
/// @throws std::out_of_range if Category is not in ExpenseTracker object.
double getSum(ExpenseTracker &et, const std::string &c);

/// @brief Performs the Sum action. Accordingly to the arguments,
/// either the sum of all items in the whole ExpenseTracker is printed,
/// or if a category is given, the sum of the items only in that
/// category.  
/// @param et ExpenseTracker object.
/// @param args Command line arguments that may include "category"
/// @throws std::out_of_range if the Category is not in the ExpenseTracker.
void performSumAction(ExpenseTracker &et, cxxopts::ParseResult &args);

// ------------------------------------------------
//                     CREATE
// ------------------------------------------------

/// @brief Creates a new Category with the given identifier in the 
/// ExpenseTracker object.
/// @param et ExpenseTracker object.
/// @param c Identifier of Category to create
/// @return Reference to Category created.  
Category& create(ExpenseTracker &et, const std::string &c);      

/// @brief Creates a new Item in the given Category only if it does not exist
/// already.
/// @param et ExpenseTracker object. 
/// @param c Identifier of Category to add Item into.
/// @param id Identifier of Item to create.
/// @param desc Description of Item.
/// @param amount Amount (£) of Item.
/// @return Reference to the created or already existing Item.
Item& create(ExpenseTracker &et, 
                const std::string &c,
                const std::string &id,
                const std::string &desc,
                const double &amount);

/// @brief Adds a list of comma separated tags to the item.
/// @param item Item to add tags to.
/// @param tagList List of tags to add.
void addTags(Item& item, const std::string& tagList);

/// @brief Performs corresponding actions for "create" according to the arguments, i.e. 
/// either creating a category or an item, using the given ExpenseTracker. If 
/// required properties are missing, for example --description for item, an error occurs. 
/// @param et ExpenseTracker object
/// @param args arguments including --category, --item and item's properties
void performCreateAction(ExpenseTracker &et, cxxopts::ParseResult &args);

/// @brief Performs the actions for creating an item specifically. An item requires
/// an identifier, a description, an amount (£), and the category it belongs to 
/// minimally. Optionally, a date and tags can be specified. If date is not 
/// specified, today's date is attached to the created item.
/// @param et ExpenseTracker to add the item to.
/// @param args arguments including category, item, description, amount, date and tags.
void performCreateItem(ExpenseTracker &et, cxxopts::ParseResult &args);

// ------------------------------------------------
//                     DELETE
// ------------------------------------------------

bool remove(ExpenseTracker& et, const std::string& category);
bool remove(ExpenseTracker& et, const std::string& category, const std::string& item);
bool remove(ExpenseTracker& et, const std::string& category, const std::string& item, const std::string &tag);

// Update category identifier
void update(ExpenseTracker& et, const std::string& oldCategoryIdent, const std::string& newCategoryIdent);

// update item 
void update(Item& item, cxxopts::ParseResult &args);

void performJsonAction(ExpenseTracker &et, cxxopts::ParseResult &args);



void performDeleteAction(ExpenseTracker &et, cxxopts::ParseResult &args);

void performUpdateAction(ExpenseTracker &et, cxxopts::ParseResult &args);
void performUpdateCategory(ExpenseTracker &et, cxxopts::ParseResult &args);
void performUpdateItem(ExpenseTracker &et, cxxopts::ParseResult &args);

Category& tryGetCategory(ExpenseTracker& et, const std::string& category);
Item& tryGetItem(ExpenseTracker& et, const std::string& category, const std::string& item);

double tryParseAmount(const std::string& amountStr);
Date tryParseDate(const std::string& dateStr);


} // namespace App

#endif // _371EXPENSES_H
