// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2212805
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "date.h"
#include <iostream>
#include <ctime>
#include <regex>
#include <sstream>


// -----------------------------------------------------
//                  Date Class Functions
// -----------------------------------------------------

// ------------------------------------------------
//                  Constructors
// ------------------------------------------------

const char DATE_REGEX[] = "([0-9]+)-([0-9]+)-([0-9]+)";
const char DATE_DELIMITER = '-';

/// @brief Constructs a Date object with today's date.
Date::Date() noexcept : year(0), month(0), day(0) {
    std::time_t timestamp = std::time(nullptr);
    struct std::tm *datetime = std::localtime(&timestamp);
    this->year = datetime->tm_year + 1900;
    this->month = datetime->tm_mon + 1;
    this->day = datetime->tm_mday;
}

/// @brief Creates a Date object with the given year, month and day if it is a valid date combination.
/// @param _year the year to be represented. 
/// @param _month the month of the year to be represented (1-12).
/// @param _day the day of the mongth to be represented (1-28/29/30/31 depending on month).
/// @throws std::invalid_argument - thrown if the combination of year, month and day represents an invalid date.
Date::Date(const unsigned int _year, const unsigned int _month, const unsigned int _day) : 
    year(0), month(0), day(0) {

    this->setDate(_year, _month, _day);

}

/// @brief Creates a Date object with the date given as a string with the representation of YYYY-MM-DD.
///        If the provided string is not in the correct format or invalid, an exception is thrown. 
/// @param dateString date represented as a string to be converted (YYYY-MM-DD).
/// @throws std::invalid_argument thrown when the provided dateString is not valid or in the wrong format.
Date::Date(const std::string &dateString) 
    : year(0), month(0), day(0) {

    this->setDate(dateString);
}

// ------------------------------------------------
//                String Representation
// ------------------------------------------------

/// @brief Gives a string representation of this date in the format 'YYYY-MM-DD'.
/// @return std::string represention of this date in the format 'YYYY-MM-DD'.
std::string Date::str() const noexcept {
    std::stringstream ss; 
    ss << this->year << DATE_DELIMITER << this->month << DATE_DELIMITER << this->day; 
    return ss.str();
}



// ------------------------------------------------
//                      Setters
// ------------------------------------------------

/// @brief Sets this date object to the given date.
/// @param _year year to be represented
/// @param _month month of the year (1-12) to to be represented
/// @param _day day of the month (1-28/29/30/31 depending on month and year) to be represented
void Date::setDate(const unsigned int _year, const unsigned int _month, const unsigned int _day) {
    if (!isValidDate(_year, _month, _day)) { 
        throw std::invalid_argument(std::to_string(_year) + DATE_DELIMITER 
                                    + std::to_string(_month) + DATE_DELIMITER 
                                    + std::to_string(_day));
    } 

    this->year = _year;
    this->month = _month;
    this->day = _day;

}

/// @brief Sets the date object to the given date as a string with the representation of YYYY-MM-DD.
///        If the provided string is not in the correct format or invalid, an exception is thrown. 
/// @param dateString date represented as a string to be converted (YYYY-MM-DD).
/// @throws std::invalid_argument thrown when the provided dateStr is not valid or in the wrong format.
void Date::setDate(const std::string &dateStr) {
    std::regex dateRegex(DATE_REGEX);
    std::cmatch dateMatch;
    std::regex_match(dateStr.c_str(), dateMatch, dateRegex);

    if (dateMatch.empty()) {
        throw std::invalid_argument(dateStr);
    }

    this->setDate(std::stoi(dateMatch[1]),  // year
                  std::stoi(dateMatch[2]),  // month
                  std::stoi(dateMatch[3])); // day
}



// ------------------------------------------------
//                      Getters
// ------------------------------------------------

/// @brief Returns this Date's year value.
/// @return  value representing the year.
unsigned int Date::getYear() const noexcept {
    return this->year;
}

/// @brief Returns this Date's month value.
/// @return  value representing the month of the year (i.e. 1-12).
unsigned int Date::getMonth() const noexcept {
    return this->month;
}

/// @brief Returns this Date's day value.
/// @return value representing the day of the month. (i.e. 1-31 depending on month)
unsigned int Date::getDay() const noexcept {
    return this->day;
}

// ------------------------------------------------
//               JSON Representation 
// ------------------------------------------------

