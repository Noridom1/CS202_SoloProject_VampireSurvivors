#ifndef MICROWAVE_H
#define MICROWAVE_H

#include "Enemy/Enemy.h"

class Microwave : public Enemy {

public:
    Microwave(sf::Vector2f pos, float timeScale);
    ~Microwave();

    void updateMovement(float deltaTime, sf::Vector2f playerPos) override;
    
    void setBoundingBox() override;

    void update(float deltaTime, sf::Vector2f playerPos);

    void takeDamage(float damage) override;

    void attack(sf::Vector2f playerPos);

    EnemyType getEnemyType() const override { return EnemyType::Microwave; }

private:

    static float maxSpeed;
    static float maxHP;
    static float maxDamage;

    float totalTime;
    float attackTime;
};




#endif