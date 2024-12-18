#ifndef BOOMERANGPROJECTILE_H
#define BOOMERANGPROJECTILE_H

#include <iostream>
#include "Projectile/Projectile.h"
#include "Projectile/ProjectileFlyweightFactory.h"

class BoomerangProjectile : public Projectile {
public:
    BoomerangProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed);

    void updateMovement(float deltaTime) override;

    void setBoundingBox();
    
    //void update(float deltaTime, Map *map) override;
private:
    float acceleration;
};

#endif