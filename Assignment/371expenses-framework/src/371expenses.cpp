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
const char ERROR_INVALID_ACTION[] = "Error: invalid action argument(s).";
const char ERROR_INVALID_CATEGORY[] = "Error: invalid category argument(s).";
const char ERROR_INVALID_ITEM[] = "Error: invalid item argument(s).";
const char ERROR_INVALID_DATE[] = "Error: invalid date argument.";
const char ERROR_INVALID_AMOUNT[] = "Error: invalid amount argument.";
const char ERROR_INVALID_TAG[] = "Error: invalid tag argument(s).";
const char ERROR_MISSING_CATEGORY[] = "Error: missing category argument(s).";
const char ERROR_MISSING_ITEM[] = "Error: missing item argument(s).";
const char ERROR_MISSING_CREATE_ARGUMENTS[] = "Error: missing category, item, amount, description argument(s).";
const char ERROR_MISSING_DELETE_ARGUMENTS[] = "Error: missing category, item, or tag argument(s).";
 
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

/// @brief Create a cxxopts instance.
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

  // Check if Category exists
  try {
    return etObj.getCategory(c).str();
  } catch (std::out_of_range &ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw ex;
  }
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

  // Check if Category exists                        
  try {
    etObj.getCategory(c); 
  } catch (std::out_of_range &ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw ex;
  }    
  
  // Check if Item exists
  try {
    etObj.getCategory(c).getItem(id);
  } catch (std::out_of_range &ex) {
    std::cerr << ERROR_INVALID_ITEM << std::endl;
    throw ex;
  }

  return etObj.getCategory(c).getItem(id).str();
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

  // No Category or Item -> ExpenseTracker
  if (!args.count(CATEGORY_ARGUMENT) || !args.count(ITEM_ARGUMENT)) {
    std::cout << getJSON(et) << std::endl;
    return;
  }

  // Just Category argument -> Category
  if (args.count(CATEGORY_ARGUMENT) && !args.count(ITEM_ARGUMENT)) {
    const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

    std::cout << getJSON(et, category) << std::endl;
    return;
  }

  // Category and Item argument -> Item
  if (args.count(CATEGORY_ARGUMENT) && args.count(ITEM_ARGUMENT)) {
    const std::string item = args[ITEM_ARGUMENT].as<std::string>();
    const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

    std::cout << getJSON(et, category, item) << std::endl;   
    return;
  }

  // Only Item, missing Category -> Error
  std::cerr << ERROR_MISSING_CATEGORY << std::endl;
  throw std::invalid_argument(ITEM_ARGUMENT);
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
  try {
    return et.getCategory(c).getSum();
  } catch (std::out_of_range &ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw &ex; 
  }
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
    return;
  }
    
  std::cout << getSum(et) << std::endl;
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

/// @brief Creates a new Item in the given Category (if the Category does
/// not exist, it will be created) in the ExpenseTracker object
/// with the given properties (overwrites any existing Item with the same 
/// identifier and merges their tags).
/// @param et ExpenseTracker object. 
/// @param c Identifier of Category to add Item into.
/// @param id Identifier of Item to create.
/// @param desc Description of Item.
/// @param amount Amount (£) of Item.
/// @return Reference to created Item.
Item& App::create(ExpenseTracker &et, 
                const std::string &c,
                const std::string &id,
                const std::string &desc,
                const double &amount) {

    return et.newCategory(c).newItem(id, desc, amount, Date());

}



void App::addTags(const std::string& tagList, Item& item) {
  std::istringstream iss(tagList);
  std::string tag;
  while (std::getline(iss, tag, ',')) {
    item.addTag(tag);
  }  
}

void App::performCreateAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  // Just category -> new Category
  if (args.count(CATEGORY_ARGUMENT) 
      && !args.count(ITEM_ARGUMENT) && !args.count(DESCRIPTION_ARGUMENT)
      && !args.count(AMOUNT_ARGUMENT) && !args.count(DATE_ARGUMENT) 
      && !args.count(TAG_ARGUMENT)) {

      const std::string category = args[CATEGORY_ARGUMENT].as<std::string>();

      create(et, category);
      return;
  }

  // Category, item, description, amount (optional date or tags) -> new Item 
  // if date is wrong, do nothing.
  if (args.count(CATEGORY_ARGUMENT) && args.count(ITEM_ARGUMENT) 
      && args.count(DESCRIPTION_ARGUMENT) && args.count(AMOUNT_ARGUMENT)) {

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
      const std::string id = args[ITEM_ARGUMENT].as<std::string>();
      const std::string desc = args[DESCRIPTION_ARGUMENT].as<std::string>();
      const std::string amountStr = args[AMOUNT_ARGUMENT].as<std::string>();
      double amount;
      Date date;

      try {
        amount = std::stod(amountStr);
      } catch (const std::exception &ex) {
        std::cerr << ERROR_INVALID_AMOUNT << std::endl;
        throw ex;
      }

      if (args.count(DATE_ARGUMENT)) {
        const std::string dateStr = args[DATE_ARGUMENT].as<std::string>();
        try {
          date = Date(dateStr);
        } catch (const std::invalid_argument& ex) {
          std::cerr << ERROR_INVALID_DATE << std::endl;
          throw ex;
        }
      } 

      Item& i = create(et, c, id, desc, amount);
      i.setDate(date);

      if (args.count(TAG_ARGUMENT)) {
        const std::string tags = args[TAG_ARGUMENT].as<std::string>();
        addTags(tags, i);
      }
      return;

  }

  std::cerr << ERROR_MISSING_CREATE_ARGUMENTS << std::endl; 
  throw std::invalid_argument("args");
}

