// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "371expenses.h"
#include "lib_cxxopts.hpp"

// ------------------------------------------------
//                  Constants
// ------------------------------------------------

const char ACTION_ARG_CREATE[] = "create";
const char ACTION_ARG_DELETE[] = "delete";
const char ACTION_ARG_UPDATE[] = "update";
const char ACTION_ARG_JSON[]   = "json";
const char ACTION_ARG_SUM[]    = "sum";

const char CATEGORY_ARGUMENT[] = "category";
const char DESCRIPTION_ARGUMENT[] = "description";
const char AMOUNT_ARGUMENT[] = "amount";
const char ITEM_ARGUMENT[] = "item";
const char DATE_ARGUMENT[] = "date";
const char TAG_ARGUMENT[] = "tag";

const char ERROR_INVALID_START[] = "Error: invalid ";
const char ERROR_INVALID_END[] = " arguments(s).";
const char ERROR_INVALID_ACTION[] = "Error: invalid action argument(s).";
const char ERROR_INVALID_CATEGORY[] = "Error: invalid category argument(s).";
const char ERROR_INVALID_ITEM[] = "Error: invalid item argument(s).";
const char ERROR_INVALID_DATE[] = "Error: invalid date argument(s).";
const char ERROR_INVALID_AMOUNT[] = "Error: invalid amount argument(s).";
const char ERROR_INVALID_TAG[] = "Error: invalid tag argument(s).";

const char ERROR_MISSING_CATEGORY[] = "Error: missing category argument(s).";
const char ERROR_MISSING_ITEM[] = "Error: missing item argument(s).";
const char ERROR_MISSING_CREATE_ARGUMENTS[] = "Error: missing category, item, amount, description argument(s).";
const char ERROR_MISSING_DELETE_ARGUMENTS[] = "Error: missing category, item, or tag argument(s).";
const char ERROR_MISSING_UPDATE_ITEM_ARGUMENTS[] = "Error: missing description, amount, or date argument(s).";
const char ERROR_MISSING_UPDATE_ARGUMENTS[] = "Error: missing category or item argument(s)."; 
const char UPDATE_CATEGORY_IDENT_REGEX[] = "([a-zA-Z0-9]+):([a-zA-Z0-9]+)";

const char TAGS_LIST_DELIMITER = ',';
 
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }

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
int App::run(int argc, char *argv[]) {
  auto options = App::cxxoptsSetup();

    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
      std::cout << options.help() << '\n';
      return 0;
    }

    // Open the database and construct the ExpenseTracker
    const std::string db = args["db"].as<std::string>();

    ExpenseTracker etObj{};
    // Only uncomment this once you have implemented the load function!
    etObj.load(db);

    // try parsing arguments and exit if there is an exception
    try {
      const Action a = parseActionArgument(args);
      switch (a) {
        case Action::CREATE:
          performCreateAction(etObj, args);
          etObj.save(db);
          break;
        case Action::JSON:
          performJsonAction(etObj, args);
          break;
        case Action::UPDATE:
          performUpdateAction(etObj, args);
          etObj.save(db);
          break;
        case Action::DELETE:
          performDeleteAction(etObj, args);
          etObj.save(db);
          break;
        case Action::SUM:
          performSumAction(etObj, args);
          break;
        default:
          throw std::runtime_error("unknown action");
      }
      return 0;
    } catch (...) {
      return 1;
    }
    
}

// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);

