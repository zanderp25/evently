#include <iomanip>
#include <cmath>
#include <algorithm>
#include "event.h"

Event::Event(int year, int month, int day, int hour, int minute, float duration, int timeZone, std::string name, std::string location = "TBD", std::string description = "No description"){
  Event::setYear(year);
  Event::setMonth(month);
  Event::setDay(day);
  Event::setHour(hour);
  Event::setMinute(minute);
  Event::setDuration(duration);
  Event::setTimeZone(timeZone);
  Event::setName(name);
  Event::setLocation(location);
  Event::setDescription(description);
}

std::ostream& operator<<(std::ostream &os, const Event &event){
    os << "[Event \"" << event.getName() << "\" on " << event.getYear() << "-" << event.getMonth() << "-" << event.getDay() 
      << " at " << event.getHour() << ":" << event.getMinute() << " " << ((event.getTimeZone() < 0)? "UTC": "UTC+") 
      << floor(event.getTimeZone()/100) << ":" << std::setfill('0') << std::setw(2) << event.getTimeZone() % 100
      << " for " << event.getDurationString() << " at " << event.getLocation() << " with description \"" << event.getDescription() << "\"]";
    return os;
}

std::string Event::getEventDate() const {
    return Event::getMonthString() + " " + std::to_string(Event::getDay()) + ", " + std::to_string(Event::getYear());
}

// Gets the event start time in 24-hour format
std::string Event::getEventTime() const {
  std::string minute = std::to_string(Event::getMinute()); 
  return std::to_string(Event::getHour()) + ":" + std::string(2 - std::min(2, (int)minute.length()), '0').append(minute);
}

// Gets the event start time and duration in 24-hour format
std::string Event::getEventTimeString() const {
  std::string minute = std::to_string(Event::getMinute()); 
  return std::to_string(Event::getHour()) + ":" + std::string(2 - std::min(2, (int)minute.length()), '0').append(minute) + " for " + Event::getDurationString();
}

std::string Event::getTimeZoneString() const{
  return ((Event::getTimeZone() < 0)? "UTC": "UTC+") + std::to_string(static_cast<int>(Event::getTimeZone()/100)) + ":" +
      std::string(2 - std::min(2, (int)std::to_string(Event::getTimeZone() % 100).length()), '0').append(std::to_string(Event::getTimeZone() % 100));
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

float Event::getDuration() const {
  return Event::duration;
}

std::string Event::getDurationString() const {
  unsigned int hour = Event::getDuration();
  unsigned int minute = (Event::getDuration() - (int)Event::getDuration()) * 60;
  return std::to_string(hour) + " hours and " + std::to_string(minute) + " minutes";
}

void Event::setDuration(float duration) {
  Event::duration = duration;
}

int Event::getTimeZone() const {
  return Event::timeZone;
}

void Event::setTimeZone(int timeZone){
  Event::timeZone = timeZone;
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

unsigned int Event::getID() const {
  return Event::id;
}

void Event::setID(unsigned int id) {
  Event::id = id;
}