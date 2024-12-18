#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H

#include "Projectile.h"
#include "ProjectileFlyweightFactory.h"
#include "BoomerangProjectile.h"

class ProjectileFactory {
public:
    static Projectile* createProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
        if (type == ProjectileType::Boomerang) {
            return new BoomerangProjectile(startPos, direction, speed);
        } 
        else {
            throw std::invalid_argument("Unknown enemy type!");
        }
    }
};
#endif