/// @brief Create a cxxopts instance with the appropriate 
/// arguments for this app.
/// @return cxxopts instance.
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371expenses", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371expenses database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action",
      "Action to take, can be: 'create', 'json', 'update', 'delete', 'sum'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action (create, json, update, delete, sum) to a category. If you "
      "want to add a category, set the action argument to 'create' and the "
      "category argument to your chosen category identifier.",
      cxxopts::value<std::string>())(

      "description",
      "Apply action (create, update) to an expense description. If you want to "
      "add an expense item, set the action argument to 'create', the category "
      "argument to your chosen category identifier and the description "
      "argument to the expense description and the amount argument to the "
      "expense amount, and the id argument to the unique expense id.",
      cxxopts::value<std::string>())(

      "amount",
      "Apply action (create, update) to an expense amount. If you want to add "
      "an expense item, set the action argument to 'create', the category "
      "argument to your chosen category identifier and the description "
      "argument to the expense description and the amount argument to the "
      "expense amount, and the id argument to the unique expense id.",
      cxxopts::value<std::string>())(

      "item",
      "Apply action (create, update, json, delete) to an expense item "
      "identified by its id. If you want to update an expense item, set the "
      "action argument to 'update', the id argument to the expense identifier, "
      "the description argument to the updated expense description, and the "
      "amount argument to the updated expense amount.",
      cxxopts::value<std::string>())(

      "date",
      "When creating or updating an expense item, set the date flag to change "
      "the expense item's date to the one specified as an argument (e.g. "
      "'2024-11-23'). If the date argument is ommitted set the expense date "
      "to today's date when creating an expense item, and leave the date "
      "unchanged if omitted when updating an expense item.",
      cxxopts::value<std::string>())(

      "tag",
      "Apply action (create or delete) to a tag.  If you want to add a tag, "
      "set the action argument to 'create', the category argument to your "
      "chosen category identifier, the item argument to your chosen item "
      "identifier, and the tag argument to a single tag 'tag' or comma "
      "seperated list of tags: 'tag1,tag2'). The action update/sum/json are "
      "unsupported here.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);

/// @brief Case-insensitively checks the action argument retrieved from cxxopts
/// and converts this to a value from the Action enum.
/// @param args arguments from cxxopts.
/// @return Action value based on action argument. 
/// @throws std::invalid_argument exception if an invalid value is given. 
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
  std::string input = args["action"].as<std::string>();

  for (int i = 0; i < (int) input.length(); i++) {
      input[i] = std::tolower(input.at(i));
  }

  if (input == ACTION_ARG_CREATE) return Action::CREATE;
  if (input == ACTION_ARG_DELETE) return Action::DELETE;
  if (input == ACTION_ARG_SUM)    return Action::SUM;
  if (input == ACTION_ARG_UPDATE) return Action::UPDATE;
  if (input == ACTION_ARG_JSON)   return Action::JSON; 
  else {
    std::cerr << ERROR_INVALID_ACTION << std::endl;
    throw std::invalid_argument("action");
  }

}


// ------------------------------------------------
//                      JSON 
// ------------------------------------------------

// Example:
//  ExpenseTracker etObj{};
//  std::cout << getJSON(etObj);

/// @brief Returns a std::string containing the JSON representation of a
/// ExpenseTracker object. 
/// @param etObj 
/// @return JSON representation of ExpenseTracker as a string. 
std::string App::getJSON(ExpenseTracker &etObj) {
  return etObj.str();
}


// Example:
//  ExpenseTracker etObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(etObj, c);

/// @brief Returns a std::string containing the JSON representation of a 
/// specific Category in an ExpenseTracker object. 
/// @param etObj ExpenseTracker object.
/// @param c Category identifier
/// @return JSON represenation of Category in ExpenseTracker as a string. 
/// @throws std::out_of_range if Category is not in ExpenseTracker object.
std::string App::getJSON(ExpenseTracker &etObj, const std::string &c) {
  return tryGetCategory(etObj, c).str();
}

// Example:
//  ExpenseTracker etObj{};
//  std::string c = "category argument value";
//  std::string id = "expense id argument value";
//  std::cout << getJSON(etObj, c, id);

