#ifndef BRINGEROFDEATH_H
#define BRINGEROFDEATH_H

#include "Enemy/Enemy.h"
#include <memory>

class BODState;

class BringerOfDeath : public Enemy {
public:
    BringerOfDeath(sf::Vector2f pos, float strengthMultiplier);

    void setState(std::unique_ptr<BODState> newState);

    void update(float deltaTime, sf::Vector2f playerPos) override;

    void updateMovement(float deltaTime, sf::Vector2f playerPos) override;

    void updateAnimation(unsigned row, float deltaTime, bool faceRight);

    bool isAnimationFinished(unsigned row) const;

    void setBoundingBox();

    void setBoundingBoxFace();

    void resetElapsedTime();

    float getElapsedTime();

    float getAtkTime();

    float getCastingTime();

    int getPhase();

    void switchPhase();

    void takeDamage(float damage) override;
    
    EnemyType getEnemyType() const override {
        return EnemyType::BringerOfDeath;
    }

    bool isBoss() override { return true; }

private:
    std::unique_ptr<BODState> state;

    bool isCharing;

    float maxSpeed;
    float maxHP;
    float maxDamage;
    float attackDist;

    float elapsedTime;
    sf::Vector2f attackDir;

    sf::FloatRect stdBBox;
    float atkTime;
    float castingTime;
    int phase;
};



#endif
