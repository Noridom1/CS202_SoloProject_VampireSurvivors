#ifndef BRINGEROFDEATH_H
#define BRINGEROFDEATH_H

#include "Enemy.h"

class BODState;

class BringerOfDeath : public Enemy {
public:
    BringerOfDeath(sf::Vector2f pos, float timescale);

    void setState(std::unique_ptr<BODState> newState);

    void update(float deltaTime, sf::Vector2f playerPos) override;

    void updateMovement(float deltaTime, sf::Vector2f playerPos) override;

    void updateAnimation(unsigned row, float deltaTime, bool faceRight);

    bool isAnimationFinished(unsigned row) const;


    void setBoundingBox();

private:
    unique_ptr<BODState> state;

    bool isCharing;

    float maxSpeed;
    float maxHP;
    float maxDamage;
    float attackDist;

    float elapsedTime;
    sf::Vector2f attackDir;

};



#endif
