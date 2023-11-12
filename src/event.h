#include <string>
#include <iostream>

class Event{
    public:
        Event(int year, int month, int day, std::string& name);
        friend std::ostream& operator<<(std::ostream&, const Event&);
        std::string getEventDate();
        std::string getEventTime();

        int getYear();
        void setYear(int year);
        int getMonth();
        void setMonth(int month);
        int getDay();
        void setDay(int day);
        int getHour();
        void setHour(int hour);
        int getMinute();
        void setMinute(int minute);
        std::string getName();
        void setName(std::string name);
        std::string getLocation();
        void setLocation(std::string location);
        std::string getDescription();
        void setDescription(std::string description);
    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
        std::string name;
        std::string location;
        std::string description;
};