#pragma once
#include "../inc/GameData.h"
#include <gui/core/gui_widget.h>
#include <utils/event_emitter.hpp>
class ControllerWidget : public gui::GuiWidget {
  public:
    enum Events { kFire };

    ControllerWidget(GameData *gameData, const char *name,
                     std::vector<int> flags = {})
        : GuiWidget(name, flags), gameData(gameData) {}
    ~ControllerWidget() override{};

    void render() override;

    utils::EventEmitter *const getEmitter() {
        return &this->eventEmitter;
    }

  protected:
    GameData *gameData;
    utils::EventEmitter eventEmitter;
};