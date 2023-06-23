#include <inc/GameLayer.h>
#include <loader/loader.hpp>
#include <logger/logger.h>
#include <render/render.hpp>
using namespace try1;

void GameLayer::handleKeyboardInput() {
    int x = 0;
    int y = 0;

    // w or up arrow
    if (this->controls.keyboardKeys[119] ||
        this->controls.keyboardKeys[1073741906]) {
        y += 1;
    }
    // s or down arrow
    if (this->controls.keyboardKeys[115] ||
        this->controls.keyboardKeys[1073741905]) {
        y -= 1;
    }
    // a or left arrow
    if (this->controls.keyboardKeys[97] ||
        this->controls.keyboardKeys[1073741904]) {
        x -= 1;
    }
    // d or right arrow
    if (this->controls.keyboardKeys[100] ||
        this->controls.keyboardKeys[1073741903]) {
        x += 1;
    }

    if (x != 0 || y != 0) {
        fire(x, y);
    }
}

void GameLayer::setGlobals() {
    for (int i = 0; i < this->entities.size(); i++) {
        this->entities[i]->getBody()->SetBullet(
            this->gameData->treatAsBullet);
        this->entities[i]->getBody()->SetGravityScale(
            this->gameData->gravityScale);
        auto fixture =
            this->entities[i]->getBody()->GetFixtureList();
        fixture->SetDensity(
            this->gameData->densityCoefficient);
        fixture->SetFriction(
            this->gameData->frictionCoefficient);
        fixture->SetRestitutionThreshold(
            this->gameData->restitutionThreshold);
    }
}

void GameLayer::fire() {
    fire(this->gameData->xDir, this->gameData->yDir);
}

void GameLayer::fire(float x, float y) {
    for (int i = 0; i < this->entities.size(); i++) {
        auto entity = this->entities[i];
        b2Vec2 force(x, -y);
        force *= this->gameData->force;
        this->gameData->forceOrImpulse
            ? entity->getBody()->ApplyForceToCenter(force,
                                                    true)
            : entity->getBody()->ApplyLinearImpulseToCenter(
                  force, true);
    }
}

void GameLayer::changeEntityAmount(int quantity) {
    int diff = quantity - this->entities.size();
    if (diff == 0)
        return;
    if (diff > 0) {
        std::uniform_int_distribution<int> distribution(
            0, this->screenWidth);
        for (int i = 0; i < diff; i++) {
            int random = distribution(this->rnd);
            this->spawnNewBox(random, 0);
        }
    } else {
        for (int i = this->entities.size() - 1;
             i > this->entities.size() + diff; i--) {
            auto entity = this->entities[i];
            b2Fixture *fixture =
                entity->getBody()->GetFixtureList();
            entity->getBody()->DestroyFixture(fixture);

            this->world->DestroyBody(
                this->entities[i]->getBody());
            delete this->entities[i];
            this->entities.pop_back();
        }
    }
}

Entity *GameLayer::spawnNewBox(int x, int y) {
    auto boxTexture =
        loader::loadTexture(renderer, "assets/box.png");
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
    boxFixtureDef.density =
        this->gameData->densityCoefficient;
    boxFixtureDef.friction =
        this->gameData->frictionCoefficient;
    boxFixtureDef.restitutionThreshold =
        this->gameData->restitutionThreshold;
    boxBody->CreateFixture(&boxFixtureDef);
    boxBody->SetGravityScale(this->gameData->gravityScale);
    boxBody->SetBullet(this->gameData->treatAsBullet);
    this->entities.push_back(
        new Entity(this->renderer, boxTexture,
                   boxBody->GetPosition(), boxBody));
    auto entity = this->entities[this->entities.size() - 1];

    this->inputSystem->getEmitter()->On(
        input::kEventKeyboardDown,
        std::function<void(int32_t id)>([=](int32_t id) {
            LOG_CLIENT_INFO("Button Down",
                            std::to_string(id).c_str());
            entity->getBody()->ApplyLinearImpulse(
                b2Vec2(-50000, 200), b2Vec2(0.5f, 0.5f),
                true);
        }));
    LOG_CLIENT_INFO(
        "Try1Burn: ",
        (std::string("Spawned entity with id ") +
         std::to_string(this->entities.size() - 1))
            .c_str());
    return entity;
}

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

void GameLayer::onAttach() {

    auto platformTexture = loader::loadTexture(
        this->renderer, "assets/platform.png");
    auto input = this->inputSystem;

    b2Vec2 gravity(0.0f,
                   this->gameData->gravity); // Set gravity
    this->world = new b2World(gravity);
    this->world->SetContinuousPhysics(true);
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
    spawnNewBox(200, 300);

    this->inputSystem->getEmitter()->On(
        input::InputEvents::kEventKeyboardDown,
        std::function<void(int32_t id)>([&](int32_t id) {
            this->controls.keyboardKeys[id] = true;
            LOG_CLIENT_INFO("Btn",
                            std::to_string(id).c_str());
        }));
    this->inputSystem->getEmitter()->On(
        input::InputEvents::kEventKeyboardUp,
        std::function<void(int32_t id)>([&](int32_t id) {
            this->controls.keyboardKeys[id] = false;
        }));
}

void GameLayer::onTick(float delta) {
    this->lastDelta = delta;
    if (-this->world->GetGravity().y !=
        this->gameData->gravity) {
        this->world->SetGravity(
            b2Vec2(0.f, -this->gameData->gravity));
    }
    handleKeyboardInput();
    this->world->Step(delta, 2, 6);
    this->platformOne->tick(delta);
    this->platformTwo->tick(delta);
    for (int i = 0; i < this->entities.size(); i++) {
        this->entities[i]->tick(delta);
    }
    this->platformOne->render();
    this->platformTwo->render();
    for (int i = 0; i < this->entities.size(); i++) {
        this->entities[i]->render();
    }
    if (this->entities.size() != this->gameData->quantity) {
        this->changeEntityAmount(this->gameData->quantity);
    }
}
void GameLayer::onDetach() {}