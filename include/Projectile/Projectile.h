#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Animation.h"
#include "ProjectileFlyweightFactory.h"

class Projectile : public Entity {
public:
    Projectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed);

    void updateAnimation(float deltaTime);

    void updatePosition(float deltaTime);

    virtual void update(float deltaTime);

    void draw(sf::RenderWindow* window);

    void move(sf::Vector2f movement);

    bool isOutOfBounds();
    
protected:
    sf::Sprite* sprite;
    sf::Vector2f position;
    sf::Vector2f direction;
    Animation animation;
    float move_speed;
};


#endif 