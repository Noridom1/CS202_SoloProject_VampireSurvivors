#ifndef GHOST_H
#define GHOST_H

#include <SFML/Graphics.hpp>
#include "Enemy/Enemy.h"

class Ghost : public Enemy{
public:
    Ghost(sf::Vector2f pos, float timeScale);
    ~Ghost();

    void updateMovement(float deltaTime, sf::Vector2f playerPos) override;
    
    void setBoundingBox() override;

    void update(float deltaTime, sf::Vector2f playerPos);

    void takeDamage(float damage) override;

    EnemyType getEnemyType() const override { return EnemyType::Ghost; }


private:

    static float maxSpeed;
    static float maxHP;
    static float maxDamage;
};

#endif