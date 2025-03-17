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

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a ExpenseTracker object
//  2. Parse the 'action' argument to decide what action should be taken
//     (json, create, sum, delete, update).  'json' and 'sum' are the easiest to implement and
//     'update' is the hardest. The details of how these arguments work is in
//     the coursework specification.
//  3. Save the updated ExpenseTracker object to the JSON file if there have been
//     changes (calling save() on the ExpenseTracker object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
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
          throw std::runtime_error("update not implemented");
          break;
        case Action::DELETE:
          throw std::runtime_error("delete not implemented");
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

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
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

// TODO Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
  std::string input = args["action"].as<std::string>();

  for (int i = 0; i < (int) input.length(); i++) {
      input[i] = std::tolower(input.at(i));
  }

  if (input == "create") {
    return Action::CREATE; 
  } else if (input == "delete") {
    return Action::DELETE; 
  } else if (input == "sum") {
    return Action::SUM;
  } else if (input == "update") {
    return Action::UPDATE;
  } else if (input == "json") {
    return Action::JSON;
  } else {
    std::cerr << "Error: invalid action argument(s)." << std::endl;
    throw std::invalid_argument("action");
  }

}

// TODO Write a function, getJSON, that returns a std::string containing the
// JSON representation of a ExpenseTracker object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  ExpenseTracker etObj{};
//  std::cout << getJSON(etObj);
std::string App::getJSON(ExpenseTracker &etObj) {
  return etObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a ExpenseTracker object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function and
// make any other adjustments).
//
// Example:
//  ExpenseTracker etObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(etObj, c);
std::string App::getJSON(ExpenseTracker &etObj, const std::string &c) {
  try {
    return etObj.getCategory(c).str();
  } catch (std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw ex;
  }
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific ExpenseItem in a ExpenseTracker object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function and
// make any other adjustments).
//
// Example:
//  ExpenseTracker etObj{};
//  std::string c = "category argument value";
//  std::string id = "expense id argument value";
//  std::cout << getJSON(etObj, c, id);
std::string App::getJSON(ExpenseTracker &etObj, 
                         const std::string &c,
                         const std::string &id) {
  try {
    etObj.getCategory(c); 
  } catch (std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw ex;
  }    
  
  try {
    etObj.getCategory(c).getItem(id);
  } catch (std::out_of_range &ex) {
    std::cerr << "Error: invalid item argument(s)." << std::endl;
    throw ex;
  }

  return etObj.getCategory(c).getItem(id).str();
}

double App::getSum(ExpenseTracker &et) {
  return et.getSum();
}

double App::getSum(ExpenseTracker &et, const std::string &c) {
  try {
    return et.getCategory(c).getSum();
  } catch (std::out_of_range &ex) {
    std::cerr << "Error: invalid category argument(s)." << std::endl;
    throw &ex; 
  }
}

Category& App::createCategory(ExpenseTracker &et, 
                        const std::string &c) {
    return et.newCategory(c);
}

Item& App::createItem(ExpenseTracker &et, 
                const std::string &c,
                const std::string &id,
                const std::string &desc,
                const double &amount) {

    return et.newCategory(c).newItem(id, desc, amount, Date());

}

void App::performJsonAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  std::string output;

  // no args -> expense tracker
  // just category -> category
  // category and item -> item
  // just item -> error.

  if (args.count("item")) {
    if (args.count("category")) {
      const std::string item = args["item"].as<std::string>();
      const std::string category = args["category"].as<std::string>();
      std::cout << getJSON(et, category, item) << std::endl;
    } else {
      std::cerr << "Error: missing category argument(s)." << std::endl;
      throw std::invalid_argument("item");
    }
  } else if (args.count("category")) {
    const std::string category = args["category"].as<std::string>();
    std::cout << getJSON(et, category) << std::endl;
  } else {
    std::cout << getJSON(et) << std::endl;
  }
}

void App::performSumAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  if (args.count("category")) {
    const std::string category = args["category"].as<std::string>();
      std::cout << getSum(et, category) << std::endl;
  } else {
    std::cout << getSum(et) << std::endl;
  }
}

void App::addTags(const std::string& tagList, Item& item) {
  std::istringstream iss(tagList);
  std::string tag;
  while (std::getline(iss, tag, ',')) {
    item.addTag(tag);
  }  
}

void App::performCreateAction(ExpenseTracker &et, cxxopts::ParseResult &args) {
  if (args.count("category") && args.count("item") && args.count("description")
      && args.count("amount")) {
        const std::string c = args["category"].as<std::string>();
        const std::string id = args["item"].as<std::string>();
        const std::string desc = args["description"].as<std::string>();
        const std::string amountStr = args["amount"].as<std::string>();

        double amount;
        try {
          amount = std::stod(amountStr);
        } catch (const std::exception &e) {
          std::cerr << "Error: invalid amount argument." << std::endl;
          throw e;
        } 

        // new item and possibly category
        Item& i = createItem(et, c, id, desc, amount);

        if (args.count("date")) {
          const std::string dateStr = args["date"].as<std::string>();
          try {
            i.setDate(Date(dateStr));
          } catch(const std::invalid_argument& e) { 
            std::cerr << "Error: invalid date argument." << std::endl;
            throw e;
          } 
        }

        if (args.count("tag")) {
          const std::string tags = args["tag"].as<std::string>();
          addTags(tags, i);
        }

  } else if (args.count("category") 
             && (!args.count("item") 
                 && !args.count("desciption")
                 && !args.count("amount") 
                 && !args.count("date") 
                 && (!args.count("tag")))) {

      const std::string category = args["category"].as<std::string>();
      createCategory(et, category);

  } else {
     std::cerr << "Error: missing category, item, amount, description argument(s)." << std::endl; 
     throw std::invalid_argument("args");
  }
}