/// @brief Returns a std::string containing the JSON representation of a 
/// specific Item in a ExpenseTracker object.
/// @param etObj ExpenseTracker object.
/// @param c Category identifier
/// @param id Item identifier.
/// @return JSON representation of Item as a string.
/// @throws std::out_of_range if Category or Item is not in ExpenseTracker.
std::string App::getJSON(ExpenseTracker &etObj, 
                         const std::string &c,
                         const std::string &id) {

  return tryGetItem(etObj, c, id).str();
}

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
void App::performJsonAction(ExpenseTracker &et, cxxopts::ParseResult &args) {

    
    if (!args.count(CATEGORY_ARGUMENT) 
        && !args.count(ITEM_ARGUMENT)) { // No Category or Item -> ExpenseTracker

      std::cout << getJSON(et) << std::endl;

    } else if (args.count(CATEGORY_ARGUMENT) 
                && !args.count(ITEM_ARGUMENT)) { // Just Category argument -> Category

      const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

      std::cout << getJSON(et, category) << std::endl;

    } else if (args.count(CATEGORY_ARGUMENT)
               && args.count(ITEM_ARGUMENT)) { // Category and Item argument -> Item

      const std::string item = args[ITEM_ARGUMENT].as<std::string>();
      const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

      std::cout << getJSON(et, category, item) << std::endl;   
      
    } else {                                // Only Item, missing Category -> Error

        std::cerr << ERROR_MISSING_CATEGORY << std::endl;
        throw std::invalid_argument(ITEM_ARGUMENT);
    }
}

// ------------------------------------------------
//                      SUM
// ------------------------------------------------

/// @brief Returns the sum of all the Items in the ExpenseTracker object.
/// @param et ExpenseTracker object.
/// @return Sum of all items. 
double App::getSum(ExpenseTracker &et) noexcept {
    return et.getSum();
}

/// @brief Returns the sum of all the Items in the Category contained
/// in the ExpenseTracker object. 
/// @param et ExpenseTracker object.
/// @param c Category identifier. 
/// @return Sum of all Items in the Category
/// @throws std::out_of_range if Category is not in ExpenseTracker object.
double App::getSum(ExpenseTracker &et, const std::string &c) {
    return tryGetCategory(et, c).getSum();
}

/// @brief Performs the Sum action. Accordingly to the arguments,
/// either the sum of all items in the whole ExpenseTracker is printed,
/// or if a category is given, the sum of the items only in that
/// category.  
/// @param et ExpenseTracker object.
/// @param args Command line arguments that may include "category"
/// @throws std::out_of_range if the Category is not in the ExpenseTracker.
void App::performSumAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
    if (args.count(CATEGORY_ARGUMENT)) {
        const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

        std::cout << getSum(et, category) << std::endl;
      
    } else {
      
        std::cout << getSum(et) << std::endl;
    }
}

// ------------------------------------------------
//                     CREATE
// ------------------------------------------------

/// @brief Creates a new Category with the given identifier in the 
/// ExpenseTracker object.
/// @param et ExpenseTracker object.
/// @param c Identifier of Category to create
/// @return Reference to Category created.  
Category& App::create(ExpenseTracker &et, 
                        const std::string &c) {
    return et.newCategory(c);
}

/// @brief Creates a new Item in the given Category only if it does not exist
/// already.
/// @param et ExpenseTracker object. 
/// @param c Identifier of Category to add Item into.
/// @param id Identifier of Item to create.
/// @param desc Description of Item.
/// @param amount Amount (£) of Item.
/// @return Reference to the created or already existing Item.
Item& App::create(ExpenseTracker &et, 
                const std::string &c,
                const std::string &id,
                const std::string &desc,
                const double &amount) {

    Category& category = tryGetCategory(et, c);
    if (!category.containsItem(id)) {
        return category.newItem(id, desc, amount, Date());
    } else {
        return category.getItem(id);   
    }


}

/// @brief Adds a list of comma separated tags to the item.
/// @param item Item to add tags to.
/// @param tagList List of tags to add.
void App::addTags(Item& item, const std::string& tagList) {
  std::istringstream iss(tagList);
  std::string tag;

  while (std::getline(iss, tag, TAGS_LIST_DELIMITER)) {
    item.addTag(tag);
  }  
}

