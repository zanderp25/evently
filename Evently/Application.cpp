#include "Application.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <stdio.h>
#include <string>
#include "calendar.h"

namespace EventlyGUI {
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
        ResetDocking();
	}

    void RenderCalendarView() {
		ImGui::Begin("Calendar View");

        static int selectedMonth = 10;
        static int selectedYear = 2023;

        static Calendar calendar;
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
							EventlyGUI::CreateEventWindow(calendar);
						}
                        if (currentMonth.getDay(week, day) == Time::getCurrentDay() && currentMonth.getMonth() == Time::getCurrentMonth() && currentMonth.getYear() == Time::getCurrentYear()) {
							ImGui::PopStyleColor(3);
						}
                        ImGui::PopID();

                        ImGui::BeginChild(listLabel, ImVec2(ImGui::GetContentRegionAvail().x, 75), ImGuiChildFlags_None, ImGuiWindowFlags_None); // Scrollable region
                        // Create a loop that makes a button for each event on this day
                        // Make the label of the button the name of the event
                        // When the button is clicked, open a window that shows the details of the event
                        ImGui::EndChild();
                    }
                }
            }
            ImGui::EndTable();
        }

		ImGui::End();
	}

    // Creates a window that allows the user to create an event using the Calendar::addEvent method
    //! The window currently opens but immediately closes
    void CreateEventWindow(Calendar calendar) {
        static bool showCreateEventWindow = true;
        if (showCreateEventWindow) {
            ImGui::Begin("Create Event", &showCreateEventWindow, ImGuiWindowFlags_AlwaysAutoResize);

            const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September",
                                            "October", "November", "December" };

            static char eventName[50] = "Untitled Event";
            static char eventDescription[100] = "No description";
            static char eventLocation[50] = "Location";

		    static int selectedMonth = Time::getCurrentMonth() - 1;
		    static int selectedYear = Time::getCurrentYear();
		    static int selectedDay = Time::getCurrentDay();
		    static int selectedHour = Time::getCurrentHour();
		    static int selectedMinute = Time::getCurrentMinute();
		    static float selectedDuration = 1.0; // one hour
            static int selectedTimeZone = Time::getCurrentTimeZone();

            ImGui::Text("Event Name"); ImGui::SameLine();
            ImGui::InputText("##event name", eventName, IM_ARRAYSIZE(eventName));
            ImGui::Text("Event Description"); ImGui::SameLine();
            ImGui::InputText("##event description", eventDescription, IM_ARRAYSIZE(eventDescription));
            ImGui::Text("Event Location"); ImGui::SameLine();
            ImGui::InputText("##event location", eventLocation, IM_ARRAYSIZE(eventLocation));

            ImGui::Text("Event Date"); ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::Combo("##month", &selectedMonth, months, IM_ARRAYSIZE(months)); // ## hides the label
            ImGui::SameLine();
            if (ImGui::Button("-")) {
		    	selectedDay--;
		    }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(40);
            ImGui::InputInt("##day", &selectedDay, 0);
            ImGui::SameLine();
            if (ImGui::Button("+")) {
                selectedDay++;
            }
            ImGui::SameLine();
            if (ImGui::Button("-")) {
                selectedYear--;
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(40);
            ImGui::InputInt("##year", &selectedYear, 0);
            ImGui::SameLine();
            if (ImGui::Button("+")) {
		    	selectedYear++;
		    }
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

            if (ImGui::Button("Create")) {
		    	Event event(selectedYear, selectedMonth + 1, selectedDay, selectedHour, selectedMinute, selectedDuration, selectedTimeZone, eventName, eventLocation, eventDescription);
		    	calendar.addEvent(event);
		    	showCreateEventWindow = false;
		    }
		    ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
		    	showCreateEventWindow = false;
		    }

		    ImGui::End();
		}


	}

    void ResetDocking() {
        
    }
}
