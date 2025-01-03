#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H

#include "Projectile.h"
#include "ProjectileFlyweightFactory.h"
#include "BoomerangProjectile.h"
#include "ExplodingProjectile.h"
#include "KingBibleProjectile.h"
#include "LightningProjectile.h"

class ProjectileFactory {
public:
    static Projectile* createProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime, float damage) {
        if (type == ProjectileType::Boomerang) {
            return new BoomerangProjectile(startPos, direction, speed, lifeTime, damage);
        } 
        else if (type == ProjectileType::ExplodingProjectile) {
            return new ExplodingProjectile(startPos, direction, speed, lifeTime, damage);
        }
        else if (type == ProjectileType::KingBible) {
            return new KingBibleProjectile(startPos, direction, speed, lifeTime, damage);
        }
        else if (type == ProjectileType::Lightning) {
            return new LightningProjectile(startPos, damage);
        }
        else {
            throw std::invalid_argument("Unknown projectile type!");
        }
    }
};
#endif