/// @brief Performs corresponding actions for "create" according to the arguments, i.e. 
/// either creating a category or an item, using the given ExpenseTracker. If 
/// required properties are missing, for example --description for item, an error occurs. 
/// @param et ExpenseTracker object
/// @param args arguments including --category, --item and item's properties
void App::performCreateAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  
  if (args.count(CATEGORY_ARGUMENT) // Just category -> new Category
      && !args.count(ITEM_ARGUMENT) 
      && !args.count(DESCRIPTION_ARGUMENT)
      && !args.count(AMOUNT_ARGUMENT) 
      && !args.count(DATE_ARGUMENT) 
      && !args.count(TAG_ARGUMENT)) {

      const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

      create(et, category);
  } else if (args.count(CATEGORY_ARGUMENT) // Require a category and item properties -> new Item
             && args.count(ITEM_ARGUMENT) 
             && args.count(DESCRIPTION_ARGUMENT) 
             && args.count(AMOUNT_ARGUMENT)) {

      performCreateItem(et, args);

  } else {
      std::cerr << ERROR_MISSING_CREATE_ARGUMENTS << std::endl; 
      throw std::invalid_argument("args");
  }
}

/// @brief Performs the actions for creating an item specifically. An item requires
/// an identifier, a description, an amount (£), and the category it belongs to 
/// minimally. Optionally, a date and tags can be specified. If date is not 
/// specified, today's date is attached to the created item.
/// @param et ExpenseTracker to add the item to.
/// @param args arguments including category, item, description, amount, date and tags.
void App::performCreateItem(ExpenseTracker &et, cxxopts::ParseResult &args) {
    const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
    const std::string id = args[ITEM_ARGUMENT].as<std::string>();
    const std::string desc = args[DESCRIPTION_ARGUMENT].as<std::string>();
    const std::string amountStr = args[AMOUNT_ARGUMENT].as<std::string>();
    double amount = tryParseAmount(amountStr);
    Date date;

    if (args.count(DATE_ARGUMENT)) {
      const std::string dateStr = args[DATE_ARGUMENT].as<std::string>();
      date = tryParseDate(dateStr);
    } 

    Item& item = create(et, c, id, desc, amount);
    item.setDate(date); // Possibly does nothing.

    if (args.count(TAG_ARGUMENT)) {
      const std::string tags = args[TAG_ARGUMENT].as<std::string>();
      addTags(item, tags);
    }
}

// ------------------------------------------------
//                     DELETE
// ------------------------------------------------

/// @brief Attempts to delete the given category from the ExpenseTracker
/// If the category is not in the ExpenseTracker, outputs an error.
/// @param et ExpenseTracker object
/// @param category Identifier of Category to be deleted
/// @return True only if category was deleted.
bool App::remove(ExpenseTracker& et, const std::string& category) {
  try {
    return et.deleteCategory(category);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw &ex; 
  }
  
}

/// @brief Attempts to delete the given item from the given category.
/// If the item does not exist in the category, outputs an error. 
/// @param et ExpenseTracker object.
/// @param catIdent Identifier of Category possibly containing item. 
/// @param item Identifier of Item to delete. 
/// @return True only if the Item was deleted. 
bool App::remove(ExpenseTracker& et, 
                 const std::string& catIdent, 
                 const std::string& item) {
  Category& category = tryGetCategory(et, catIdent);

  try {
    return category.deleteItem(item);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_ITEM << std::endl;
    throw ex; 
  }
}

/// @brief Attempts to delete the given tag from an Item in a Category.
/// If the tag does not exist on the Item, outputs an error message. 
/// @param et ExpenseTracker object
/// @param category Identifier of Category.
/// @param id Identifier of Item.
/// @param tag Tag to be deleted
/// @return True only if Tag was deleted.
bool App::remove(ExpenseTracker& et, 
                 const std::string& category, 
                 const std::string& id, 
                 const std::string& tag) {

  Item& item = tryGetItem(et, category, id);

  try {
    return item.deleteTag(tag);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_TAG << std::endl;
    throw ex;
  }
}

