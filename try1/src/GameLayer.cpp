#include <inc/GameLayer.h>
#include <loader/loader.hpp>
#include <logger/logger.h>
#include <render/render.hpp>
using namespace try1;

void Entity::tick(float delta) {
    this->position = this->body->GetPosition();
}
void Entity::render() {
    auto textureSize = render::getTextureSize(this->sprite);
    auto posX = this->position.x - textureSize.w / 2;
    auto posY = this->position.y - textureSize.h / 2;
    render::renderAsset(this->renderer, this->sprite, posX,
                        posY);
}
void hookGamepadAndKeyboardInfoLog(
    input::InputSystem *input) {
    // Handle gamepad connected via binding gamepad input
    std::function<void(uint8_t id)>
        handleControllerConnect = [input](uint8_t id) {
            LOG_CLIENT_INFO("Try1: Hook Gamepad",
                            std::to_string(id).c_str());
            std::function<void(uint8_t i)> emitMessage =
                std::function<void(uint8_t i)>(
                    [](uint8_t i) {
                        LOG_CLIENT_INFO(
                            "Try1: Gamepad Button Down ",
                            std::to_string(i).c_str());
                    });
            input->getController(id)->eventEmitter.On(
                input::kEventGamepadDown, emitMessage);
        };

    // Hook gamepad created
    input->getEmitter()->On(input::kEventGamepadCreated,
                            handleControllerConnect);
    input->getEmitter()->On(
        input::kEventKeyboardDown,
        std::function<void(uint8_t)>([input](uint8_t id) {
            LOG_CLIENT_INFO("Button: ",
                            std::to_string(id).c_str());
        }));
}

void GameLayer::onAttach() {
    auto config = loader::LoadingTextureConfig();
    config.colorKey.r = 0, config.colorKey.g = 0,
    config.colorKey.b = 0;

    auto platformTexture = loader::loadTexture(
        this->renderer, "assets/platform.png", config);
    auto input = this->inputSystem;
    hookGamepadAndKeyboardInfoLog(input);

    b2Vec2 gravity(0.0f, 9.8f); // Set gravity
    this->world = new b2World(gravity);
    auto platformTextureSize =
        render::getTextureSize(platformTexture);

    // Define ground body
    b2BodyDef platformOneDef;
    platformOneDef.position.Set(100.f, 800.0f);
    b2Body *platformOneBody =
        this->world->CreateBody(&platformOneDef);
    b2PolygonShape platformOneShape;
    platformOneShape.SetAsBox(platformTextureSize.w / 2,
                              platformTextureSize.h / 2);
    platformOneBody->CreateFixture(&platformOneShape, 0.0f);
    this->platformOne = new Entity(
        this->renderer, platformTexture,
        platformOneBody->GetPosition(), platformOneBody);

    b2BodyDef platformTwoDef;
    platformTwoDef.position.Set(
        platformOneBody->GetPosition().x +
            platformTextureSize.w + 20.f,
        800.0f);
    b2Body *platformTwoBody =
        this->world->CreateBody(&platformTwoDef);
    b2PolygonShape platformTwoShape;
    platformTwoShape.SetAsBox(platformTextureSize.w / 2,
                              platformTextureSize.h / 2);
    platformTwoBody->CreateFixture(&platformTwoShape, 0.0f);
    this->platformTwo = new Entity(
        this->renderer, platformTexture,
        platformTwoBody->GetPosition(), platformTwoBody);

    auto boxTexture = loader::loadTexture(
        renderer, "assets/box.png", config);
    auto boxTextureSize =
        render::getTextureSize(boxTexture);
    b2BodyDef boxBodyDef;
    boxBodyDef.enabled = true;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position.Set(500.0f, 0.0f);
    b2Body *boxBody = this->world->CreateBody(&boxBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(boxTextureSize.w / 2,
                      boxTextureSize.h / 2);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1.0f;
    boxFixtureDef.friction = 0.3f;
    boxBody->CreateFixture(&boxFixtureDef);
    this->box = new Entity(this->renderer, boxTexture,
                           boxBody->GetPosition(), boxBody);
}

void GameLayer::onTick(float delta) {
    this->world->Step(delta, 2, 6);
    this->platformOne->tick(delta);
    this->platformTwo->tick(delta);
    this->box->tick(delta);
    this->platformOne->render();
    this->platformTwo->render();
    this->box->render();
}
void GameLayer::onDetach() {}