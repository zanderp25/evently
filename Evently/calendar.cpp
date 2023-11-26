#include "calendar.h"
#include <vector>

Calendar::Calendar() {
    std::vector<Event> events;
}

int getIndexForID(std::vector<Event> events, unsigned int id) {
	for (int i = 0; i < events.size(); i++) {
		if (events[i].getID() == id) {
			return i;
		}
	}
	return -1;
}

std::vector<Event> Calendar::getEvents() {
	return events;
}

std::vector<Event> Calendar::getEvents(int year, int month, int day) {
    std::vector<Event> eventsOnDay;
    for (int i = 0; i < events.size(); i++) {
        if (events[i].getYear() == year && events[i].getMonth() == month && events[i].getDay() == day) {
			eventsOnDay.push_back(events[i]);
		}
	}
	return eventsOnDay;
}

void Calendar::addEvent(Event e) {
	e.setID(events.size());
	events.push_back(e);
}

void Calendar::editEvent(Event e){
    unsigned int index = getIndexForID(events, e.getID());
	events[index] = e;
}

void Calendar::removeEvent(Event e){
    unsigned int index = getIndexForID(events, e.getID());
    events.erase(events.begin() + index);
}

Event Calendar::getEvent(int id) {
	return events[getIndexForID(events, id)];
}