/// @brief Performs the action for deleting either a category, an item or a tag. 
/// If an invalid combination of arguments, e.g. no arguments, tag without an item,
/// or an item without a category, an error is output.
/// @param et ExpenseTracker objects
/// @param args arguments that may include category, item and tag.
void App::performDeleteAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  
  
  if (args.count(CATEGORY_ARGUMENT) 
      && args.count(ITEM_ARGUMENT) 
      && args.count(TAG_ARGUMENT)) { // Delete tag

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
      const std::string i = args[ITEM_ARGUMENT].as<std::string>();
      const std::string t = args[TAG_ARGUMENT].as<std::string>();
        
      remove(et, c, i, t);

  } else if (args.count(CATEGORY_ARGUMENT) 
             && args.count(ITEM_ARGUMENT) 
             && !args.count(TAG_ARGUMENT)) { // Delete item

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
      const std::string i = args[ITEM_ARGUMENT].as<std::string>();
        
      remove(et, c, i);

  } else if (args.count(CATEGORY_ARGUMENT) 
             && !args.count(ITEM_ARGUMENT) 
             && !args.count(TAG_ARGUMENT)) { // Delete category

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
        
      remove(et, c);

  } else { // Missing arguments 
    std::cerr << ERROR_MISSING_DELETE_ARGUMENTS << std::endl; 
    throw std::invalid_argument("args");
  }
}

// ------------------------------------------------
//                     UPDATE
// ------------------------------------------------

/// @brief Updates the given Category with the new identifier.
/// If the given Category does not exist in the ExpenseTracker,
/// an error is output.
/// @param et ExpenseTracker object.
/// @param oldCategoryIdent Old Category identifier to be updated.
/// @param newCategoryIdent New Category identifier to update to. 
void App::update(ExpenseTracker& et, 
                 const std::string& oldCategoryIdent, 
                 const std::string& newCategoryIdent) {

    Category category = tryGetCategory(et, oldCategoryIdent);
    et.deleteCategory(oldCategoryIdent); 
    category.setIdent(newCategoryIdent);
    et.addCategory(category);
}

/// @brief Updates the given Item according to the given arguments, 
/// either date, amount, and description. These can be updated 
/// simulataneously 
/// @param item Item whose properties may be updated.
/// @param args arguments that may include description, amount or date.
void App::update(Item& item, cxxopts::ParseResult &args) {

    // Update date
    if (args.count(DATE_ARGUMENT)) {
      Date date = tryParseDate(args[DATE_ARGUMENT].as<std::string>());
      item.setDate(date);

    } 

    // Update amount
    if (args.count(AMOUNT_ARGUMENT)) {
        double amount = tryParseAmount(args[AMOUNT_ARGUMENT].as<std::string>());
        item.setAmount(amount);
    }

    // Update description
    if (args.count(DESCRIPTION_ARGUMENT)) {
      std::string description = args[DESCRIPTION_ARGUMENT].as<std::string>();
      item.setDescription(description);
    }
}

/// @brief Performs the action for updating either the identifier of category,
/// or the properties, data, description or amount, of a specified item. 
/// If an item is specified without a category, an error is output. 
/// Similarly, if a category, item or erroneous data is given, an 
/// an appropriate error is output. 
/// @param et ExpenseTracker object
/// @param args Arguments that may include category, item, description, 
/// amount or date. 
void App::performUpdateAction(ExpenseTracker &et, cxxopts::ParseResult &args) {

    if (args.count(CATEGORY_ARGUMENT) && !args.count(ITEM_ARGUMENT)) { // Update Category
      performUpdateCategory(et, args);

    } else if (args.count(CATEGORY_ARGUMENT) && args.count(ITEM_ARGUMENT)) { // Update Item
      performUpdateItem(et, args);

    } else { // Handle missing arguments
      std::cerr << ERROR_MISSING_UPDATE_ARGUMENTS << std::endl; 
      throw std::invalid_argument("args");
    } 

}

