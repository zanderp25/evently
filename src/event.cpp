#include "event.h"

Event::Event(int year, int month, int day, int hour, int minute, std::string name, std::string location = "TBD", std::string description = "No description"){
  Event::setYear(year);
  Event::setMonth(month);
  Event::setDay(day);
  Event::setHour(hour);
  Event::setMinute(minute);
  Event::setName(name);
  Event::setLocation(location);
  Event::setDescription(description);
}

std::ostream& operator<<(std::ostream &os, const Event &event){
    os << "[Event \"" << event.getName() << "\" on " << event.getYear() << "-" << event.getMonth() << "-" << event.getDay() 
    << " at " << event.getHour() << ":" << event.getMinute() << "]" << std::endl;

    return os;
}

std::string Event::getEventDate() const {
    return Event::getMonthString() + " " + std::to_string(Event::getDay()) + ", " + std::to_string(Event::getYear());
}

std::string Event::getEventTime() const {
  return std::to_string(Event::getHour()) + ":" + std::to_string(Event::getMinute());
}

int Event::getYear() const {
  return Event::year;
}

void Event::setYear(int year){
  Event::year = year;
}

int Event::getMonth() const {
  return Event::month;
}

std::string Event::getMonthString() const{
  switch(Event::getMonth()){
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

void Event::setMonth(int month){
  Event::month = month;
}

int Event::getDay() const {
  return Event::day;
}

void Event::setDay(int day){
  Event::day = day;
}

int Event::getHour() const {
  return Event::hour;
}

void Event::setHour(int hour){
  Event::hour = hour;
}

int Event::getMinute() const {
  return Event::minute;
}

void Event::setMinute(int minute){
  Event::minute = minute;
}

std::string Event::getName() const {
  return Event::name;
}

void Event::setName(std::string name){
  Event::name = name;
}

std::string Event::getLocation() const {
  return Event::location;
}

void Event::setLocation(std::string location){
  Event::location = location;
}

std::string Event::getDescription() const {
  return Event::description;
}

void Event::setDescription(std::string description){
  Event::description = description;
}
