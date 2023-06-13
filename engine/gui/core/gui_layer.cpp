#include "gui_layer.h"
#include <libraries/imgui/backends/imgui_impl_sdl3.h>
#include <libraries/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libraries/imgui/imgui.h>
#include <objects/sdl_renderer_object.h>
void gui::GuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::SetCurrentContext(ImGui::CreateContext());
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable
                                            // Keyboard
                                            // Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad
                                           // Controls

    auto renderer =
        static_cast<objects::SDLRenderer *>(this->renderer);
    auto sdlRenderer = (SDL_Renderer *)*renderer;
    auto sdlWindow = (SDL_Window *)*renderer;
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
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(
        ImGui::GetDrawData());
}

void gui::GuiLayer::onDetach() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
