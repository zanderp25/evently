#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include "event.h"

enum month{
    January = 1,    // 31
    February,       // 28/29 <- leap
    March,          // 31
    April,          // 30
    May,            // 31
    June,           // 30
    July,           // 31
    August,         // 31
    September,      // 30
    October,        // 31
    November,       // 30
    December        // 31
};

enum day
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

// The Month class provides the first day and length of the month.
// There is also a GetDay method that returns the number of day in the month based on the row and column.
class Month{
    public:
        Month(int month, int year);
        friend std::ostream& operator<<(std::ostream&, const Month&);
        bool operator==(const Month& m) const;
        bool operator!=(const Month& m) const;
        int getNumDays() const;
        int getMonth() const;
        std::string getMonthString() const;
        int getYear() const;
        day getStartWkDay() const;
        int getDay(int week, int dayOfWeek) const;
    private:
        int numDays;
        int month;
        int year;
        day startWkDay;
        std::array<std::array<int, 7>, 6> days;
};

namespace Time{
    std::string getCurrentTime();
    std::string getCurrentDate();
    int getCurrentYear();
    int getCurrentMonth();
    int getCurrentDay();
    int getCurrentHour();
    int getCurrentMinute();
    int getCurrentSecond();
    int getCurrentWeekday();
    int getCurrentTimeZone();
    std::string getCurrentTimeZoneString();
}

// The Calendar class provides a list of events.
// There are a few main methods that will be useful for the GUI:
// addEvent, editEvent, getEvent, removeEvent, getEvents
class Calendar{
    public:
        Calendar();
        void addEvent(Event e);
        void editEvent(Event a);
        Event getEvent(int index);
        void removeEvent(Event e);
        std::vector<Event> getEvents();
        std::vector<Event> getEvents(int year, int month, int day);
    private:
        std::vector<Event> events;
        int IndexID = 0;
};

#endif