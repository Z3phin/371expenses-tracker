// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Item class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). An Item also has a description (e.g. 'Costa
// Coffee'), a double amount (e.g. 2.55), and date associated with it. 
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include "date.h"
#include "lib_json.hpp"
#include <vector> // would have used a set - but the tests require the order they were inserted in
#include <string>

class Item {
    private:
        std::string identifier; 
        std::string description; 
        double amount; 
        Date date;
        std::vector<std::string> tags; 

    public:
    
        // ------------------------------------------------
        //                  Constructors
        // ------------------------------------------------

        /// @brief Constructs an Item with an identifier, description, amount and date. 
        /// @param _identifier identifier of this item.
        /// @param _description description of this item.
        /// @param _amount amount belonging to this expense item (e.g £42.11)
        /// @param _date date of this item. 
        Item(const std::string &_identifier, const std::string &_description, const double &_amount, const Date &_date) noexcept;

        // ------------------------------------------------
        //                      Getters
        // ------------------------------------------------

        /// @brief Returns the identifier for this Item.
        /// @return identifier of this item.
        std::string getIdent() const noexcept; 

        /// @brief Returns the description of this item.
        /// @return the description of this item. 
        std::string getDescription() const noexcept;

        /// @brief Returns the amount for this Item.
        /// @return the amount for this Item.
        double getAmount() const noexcept;

        /// @brief Gets the date belonging to this item.
        /// @return Date object belonging to this item
        Date getDate() const noexcept;

        // ------------------------------------------------
        //                      Setters
        // ------------------------------------------------

        /// @brief Sets the description of this Item.
        /// @param _description new description.
        void setDescription(const std::string &_description) noexcept;

        /// @brief Updates the amount for this item.
        /// @param _amount new amount. 
        void setAmount(const double &_amount) noexcept;

        /// @brief Updates the date belonging to this Item.
        /// @param _date new date for this item. 
        void setDate(const Date &_date) noexcept;
    

        // ------------------------------------------------
        //                  Tag Functions 
        // ------------------------------------------------

        /// @brief Adds the provided tag to the tags attached to this Item, only if it not already an existing tag.
        /// @param tag tag to tbe added
        /// @return True if the tag was added, otherwise false 
        bool addTag(const std::string &tag) noexcept;

        /// @brief Deletes the provided tag from this Item's tags
        /// @param tag tag to be deleted
        /// @return True if this tag was deleted. 
        /// @throw std::out_of_range - thrown when the given tag does not exist.
        bool deleteTag(const std::string &tag);

        /// @brief Checks whether the provided string is a tag attached to this object. 
        /// @param tag string to be checked. 
        /// @return True if the tag exists. Otherwise return false.
        bool containsTag(const std::string &tag) const noexcept;

        /// @brief Returns the number of tags belonging to this item
        /// @return number of tags.
        unsigned int numTags() const noexcept;

        /// @brief Merges the tags of another Item object with this object.
        /// @param other Item with tags to be merged into this object.
        void mergeTags(const Item& other) noexcept;        

        // ------------------------------------------------
        //               JSON Representation 
        // ------------------------------------------------

        /// @brief Returns a std::string of the JSON representation of the data in this Item in the format:
        /// 
        /// {"amount": xx.xx,"date":YYYY-MM-DD,"description":xxxxxxx,"tags":["tag","tag1",...,"tagN"]}
        ///
        /// @return std::string of the JSON representation of the data in this Item.
        std::string str() const noexcept; 

        friend void to_json(nlohmann::json& json, const Item& item) noexcept; 
        friend void from_json(const nlohmann::json& json, Item& item); 

        // ------------------------------------------------
        //                    Operators 
        // ------------------------------------------------

        /// @brief Compares two Item objects. 
        ///        Two Item objects are equal only if they have the same identifier, date, amount, description, and tags.
        /// @param lhs left hand side item.
        /// @param rhs right hand side item.
        /// @return True if lhs identifier, date, amount and tags are the same as rhs. Otherwise false.
        friend bool operator==(const Item& lhs, const Item& rhs) noexcept;

        /// @brief Compares two Item objects. 
        ///        Two Item objects are equal only if they have the same identifier, date, amount, description, and tags.
        /// @param lhs left hand side item.
        /// @param rhs right hand side item.
        /// @return True if lhs identifier, date, amount and tags are the same as rhs. Otherwise false.
        friend bool operator!=(const Item& lhs, const Item& rhs) noexcept;
        
};

#endif // ITEM_H
