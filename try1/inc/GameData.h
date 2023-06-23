#pragma once

struct GameData {
    int quantity = 0;
    float force = 0;
    bool forceOrImpulse = false;
    bool treatAsBullet = false;
    float xDir = 0;
    float yDir = 0;
    float densityCoefficient = 0.3;
    float frictionCoefficient = 0.1;
    float restitutionThreshold = 100000;
    float gravity = -9.8;
    float gravityScale = 1;
};