// ------------------------------------------------
//                     DELETE
// ------------------------------------------------

bool App::remove(ExpenseTracker& et, const std::string& category) {
  try {
    return et.deleteCategory(category);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw &ex; 
  }
  
}

bool App::remove(ExpenseTracker& et, const std::string& category, const std::string& item) {
  try {
    et.getCategory(category);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw ex; 
  }

  try {
    return et.getCategory(category).deleteItem(item);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_ITEM << std::endl;
    throw ex; 
  }
}

bool App::remove(ExpenseTracker& et, const std::string& category, const std::string& item, const std::string& tag) {
  try {
    et.getCategory(category);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_CATEGORY << std::endl;
    throw ex; 
  }

  try {
    et.getCategory(category).getItem(item);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_ITEM << std::endl;
    throw ex; 
  }

  try {
    return et.getCategory(category).getItem(item).deleteTag(tag);
  } catch(std::out_of_range& ex) {
    std::cerr << ERROR_INVALID_TAG << std::endl;
    throw ex;
  }
}

void App::performDeleteAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  
  // Delete tag
  if (args.count(CATEGORY_ARGUMENT) 
      && args.count(ITEM_ARGUMENT) 
      && args.count(TAG_ARGUMENT)) {

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
      const std::string i = args[ITEM_ARGUMENT].as<std::string>();
      const std::string t = args[TAG_ARGUMENT].as<std::string>();
        
      remove(et, c, i, t);
      return;

  } 
  
  if (args.count(CATEGORY_ARGUMENT) 
      && args.count(ITEM_ARGUMENT) 
      && !args.count(TAG_ARGUMENT)) { // Delete item

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
      const std::string i = args[ITEM_ARGUMENT].as<std::string>();
        
      remove(et, c, i);
      return;

  } 
  
  if (args.count(CATEGORY_ARGUMENT) 
      && !args.count(ITEM_ARGUMENT) 
      && !args.count(TAG_ARGUMENT)) { // Delete category

      const std::string c = args[CATEGORY_ARGUMENT].as<std::string>();
        
      remove(et, c);
      return;

  } 
  
  // Missing arguments 
  std::cerr << ERROR_MISSING_DELETE_ARGUMENTS << std::endl; 
  throw std::invalid_argument("args");
  
}

// ------------------------------------------------
//                     UPDATE
// ------------------------------------------------

// Update category identifier
void App::update(ExpenseTracker& et, const std::string& oldCategoryIdent, const std::string& newCategoryIdent) {
  try {
    Category category = et.getCategory(oldCategoryIdent);
    et.deleteCategory(oldCategoryIdent);
    category.setIdent(newCategoryIdent);
    et.addCategory(category);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw ex; 
  }
}

// update item description
void App::update(ExpenseTracker& et, const std::string& category, const std::string& item, const std::string& description) {
  try {
    et.getCategory(category);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw ex; 
  }

  try {
    et.getCategory(category).getItem(item).setDescription(description);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid item argument(s)." << std::endl;
    throw ex; 
  }

}

// updates item amount
void App::update(ExpenseTracker& et, const std::string& category, const std::string& item, const double& amount) {
  try {
    et.getCategory(category);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw ex; 
  }

  try {
    et.getCategory(category).getItem(item).setAmount(amount);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid item argument(s)." << std::endl;
    throw ex; 
  }

}

// update item date
void App::update(ExpenseTracker& et, const std::string& category, const std::string& item, const Date& date) {
  try {
    et.getCategory(category);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw ex; 
  }

  try {
    et.getCategory(category).getItem(item).setDate(date);
  } catch (const std::out_of_range &ex) {
    std::cerr << "Error: invalid item argument(s)." << std::endl;
    throw ex; 
  }
}

void App::performUpdateAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  // update item 
  if (args.count("category") && args.count("item")) {
    // throw an error if it does not have description, amount or date

    if (!(args.count("description") || args.count("amount") || args.count("date"))) {
      std::cerr << "Error: missing description, amount, or date argument(s)." << std::endl; 
      throw std::invalid_argument("args");
    }

    const std::string c = args["category"].as<std::string>();
    const std::string i = args["item"].as<std::string>();

    if (args.count("amount")) {
      const std::string amountStr = args["amount"].as<std::string>();
      double amount;
      try {
        amount = std::stod(amountStr);
      } catch (const std::exception &e) {
        std::cerr << "Error: invalid amount argument." << std::endl;
        throw e;
      }

      update(et, c, i, amount);      

    }

    if (args.count("date")) {
      const std::string dateStr = args["date"].as<std::string>();
      Date date;
      try {
        date = Date(dateStr);
      } catch (const std::exception &e) {
        std::cerr << "Error: invalid date argument." << std::endl;
        throw e;
      }

      update(et, c, i, date);
    }

    if (args.count("description")) {
      const std::string d = args["description"].as<std::string>();

      update(et, c, i, d);

    }
    
  } else if (args.count("category") && !args.count("item")) { // update category

    std::regex identifiersRegex("([a-zA-Z0-9]+):([a-zA-Z0-9]+)");
    std::cmatch identifiersMatch;
    const std::string identifiers = args["category"].as<std::string>();
    std::regex_match(identifiers.c_str(), identifiersMatch, identifiersRegex);

    if (identifiers.empty()) {
        std::cerr << "Error: invalid category argument." << std::endl;
        throw std::invalid_argument("args");
    }

    update(et, std::string(identifiersMatch[1]), std::string(identifiersMatch[2]));

    
  } else { // handle bad arguments
      std::cerr << "Error: missing category or item argument(s)." << std::endl; 
      throw std::invalid_argument("args");  
  }
  // Otherwise, ignore other arguments
}