/// @brief Converts the Date object into a JSON string in the format "YYYY-MM-DD"
/// @param json json string to hold Date respresentation. 
/// @param date Date to be converted to JSON.
void to_json(nlohmann::json& json, const Date& date) noexcept {
    json = date.str();
}

/// @brief Sets a Date object to the date stored in a JSON string of the form "YYYY-MM-DD".
/// @param json json string representation "YYYY-MM-DD".
/// @param date Date object to be set.
/// @throws std::invalid_argument thrown when the provided string is in the wrong format.
void from_json(const nlohmann::json& json, Date& date) {
    std::string dateStr;
    json.get_to(dateStr);
    date.setDate(dateStr);
}

// ------------------------------------------------
//                    Operators 
// ------------------------------------------------

/// @brief Compares two date objects. Two Date objects are equal only if they represent the same year, month and day.
/// @param lhs left hand side object.
/// @param rhs right hand side object. 
/// @return True if lhs date is chronologically equal to the rhs date. False otherwise
bool operator==(const Date& lhs, const Date& rhs) noexcept {
    return (lhs.year == rhs.year 
            && lhs.month == rhs.month
            && lhs.day == rhs.day);
}

/// @brief Compares two date objects and returns true if
/// the first Date object is chronologically before the second date object.
/// Otherwise return false.
/// @param lhs left hand side object.
/// @param rhs right hand side object. 
/// @return True if lhs date is chronologically before the rhs date. False otherwise
bool operator<(const Date& lhs, const Date& rhs) noexcept {
    if (lhs.year < rhs.year) return true; 

    if (lhs.year > rhs.year) return false;

    if (lhs.month < rhs.month) return true; 

    if (lhs.month > rhs.month) return false;
    
    return (lhs.day < rhs.day);
}

/// @brief Compares two date objects and returns true if
/// the first Date object is chronologically after the second date object.
/// Otherwise return false. 
/// @param lhs left hand side object.
/// @param rhs right hand side object. 
/// @return True if lhs date is chronologically after rhs date. False otherwise
bool operator>(const Date& lhs, const Date& rhs) noexcept {
    return !(lhs < rhs || lhs == rhs);
}

/// @brief Compares two date objects. Two Date objects are not equal if the year, month or day are not equivalant.
/// @param lhs left hand side object.
/// @param rhs right hand side object.
/// @return  True if lhs is not chronologically equal to rhs date (i.e lhs is before or after rhs). False otherwise.
bool operator!=(const Date& lhs, const Date& rhs) noexcept {
    return !(lhs == rhs);
}

/// @brief Compares two date objecst and returns true if 
/// the first Date object is chronologically before the second date object.
/// Otherwise return false.
/// @param lhs left hand side object.
/// @param rhs right hand side object.
/// @return True if lhs is chronologically on or before rhs. False otherwise. 
bool operator<=(const Date& lhs, const Date& rhs) noexcept {
    return (lhs < rhs || lhs == rhs);
}

/// @brief Compares two date objecst and returns true if 
/// the first Date object is chronologically on or after the second date object.
/// Otherwise return false.
/// @param lhs left hand side object.
/// @param rhs right hand side object.
/// @return True if lhs date is chronologiclly on or after rhs date. False otherwise 
bool operator>=(const Date& lhs, const Date& rhs) noexcept {
    return (lhs > rhs || lhs == rhs);
}

// -----------------------------------------------------
//                  Helper Functions
// -----------------------------------------------------

// Checks whether or not the given year is a leap year.
bool Date::isLeapYear(const unsigned int year) noexcept {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Checks whether the given value is a valid month value. 
bool Date::isValidMonth(const unsigned int month) noexcept {
    return (month >= 1 && month <= 12);
}

// Checks whether the given value is a valid day value (regardless of month) 
bool Date::isValidDay(const unsigned int day) noexcept {
    return (day >= 1 && day <= 31);
}

// Checks whether the given year, month and day are a valid combination 
// (including number of days per month and leap years)
bool Date::isValidDate(const unsigned int year, 
                 const unsigned int month, 
                 const unsigned int day) noexcept {
    
    if (!isValidMonth(month) || !isValidDay(day)) return false; 

    if ((month == 9 || month == 4 || month == 6 || month == 11)
        && day > 30 ) return false; 

    if (month == 2) {
        if (isLeapYear(year)) {
            return (day < 30);
        } 
        return (day < 29);
    }

    return true; 
}

