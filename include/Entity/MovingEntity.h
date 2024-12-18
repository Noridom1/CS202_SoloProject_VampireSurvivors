#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include <SFML/Graphics.hpp>
#include <Map/Map.h>
#include "Entity/Entity.h"

class MovingEntity : public Entity {

public:
    MovingEntity(sf::Vector2f pos) : Entity(pos) {}

    void moveBoundingBox(sf::Vector2f movement);

    virtual void updateMovement(float deltaTime) = 0;

    //virtual void move(sf::Vector2f movement) = 0;

};

#endif