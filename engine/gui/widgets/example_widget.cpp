#include "example_widget.h"

void gui::ExampleWidget::render() {
    static float f = 0.0f;
    static int counter = 0;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    ImGui::ColorEdit3("clear color", (float *)&clear_color);

    if (ImGui::Button("Button")) {
        counter++;
    }

    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGuiIO &io = ImGui::GetIO();
    ImGui::Text(
        "Application average %.3f ms/frame (%.1f "
        "FPS)",
        1000.0f / io.Framerate, io.Framerate);
    GuiWidget::render();
}