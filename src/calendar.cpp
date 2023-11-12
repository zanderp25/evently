#include <iostream>
#include <iomanip>
#include <ctime>
#include "calendar.h"

Month::Month(int month, int year): month(month), year(year){
    switch(month){
        case January:
        case March:
        case May:
        case July:
        case August:
        case October:
        case December:
            numDays = 31;
            break;
        case April:
        case June:
        case September:
        case November:
            numDays = 30;
            break;
        case February:
            /*
                * Determine if the year is a leap year
                * From https://www.timeanddate.com/date/leapyear.html:

                In our modern-day Gregorian calendar, three criteria must be taken into account to identify leap years:

                - The year must be evenly divisible by 4;
                - If the year can also be evenly divided by 100, it is not a leap year;
                    unless...
                - The year is also evenly divisible by 400. Then it is a leap year.
                    According to these rules, the years 2000 and 2400 are leap years,
                    while 1800, 1900, 2100, 2200, 2300, and 2500 are not leap years.
            */

            if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
                numDays = 29;
            } else {
                numDays = 28;
            }
            break;
        default:
            throw std::invalid_argument("Invalid month");
    }

    /*
        * Determine the day of week the month starts on
        * From https://stackoverflow.com/a/40517482:

        Use std::localtime and std::mktime to convert a std::tm to a std::time_t.
        Then use std::localtime and std::gmtime to convert a std::time_t to a std::tm.
    */

    std::tm monthStart = {0, 0, 0, 1, month - 1, year - 1900}; // sec, min, hour, 1-indexed day, 0-indexed month, year since 1900
    std::time_t monthStart_t = std::mktime(&monthStart);
    const std::tm* monthStart_tm = std::localtime(&monthStart_t);
    startWkDay = static_cast<day>(monthStart_tm->tm_wday);
}

// Print the month.
std::ostream& operator<<(std::ostream& os, const Month& m){
    os << "Su Mo Tu We Th Fr Sa" << std::endl;
    for(int i = 0; i < m.startWkDay; i++){
        os << "   ";
    }
    for(int i = 1; i <= m.numDays; i++){
        os << std::setw(2) << i << " ";
        if((i + m.startWkDay) % 7 == 0){
            os << std::endl;
        }
    }
    os << std::endl;
    return os;
}

bool Month::operator==(const Month& m) const{
    return (month == m.month && year == m.year);
}

bool Month::operator!=(const Month& m) const{
    return !(*this == m);
}