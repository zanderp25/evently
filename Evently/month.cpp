#include <ctime>
#include "calendar.h"

Month::Month(int month, int year) : month(month), year(year) {
    switch (month) {
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

        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            numDays = 29;
        }
        else {
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

        # I changed the previous solution to this because any year less than 1970 would break everything lol
        # The previous solution was more accurate, but the new solution is more reliable
        # Formula source: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Disparate_variation
    */

    if (year > 1970) {
        std::tm timeinfo = { 0 };
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = 1;
        std::time_t time = std::mktime(&timeinfo);
        std::tm* timeinfo2 = std::localtime(&time);
        startWkDay = static_cast<day>(timeinfo2->tm_wday);
    }
    else {
        int mon = (month + 10) % 12;
        int yr = year - mon / 10;
        int cent = yr / 100;
        startWkDay = static_cast<day>((1 + static_cast<int>(2.6 * mon - 0.2) + (yr % 100) + (yr % 100 / 4) + (cent / 4) - (2 * cent)) % 7);
    }

    if (startWkDay < 0) startWkDay = static_cast<day>(7 + startWkDay); // fixes that weird bug where the day of the week is negative

    int swd = 1 - Month::getStartWkDay();
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if ((Month::numDays < swd) || (0 > swd)) {
                Month::days[i][j] = 0;
            }
            else {
                Month::days[i][j] = swd;
            }
            swd++;
        }

    }
}

// Print the month.
std::ostream& operator<<(std::ostream& os, const Month& m) {
    os << "Su Mo Tu We Th Fr Sa" << std::endl;
    for (int i = 0; i < m.startWkDay; i++) {
        os << "   ";
    }
    for (int i = 1; i <= m.numDays; i++) {
        os << std::setw(2) << i << " ";
        if ((i + m.startWkDay) % 7 == 0) {
            os << std::endl;
        }
    }
    os << std::endl;
    return os;
}

bool Month::operator==(const Month& m) const {
    return (month == m.month && year == m.year);
}

bool Month::operator!=(const Month& m) const {
    return !(*this == m);
}

int Month::getNumDays() const {
    return numDays;
}

int Month::getMonth() const {
    return month;
}

std::string Month::getMonthString() const {
    switch (Month::getMonth()) {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    default:
        return "December";
    }
}

int Month::getYear() const {
    return year;
}

day Month::getStartWkDay() const {
    return startWkDay;
}

int Month::getDay(int week, int dayOfWeek) const {
    return days[week][dayOfWeek];
}