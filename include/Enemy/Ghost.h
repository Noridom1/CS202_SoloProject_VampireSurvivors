#ifndef GHOST_H
#define GHOST_H

#include <SFML/Graphics.hpp>
#include "Enemy/Enemy.h"

class Ghost : public Enemy{
public:
    Ghost(sf::Vector2f pos);
    ~Ghost();

    void updateMovement(float deltaTime, sf::Vector2f playerPos) override;
    
    void setBoundingBox() override;

    void update(float deltaTime, sf::Vector2f playerPos);

private:
    bool isSpawning;
    bool isHurting;
    bool isVanishing;

    float acceleration;
};

#endif