#include "Application.h"
#include "imgui.h"

namespace EventlyGUI {
    void RenderUI() {
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");
        ImGui::Text("I love GUIs.");                // Display some text (you can use a format strings too)
        ImGui::End();
    }
}
