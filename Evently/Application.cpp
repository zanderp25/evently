#include "Application.h"
#include "imgui.h"
#include <stdio.h>
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
		ImGui::Text("This is the calendar view.");

        static int selectedMonth = 10;
        static int selectedYear = 2023;

        Month currentMonth(selectedMonth + 1 , selectedYear);

        const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September",
        								"October", "November", "December" };

        /*char* years[1000];

        for (int i = 1900; i < 2900; i++){
            char year[5];
            sprintf(year, "%d", i);
            years[i] = year;
        }*/

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
        ImGui::Text("%s %d", currentMonth.getMonthString().c_str(), currentMonth.getYear());
        ImGui::SameLine();
        ImGui::Combo(" ", &selectedMonth, months, IM_ARRAYSIZE(months));
        ImGui::SameLine();
        ImGui::Combo(" ", &selectedMonth, years, IM_ARRAYSIZE(years));
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
                    sprintf(buttonLabel, "%d", currentMonth.getDay(week, day));
                    ImGui::TableSetColumnIndex(day);
                    if (currentMonth.getDay(week, day) != 0) {
                        ImGui::PushID((int)(week * day));
                        ImGui::Button(buttonLabel);
                        ImGui::PopID();
                    }
                }
            }
            ImGui::EndTable();
        }
        /*if (ImGui::IsItemClicked())
            ClickedOnDay();*/
		ImGui::End();
	}

    void ResetDocking() {
        
    }
}
