#include "Application.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <stdio.h>
#include <string>
#include "calendar.h"

namespace EventlyGUI {
    static bool showCreateEventWindow = false;
    static Calendar calendar;
    static int selectedDate[3] = {2023, 1, 1};
    static int selectedEventID = -1;

    void RenderUI() {
        // Call the main render functions
        RenderMainView();

        // Hello World window that can be closed
        static bool show_hello_world = false;
        if (show_hello_world) {
            ImGui::Begin("Hello, world!", &show_hello_world);
            ImGui::Text("This is some useful text.");
            ImGui::Text("I love GUIs.");
            ImGui::End();
        }

        // show demo window
        static bool show_demo_window = true;
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
    }

    void RenderMainView() {
		// main calendar view
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        RenderCalendarView();
        CreateEventWindow();
        ResetDocking();
	}

    void RenderCalendarView() {
		ImGui::Begin("Calendar View");

        static int selectedMonth = 10;
        static int selectedYear = 2023;

        Month currentMonth(selectedMonth + 1 , selectedYear);

        const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September",
        								"October", "November", "December" };


        // Header for the calendar
        if (ImGui::Button("<")) {
            if (selectedMonth == 0) {
				selectedMonth = 11;
				selectedYear--;
			}
            else {
				selectedMonth--;
			}
		}
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::Combo("##month", &selectedMonth, months, IM_ARRAYSIZE(months)); // ## hides the label
        ImGui::SameLine();
        if (ImGui::Button("-")) {
            selectedYear--;
        }
        ImGui::SameLine();
        //ImGui::Text("%d", selectedYear);
        ImGui::SetNextItemWidth(40);
        ImGui::InputInt("##year", &selectedYear, 0);
        ImGui::SameLine();
        if (ImGui::Button("+")) {
			selectedYear++;
		}
        ImGui::SameLine();
		if (ImGui::Button(">")) {
            if (selectedMonth == 11) {
				selectedMonth = 0;
				selectedYear++; 
			}
            else {
				selectedMonth++;
			}
		} 
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Text("%s %s %d", Time::getCurrentDate().c_str(), Time::getCurrentTime().c_str(), Time::getCurrentTimeZone());

    
        if (ImGui::BeginTable("table1", 7, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_BordersOuterV, { 0, 0 }))
        {
            ImGui::TableSetupColumn("Sunday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Monday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Tuesday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Wednesday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Thursday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Friday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Saturday", ImGuiTableColumnFlags_None, 0);
            ImGui::TableHeadersRow();

            for (size_t week = 0; week < 6; ++week)
            {
                ImGui::TableNextRow();
                for (size_t day = 0; day < 7; ++day) {
                    char buttonLabel[3];
                    char listLabel[10];
                    sprintf(buttonLabel, "%d", currentMonth.getDay(week, day));
                    sprintf(listLabel, "Events %d", currentMonth.getDay(week, day));
                    ImGui::TableSetColumnIndex(day);
                    if (currentMonth.getDay(week, day) != 0) {
                        ImGui::PushID((int)(week * day));
                        if (currentMonth.getDay(week, day) == Time::getCurrentDay() && currentMonth.getMonth() == Time::getCurrentMonth() && currentMonth.getYear() == Time::getCurrentYear()) {
                            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.6f, 0.5f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.6f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.7f));
                        }
                        if (ImGui::Button(buttonLabel)) {
							showCreateEventWindow = true;
                            selectedDate[0] = currentMonth.getYear();
                            selectedDate[1] = currentMonth.getMonth();
                            selectedDate[2] = currentMonth.getDay(week, day);
						}
                        if (currentMonth.getDay(week, day) == Time::getCurrentDay() && currentMonth.getMonth() == Time::getCurrentMonth() && currentMonth.getYear() == Time::getCurrentYear()) {
							ImGui::PopStyleColor(3);
						}
                        ImGui::PopID();

                        ImGui::BeginChild(listLabel, ImVec2(ImGui::GetContentRegionAvail().x, 75), ImGuiChildFlags_None, ImGuiWindowFlags_None); // Scrollable region
                        // Create a loop that makes a button for each event on this day
                        // Make the label of the button the name of the event
                        // When the button is clicked, open a window that shows the details of the event
                        std::vector<Event> events = calendar.getEvents(currentMonth.getYear(), currentMonth.getMonth(), currentMonth.getDay(week, day));
                        for (int i = 0; i < events.size(); i++) {
							ImGui::PushID(i);
                            char eventLabel[50];
                            sprintf(eventLabel, "%s##%d", events[i].getName().c_str(), events[i].getID());
                            if (ImGui::Button(eventLabel)) {
                                // show a window with the event details
							}
							ImGui::PopID();
						}
                        ImGui::EndChild();
                    }
                }
            }
            ImGui::EndTable();
        }

		ImGui::End();
	}

    // Creates a window that allows the user to create an event using the Calendar::addEvent method
    void CreateEventWindow() {
        if (showCreateEventWindow) {
            ImGui::Begin("Create Event", &showCreateEventWindow, ImGuiWindowFlags_AlwaysAutoResize);

            const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September",
                                            "October", "November", "December" };

            static bool reset = true;

            static char eventName[50];
            static char eventDescription[100];
            static char eventLocation[50];

		    static int selectedYear;
		    static int selectedMonth;
		    static int selectedDay;
		    static int selectedHour;
            static int selectedMinute;
            static float selectedDuration;
            static int selectedTimeZone;

            if (reset) {
                strcpy(eventName, "Untitled Event");
                strcpy(eventDescription, "No description");
                strcpy(eventLocation, "Location");

                selectedYear = selectedDate[0];
				selectedMonth = selectedDate[1] - 1;
				selectedDay = selectedDate[2];
				selectedHour = Time::getCurrentHour();
				selectedMinute = Time::getCurrentMinute();
				selectedDuration = 1.0; // one hour
				selectedTimeZone = Time::getCurrentTimeZone();

				reset = false;
            }

            Month currentMonth(selectedMonth + 1 , selectedYear);

            ImGui::Text("Event Name        "); ImGui::SameLine();
            ImGui::InputText("##event name", eventName, IM_ARRAYSIZE(eventName));
            ImGui::Text("Event Description "); ImGui::SameLine();
            ImGui::InputText("##event description", eventDescription, IM_ARRAYSIZE(eventDescription));
            ImGui::Text("Event Location    "); ImGui::SameLine();
            ImGui::InputText("##event location", eventLocation, IM_ARRAYSIZE(eventLocation));

            ImGui::Text("Event Date"); ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::Combo("##month", &selectedMonth, months, IM_ARRAYSIZE(months)); // ## hides the label
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80);
            ImGui::InputInt("##day", &selectedDay);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(90);
            ImGui::InputInt("##year", &selectedYear);

            ImGui::Text("Event Time"); ImGui::SameLine();
		    ImGui::SetNextItemWidth(40);
		    ImGui::InputInt("##hour", &selectedHour, 0);
		    ImGui::SameLine();
		    ImGui::Text(":"); ImGui::SameLine();
		    ImGui::SetNextItemWidth(40);
		    ImGui::InputInt("##minute", &selectedMinute, 0);
		    ImGui::SameLine();
		    ImGui::Text("Duration"); ImGui::SameLine();
		    ImGui::SetNextItemWidth(40);
		    ImGui::InputFloat("##duration", &selectedDuration, 0.0f, 0.0f, "%.1f");
		    ImGui::SameLine();
		    ImGui::Text("hours");

		    ImGui::Text("Time Zone"); ImGui::SameLine();
		    ImGui::SetNextItemWidth(40);
		    ImGui::InputInt("##time zone", &selectedTimeZone, 0);

            if (selectedDay < 1) {
                selectedMonth--;
                currentMonth = Month((selectedMonth + 1 == 0) ? 12 : selectedMonth + 1, selectedYear);
                selectedDay = currentMonth.getNumDays();
            }
            else if (selectedDay > currentMonth.getNumDays()) {
				selectedMonth++;
				currentMonth = Month((selectedMonth + 1 == 13)? 1: selectedMonth + 1, selectedYear);
				selectedDay = 1;
			}

            if (selectedMonth < 0) {
				selectedYear--;
				selectedMonth = 11;
            } else if (selectedMonth > 11) {
                selectedYear++;
                selectedMonth = 0;
            }

            if (ImGui::Button("Create")) {
		    	Event event(selectedYear, selectedMonth + 1, selectedDay, selectedHour, selectedMinute, selectedDuration, selectedTimeZone, eventName, eventLocation, eventDescription);
		    	calendar.addEvent(event);
		    	showCreateEventWindow = false;
                reset = true;
		    }
		    ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
		    	showCreateEventWindow = false;
                reset = true;
		    }

		    ImGui::End();
		}


	}

    void ResetDocking() {
        
    }
}
