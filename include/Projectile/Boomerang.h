#ifndef BOOMERANG_H
#define BOOMERANG_H

#include <iostream>
#include "Projectile/Projectile.h"
#include "Projectile/ProjectileFlyweightFactory.h"

class Boomerang : public Projectile {
public:
    Boomerang(sf::Vector2f startPos, sf::Vector2f direction, float speed) : 
        Projectile(ProjectileType::Boomerang, startPos, direction, speed), acceleration(-250.0f) {}

    void updatePosition(float deltaTime) {
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0.0f) {
            direction /= magnitude;
        }
        move_speed += acceleration * deltaTime;
        this->move(direction * move_speed * deltaTime);
    }

    void update(float deltaTime) override {
        //std::cout << "Boomerang::update()\n";
        Projectile::updateAnimation(deltaTime);
        updatePosition(deltaTime);
    }
private:
    float acceleration;

};

#endif