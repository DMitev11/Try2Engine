#include "gui_layer.h"
#include <algorithm>
#include <libraries/imgui/backends/imgui_impl_sdl3.h>
#include <libraries/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libraries/imgui/imgui.h>
#include <objects/helpers_object.hpp>

/**
 * @brief SDL-based implementation, where "ImGui" requires
 * binding to a specific window and knowing which render to
 * use for displaying all buffered widget data (per frame)
 *
 */
void gui::GuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::SetCurrentContext(ImGui::CreateContext());
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Enable navigating with keyboard
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // Enable navigating with gamepad/controller
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    auto sdlRenderer =
        objects::toSdlRenderer(this->kRenderer);
    auto sdlWindow = objects::toSdlWindow(this->kRenderer);

    // Personal preference
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(sdlWindow,
                                      sdlRenderer);
    ImGui_ImplSDLRenderer3_Init(sdlRenderer);
}

void gui::GuiLayer::onTick(float delta) {
    this->begin();
    this->render();
    this->end();
}

void gui::GuiLayer::begin() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void gui::GuiLayer::render() {
    for (GuiWidget *widget : this->widgets) {
        widget->begin();
        widget->render();
        widget->end();
    }
}

gui::GuiWidget *
gui::GuiLayer::addWidget(gui::GuiWidget *widget) {
    this->widgets.push_back(widget);
    return this->widgets[this->widgets.size() - 1];
}
//@todo replace with id
void gui::GuiLayer::removeWidget(const char *name) {

    this->widgets.erase(std::remove_if(
        this->widgets.begin(), this->widgets.end(),
        [=](gui::GuiWidget *widget) {
            return name == widget->getName();
        }));
}
void gui::GuiLayer::end() {
    // Buffer render data
    ImGui::Render();
    // Send that buffer data to this->renderer
    ImGui_ImplSDLRenderer3_RenderDrawData(
        ImGui::GetDrawData());
}

void gui::GuiLayer::onDetach() {
    // Remove "ImGui" from the SDL renderer
    ImGui_ImplSDLRenderer3_Shutdown();
    // Remove "ImGui" from the SDL window
    ImGui_ImplSDL3_Shutdown();
    // Cleanup
    ImGui::DestroyContext();
}
