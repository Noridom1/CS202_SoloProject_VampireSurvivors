#ifndef EXPLODINGPROJECTILE_H
#define EXPLODINGPROJECTILE_H

#include "Projectile/Projectile.h"

class ExplodingProjectile : public Projectile {

public:
    ExplodingProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime, float damage);
    ~ExplodingProjectile();

    void updateMovement(float deltaTime, Player *player) override;

    void setBoundingBox() override;

    void update(float deltaTime, Player* player) override;

    void markHit() override;
    
    void updateExplosion(float deltaTime);

    ProjectileCaster getCaster() override;

private:
    void explode(Player *player);

    #include <cmath> // For std::sqrt and std::pow

    bool checkCollisionWith(const sf::FloatRect& rect);


private:
    sf::CircleShape effectiveArea;
    bool hasExploded;
    bool playerExploded;
    float explodingRadius;
    Animation expAnimation;
    Image *expImage;
    unsigned row;
};

#endif