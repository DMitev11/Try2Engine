#include <gui/core/gui_layer.h>
#include <input/input.hpp>
#include <render/render.hpp>
#include <utils/entry.h>
#include <window/window.hpp>

class ExampleWidget : public gui::GuiWidget {
  public:
    // override constructor on demand
    ExampleWidget(const char *name,
                  std::vector<int> flags = {})
        : GuiWidget(name, flags) {}
    // override destructor on demand
    ~ExampleWidget() override{};
    // Override only this method
    void render() override;
};

void ExampleWidget::render() {
    static float f = 0.0f;
    static int counter = 0;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 1. Create a text line to give some description
    ImGui::Text("This is some useful text.");

    // 2. Add an interactive alement and bind its returned
    // value to a variable
    //  The example uses static variables, but member
    //  variables are highly advised
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    // 3. Read about the different types of elements in
    // <imgui/imgui_widgets.cpp>
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

    // 4. Render a frame
    GuiWidget::render();
}

class ExampleEntry : public utils::Entry {
  public:
    ExampleEntry(){};
    ~ExampleEntry() override {}
    void run() override {
        // 0. Create windowing and renderer
        window::init();
        render::init();
        auto window =
            window::createWindow(1000, 1200, "GUI Example");
        auto renderer = render::createRenderer(window);
        // 1. Initialize an input system to interact with
        // the UI
        auto inputSystem = input::createInputSystem();
        inputSystem->init();

        // 2. Create and add a Layer
        auto gui = static_cast<gui::GuiLayer *>(
            this->layerStack.addLayer(
                new gui::GuiLayer("GuiLayer", renderer)));
        // 3. Add widgets to it - see above
        gui->addWidget(new ExampleWidget("example widget"));
        gui->addWidget(
            new ExampleWidget("example widget3"));
        gui->addWidget(
            new ExampleWidget("example widget4"));
        gui->addWidget(
            new ExampleWidget("example widget2"));

        bool exit = false;
        inputSystem->getEmitter()->On(
            input::kEventQuit,
            std::function(
                [&](int i, input::InputSystem *input) {
                    exit = true;
                }));
        while (!exit) {
            render::clearRenderer(renderer);
            // 4. Poll input system to detect UI input
            inputSystem->poll();
            render::setDrawColor(renderer, 255, 0, 0, 255);
            // 5. Update layer stack and let buffer for
            // rendering
            this->layerStack.tick(0.005f);
            // 6. Render a frame
            render::renderFrame(renderer);
        }
    }
};

int main(int argc, char const *argv[]) {
    // 1. Create an entry point
    auto entry = new ExampleEntry();
    // 2. Run it
    entry->run();
    delete entry;
    return 0;
}