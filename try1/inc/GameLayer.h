#pragma once
#include <box2d/box2d.h>
#include <inc/GameData.h>
#include <input/input.hpp>
#include <objects/renderer_object.h>
#include <objects/texture_object.h>
#include <random>
#include <utils/event_emitter.hpp>
#include <utils/layer.h>
namespace try1 {

    struct Controls {
        std::map<int, bool> keyboardKeys;
        // std::map<int, bool> controllerAxis;
    };

    //@todo will change to ECS/EC
    struct Entity {
      public:
        Entity(objects::Renderer *renderer,
               objects::Texture *sprite, b2Vec2 position,
               b2Body *body)
            : renderer(renderer), sprite(sprite),
              position(position), body(body){};
        ~Entity(){};
        void tick(float delta);
        void render();

        b2Body *const getBody() const { return body; }

      protected:
        objects::Renderer *renderer;
        objects::Texture *sprite;
        b2Vec2 position;
        b2Body *body;
    };

    class GameLayer : public utils::Layer {
      public:
        GameLayer(const char *name,
                  objects::Renderer *renderer,
                  input::InputSystem *inputSystem,
                  GameData *gameData, int screenWidth)
            : utils::Layer(name), renderer(renderer),
              inputSystem(inputSystem), gameData(gameData),
              screenWidth(screenWidth) {

            std::random_device rd;
            this->rnd = std::mt19937(rd());
        };
        ~GameLayer() override{};

        void onAttach() override;
        void onDetach() override;
        void onTick(float delta) override;

        utils::EventEmitter *const getEmitter() {
            return &this->eventEmitter;
        };

        void fire();
        void fire(float x, float y);
        void setGlobals();

      protected:
        Entity *spawnNewBox(int x, int y);
        void changeEntityAmount(int quantity);
        void handleKeyboardInput();

        objects::Renderer *renderer;
        utils::EventEmitter eventEmitter;
        input::InputSystem *inputSystem;

        std::mt19937 rnd;
        int screenWidth;
        GameData *gameData;
        Controls controls;
        float lastDelta;

        std::vector<Entity *> entities;
        b2World *world;
        Entity *platformOne;
        Entity *platformTwo;
    };
} // namespace try1