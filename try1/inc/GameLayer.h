#pragma once
#include <box2d/box2d.h>
#include <input/input.hpp>
#include <objects/renderer_object.h>
#include <objects/texture_object.h>
#include <utils/event_emitter.hpp>
#include <utils/layer.h>
namespace try1 {

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
                  input::InputSystem *inputSystem)
            : utils::Layer(name), renderer(renderer),
              inputSystem(inputSystem){};
        ~GameLayer() override{};

        void onAttach() override;
        void onDetach() override;
        void onTick(float delta) override;

        utils::EventEmitter *const getEmitter() {
            return &this->eventEmitter;
        };

      protected:
        objects::Renderer *renderer;
        utils::EventEmitter eventEmitter;
        input::InputSystem *inputSystem;
        Entity *box;
        b2World *world;
        Entity *platformOne;
        Entity *platformTwo;
    };
} // namespace try1