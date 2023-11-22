#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <iostream>

class Event{
    public:
        Event(int year, int month, int day, int hour, int minute, float duration, int timeZone, std::string name, std::string location, std::string description);
        friend std::ostream& operator<<(std::ostream&, const Event&);
        std::string getEventDate() const;
        std::string getEventTime() const;
        std::string getEventTimeString() const;

        int getYear() const;
        void setYear(int);
        int getMonth() const;
        std::string getMonthString() const;
        void setMonth(int);
        int getDay() const;
        void setDay(int);
        int getHour() const;
        void setHour(int);
        int getMinute() const;
        void setMinute(int);
        float getDuration() const;
        std::string getDurationString() const;
        void setDuration(float);
        int getTimeZone() const;
        void setTimeZone(int);
        std::string getName() const;
        void setName(std::string);
        std::string getLocation() const;
        void setLocation(std::string);
        std::string getDescription() const;
        void setDescription(std::string);
        

    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
        float duration;

        // Time Zone is the difference from UTC
        // Eg: Eastern Standard Time is -500 (UTC-5) and Australian Central Standard Time is 930 (UTC+9:30)
        int timeZone;

        std::string name;
        std::string location;
        std::string description;
};

#endif