/// @brief Perform the action of updating a category identifier. 
/// A category identifier can be updated with the argument 
/// --category oldIdentifier:newIdentifier.
/// If this pattern is malformed or oldIdentifier is not a valid 
/// category, an error is output.
/// In the case that the newIdentifier is the same as an existing 
/// category, see addCategory() for this behaviour.
/// @param et ExpenseTracker object
/// @param args Arguments that contains --category
void App::performUpdateCategory(ExpenseTracker &et, cxxopts::ParseResult &args) {
    std::regex identifiersRegex(UPDATE_CATEGORY_IDENT_REGEX);
    std::cmatch identifiersMatch;

    const std::string identifiers = args[CATEGORY_ARGUMENT].as<std::string>();
    std::regex_match(identifiers.c_str(), identifiersMatch, identifiersRegex);

    if (identifiers.empty()) {
        std::cerr << ERROR_INVALID_CATEGORY << std::endl;
        throw std::invalid_argument("args");
    }

    const std::string oldIdentifier = std::string(identifiersMatch[1]);
    const std::string newIdentifier = std::string(identifiersMatch[2]);
    update(et, oldIdentifier, newIdentifier);
}

/// @brief Performs the update action on item specifically. Updating an item 
/// requires at least one of description, amount or date arguments to be specified
/// otherwise an error is output.
/// Additional error messages may be output if erroneous data is given. 
/// Otherwise, the item's properties will be updated to reflect the 
/// specified arguments. 
/// @param et ExpenseTracker object. 
/// @param args Arguments that may include description, amount or date. 
void App::performUpdateItem(ExpenseTracker &et, cxxopts::ParseResult &args) {

    // Check if description, amount or date are present.
    if (!(args.count(DESCRIPTION_ARGUMENT) 
          || args.count(AMOUNT_ARGUMENT) 
          || args.count(DATE_ARGUMENT))) {

        std::cerr << ERROR_MISSING_UPDATE_ITEM_ARGUMENTS << std::endl; 
        throw std::invalid_argument("args");        
    }

    const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
    const std::string i = args[ITEM_ARGUMENT].as<std::string>();

    Item& item = tryGetItem(et, c, i);

    update(item, args);
}


// ------------------------------------------------
//                HELPER FUNCTIONS
// ------------------------------------------------


/// @brief Tries to get hte given category from the ExpenseTracker.
/// If not successful, outputs an error message and an exception is thrown.
/// @param et ExpenseTracker object.
/// @param category Category identifer. 
/// @return Refernence to the Category only if successful. 
Category& App::tryGetCategory(ExpenseTracker& et, const std::string& category) {
    try {
        return et.getCategory(category);
    } catch (const std::out_of_range &ex) {
        std::cerr << ERROR_INVALID_CATEGORY << std::endl;
        throw ex; 
    }
}

/// @brief Tries to get the given item from the ExpenseTracker Category.
/// If not successful, outputs an error message and an exception is thrown. 
/// @param et ExpenseTracker object.
/// @param category Category identifier. 
/// @param item Item identifier.
/// @return Reference to the Item only if successful. 
Item& App::tryGetItem(ExpenseTracker& et, const std::string& category, const std::string& item) {
    try {
        return et.getCategory(category).getItem(item);
    } catch (const std::out_of_range &ex) {
        std::cerr << ERROR_INVALID_START << ex.what() << ERROR_INVALID_END << std::endl;
        throw ex; 
    }
}

/// @brief Tries to parse the given string to an amount.
/// If not successful, outputs an error message and throws the exception.
/// @param amountStr String to be parsed.
/// @return amount only if successful. 
double App::tryParseAmount(const std::string& amountStr) {
    try {
        return std::stod(amountStr);
    } catch (const std::exception &e) {
        std::cerr << ERROR_INVALID_AMOUNT << std::endl;
        throw e;
    }
}

/// @brief Tries to parse the given string to a Date.
/// If not successful, outputs an error message and throws the exception.
/// @param dateStr String to be parsed.
/// @return Date only if parse was successful. 
Date App::tryParseDate(const std::string& dateStr) {
    try {
        return Date(dateStr);
    } catch (const std::invalid_argument &e) {
        std::cerr << ERROR_INVALID_DATE << std::endl;
        throw e;
    }
}

