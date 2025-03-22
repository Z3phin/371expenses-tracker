// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// -----------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include <string>
#include "lib_json.hpp"

class Date {
    private: 
        unsigned int year; 
        unsigned int month; 
        unsigned int day; 

        // -----------------------------------------------------
        //                  Helper Functions
        // -----------------------------------------------------

        /// @brief Checks whether or not the given year is a leap year.
        /// @param year year to be checked.
        /// @return True if a leap year, otherwise false. 
        static bool isLeapYear(const unsigned int year) noexcept;

        /// @brief Checks whether the given value is a valid month value. 
        /// @param month month to be checked.
        /// @return True if month is valid, otherwise false. 
        static bool isValidMonth(const unsigned int month) noexcept;

        /// @brief Checks whether the given value is a valid day value (regardless of month)
        /// @param day day to be checked. 
        /// @return True if valid, otherwise false. 
        static bool isValidDay(const unsigned int day) noexcept;

        /// @brief Checks whether the given year, month and day are a valid combination 
        /// (including number of days per month and leap years)
        /// @param year year to be checked
        /// @param month month to be checked.
        /// @param day day to be checked.
        /// @return True if the given year, month and day representa valid date, 
        /// otherwise false. 
        static bool isValidDate(const unsigned int year,   
                                const unsigned int month, 
                                const unsigned int day) noexcept;

    public:

        // ------------------------------------------------
        //                  Constructors
        // ------------------------------------------------

        /// @brief Constructs a Date object with today's date.
        Date() noexcept;

        /// @brief Creates a Date object with the given year, month and day if it is a valid date combination.
        /// @param _year the year to be represented. 
        /// @param _month the month of the year to be represented (1-12).
        /// @param _day the day of the mongth to be represented (1-28/29/30/31 depending on month).
        /// @throws std::invalid_argument - thrown if the combination of year, month and day represents an invalid date.
        Date(const unsigned int _year, const unsigned int _month, const unsigned int _day);

        /// @brief Creates a Date object with the date given as a string with the representation of YYYY-MM-DD.
        ///        If the provided string is not in the correct format or invalid, an exception is thrown. 
        /// @param dateString date represented as a string to be converted (YYYY-MM-DD).
        /// @throws std::invalid_argument thrown when the provided dateString is not valid or in the wrong format.
        Date(const std::string &dateStr);


        // ------------------------------------------------
        //                String Representation
        // ------------------------------------------------

        /// @brief Gives a string representation of this date in the format 'YYYY-MM-DD'.
        /// @return std::string represention of this date in the format 'YYYY-MM-DD'.
        std::string str() const noexcept;


        // ------------------------------------------------
        //                      Setters
        // ------------------------------------------------

        /// @brief Sets this date object to the given date.
        /// @param _year year to be represented
        /// @param _month month of the year (1-12) to to be represented
        /// @param _day day of the month (1-28/29/30/31 depending on month and year) to be represented
        void setDate(const unsigned int _year, const unsigned int _month, const unsigned int _day);

        /// @brief Sets the Date object to the date given as a string with the representation of YYYY-MM-DD.
        ///        If the provided string is not in the correct format or invalid, an exception is thrown. 
        /// @param dateString date represented as a string to be converted (YYYY-MM-DD).
        /// @throws std::invalid_argument thrown when the provided dateStr is not valid or in the wrong format.
        void setDate(const std::string &dateStr);


        // ------------------------------------------------
        //                      Getters
        // ------------------------------------------------

        /// @brief Returns this Date's year value.
        /// @return  value representing the year.
        unsigned int getYear() const noexcept;
        
        /// @brief Returns this Date's month value.
        /// @return  value representing the month of the year (i.e. 1-12).
        unsigned int getMonth() const noexcept;

        /// @brief Returns this Date's day value.
        /// @return value representing the day of the month. (i.e. 1-31 depending on month)
        unsigned int getDay() const noexcept;

        // ------------------------------------------------
        //               JSON Representation 
        // ------------------------------------------------

        /// @brief Converts the Date object into a JSON string in the format "YYYY-MM-DD"
        /// @param json json string to hold Date respresentation. 
        /// @param date Date to be converted to JSON.
        friend void to_json(nlohmann::json& json, const Date& date) noexcept;

        /// @brief Sets a Date object to the date stored in a JSON string of the form "YYYY-MM-DD".
        /// @param json json string representation "YYYY-MM-DD".
        /// @param date Date object to be set.
        /// @throws std::invalid_argument thrown when the provided string is in the wrong format. 
        friend void from_json(const nlohmann::json& json, Date& date);

        // ------------------------------------------------
        //                    Operators 
        // ------------------------------------------------
 
        /// @brief Compares two date objects. Two Date objects are equal only if they represent the same year, month and day.   
        /// @param lhs left hand side object.
        /// @param rhs right hand side object. 
        /// @return True if lhs date is chronologically equal to the rhs date. False otherwise
        friend bool operator==(const Date& lhs, const Date& rhs) noexcept; 

        /// @brief Compares two date objects and returns true if
        /// the first Date object is chronologically before the second date object.
        /// Otherwise return false.
        /// @param lhs left hand side object.
        /// @param rhs right hand side object. 
        /// @return True if lhs date is chronologically before the rhs date. False otherwise
        friend bool operator<(const Date& lhs, const Date& rhs) noexcept;

        /// @brief Compares two date objects and returns true if
        /// the first Date object is chronologically after the second date object.
        /// Otherwise return false. 
        /// @param lhs left hand side object.
        /// @param rhs right hand side object. 
        /// @return True if lhs date is chronologically after rhs date. False otherwise
        friend bool operator>(const Date& lhs, const Date& rhs) noexcept;

        /// @brief Compares two date objects. Two Date objects are not equal if the year, month or day are not equivalant.
        /// @param lhs left hand side object.
        /// @param rhs right hand side object.
        /// @return  True if lhs is not chronologically equal to rhs date (i.e lhs is before or after rhs). False otherwise.
        friend bool operator!=(const Date& lhs, const Date& rhs) noexcept;

        /// @brief Compares two date objecst and returns true if 
        /// the first Date object is chronologically before the second date object.
        /// Otherwise return false. 
        /// @param lhs left hand side object.
        /// @param rhs right hand side object.
        /// @return True if lhs is chronologically on or before rhs. False otherwise. 
        friend bool operator<=(const Date& lhs, const Date& rhs) noexcept;

        /// @brief Compares two date objecst and returns true if 
        /// the first Date object is chronologically on or after the second date object.
        /// Otherwise return false.
        /// @param lhs left hand side object.
        /// @param rhs right hand side object.
        /// @return True if lhs date is chronologiclly on or after rhs date. False otherwise 
        friend bool operator>=(const Date& lhs, const Date& rhs) noexcept;
     
};

#endif // DATE_H
