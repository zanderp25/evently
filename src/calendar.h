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
// This will be helpful with the GUI, as we can use this to determine
// where the numbers should go.
class Month{
    public:
        Month(int month, int year);
        friend std::ostream& operator<<(std::ostream&, const Month&);
        bool operator==(const Month& m) const;
        bool operator!=(const Month& m) const;
        int getNumDays();
        int getMonth();
        int getYear();
        day getStartWkDay();
    private:
        int numDays;
        int month;
        int year;
        day startWkDay;
};

// The Calendar class provides a list of events.
// There are a few main methods that will be useful for the GUI:
// addEvent, editEvent, getEvent, removeEvent, getEvents
class Calendar{
    public:
        Calendar();
        friend std::ostream& operator<<(std::ostream&, Calendar&); // print list of events
        void addEvent(Event e);
        void editEvent(Event e);
        Event getEvent(int index);
        void removeEvent(int index);
        std::vector<Event> getEvents();
    private:
        std::vector<Event> events;
};

#endif