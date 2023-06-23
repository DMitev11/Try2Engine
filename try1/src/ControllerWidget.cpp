#pragma once
#include "../inc/ControllerWidget.h"
void ControllerWidget::render() {
    static float f = 0.0f;
    static int counter = 0;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 1. Create a text line to give some description
    ImGui::Text("Cubes or whatever");
    ImGui::Text("Use arrow keys or wasd");
    ImGui::SliderFloat("Gravity", &this->gameData->gravity,
                       -100, 100.f);
    ImGui::SliderInt("Quantity", &this->gameData->quantity,
                     0, 500);

    ImGui::SliderFloat("Force in NM",
                       &this->gameData->force, 0,
                       100000000000);
    ImGui::RadioButton("On: Force; Off:Impulse",
                       &this->gameData->forceOrImpulse);
    ImGui::RadioButton("Treat as bullet?",
                       &this->gameData->treatAsBullet);
    ImGui::SliderFloat("X direction", &this->gameData->xDir,
                       -1, 1);
    ImGui::SliderFloat("Y direction", &this->gameData->yDir,
                       -1, 1);
    if (ImGui::Button("FIRE!")) {
        LOG_ENGINE_INFO("Try1Burn: ", "FIRE THE CHAOS");
        this->eventEmitter.Emit(
            ControllerWidget::Events::kFire, 0);
    }
    ImGui::Text(
        "You have to press 'Set' for all old boxes");
    ImGui::SliderFloat("Density",
                       &this->gameData->densityCoefficient,
                       0.00001f, 1000);
    ImGui::SliderFloat("Friction",
                       &this->gameData->frictionCoefficient,
                       0.001f, 1.f);
    ImGui::SliderFloat("GravityScale",
                       &this->gameData->gravityScale,
                       0.001f, 1.f);
    ImGui::SliderFloat(
        "Restitution Threshold",
        &this->gameData->restitutionThreshold, 0.001f, 1.f);
    if (ImGui::Button("Set Values for all boxes")) {
        LOG_ENGINE_INFO("Try1Burn: ", "FIRE THE CHAOS");
        this->eventEmitter.Emit(
            ControllerWidget::Events::kFire, 0);
    }

    ImGuiIO &io = ImGui::GetIO();
    ImGui::Text(
        "Application average %.3f ms/frame (%.1f "
        "FPS)",
        1000.0f / io.Framerate, io.Framerate);

    // 4. Render a frame
    GuiWidget::render();
}