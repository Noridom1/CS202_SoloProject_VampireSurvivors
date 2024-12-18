#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Entity/Entity.h"
#include "Entity/MovingEntity.h"
#include "Animation.h"
#include "ProjectileFlyweightFactory.h"

class Projectile : public MovingEntity {
public:
    Projectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float destroyedAfter, float damage);

    void updateAnimation(float deltaTime);

    //virtual void updateMovement(float deltaTime, Map *map) override;

    void update(float deltaTime);

    void draw(sf::RenderWindow* window);

    void move(sf::Vector2f movement) override;

    bool isMarkedDelete();

    void markDelete();

    float getDamage();

    EntityType getType() const override {return EntityType::Projectile;}

    
protected:
    sf::Sprite* sprite;
    sf::Vector2f direction;
    Animation animation;
    float move_speed;

    bool markedDelete;
    float totalExistedTime;
    float destroyedAfter;

    float damage;
};


#endif 