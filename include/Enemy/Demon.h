#ifndef DEMON_H
#define DEMON_H

#include "Enemy/Enemy.h"

class Demon : public Enemy {
public:
    Demon(sf::Vector2f pos, float timeScale);

    ~Demon();

    void updateMovement(float deltaTime, sf::Vector2f playerPos) override;
    
    void setBoundingBox() override;

    void update(float deltaTime, sf::Vector2f playerPos);

    void takeDamage(float damage) override;

    void setEffectiveArea();

    void resetBoundingbox();

    void attack();

    EnemyType getEnemyType() const override { return EnemyType::Demon; }

    bool isBoss() override { return true; }


private:
    bool isSpawning;
    bool isCharging;
    bool isAttacking;
    bool isHurting;
    bool isVanishing;

    float totalTime;
    float attackTime;
    float attackingTime;
    bool faceAttack;
    
    static float maxSpeed;
    static float maxHP;
    static float maxDamage;
    static float attackDist;
    static float duration;

    sf::FloatRect normalBoundingBox;
    sf::FloatRect effectArea;
    sf::FloatRect normalBoundingbox;
    sf::Vector2f attackDir;
};

#endif