#ifndef KINGBIBLEPROJECTILE_H
#define KINGBIBLEPROJECTILE_H

#include "Projectile.h"

class KingBibleProjectile : public Projectile {

public:
    KingBibleProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed, float destroyedAfter, float damage);

    void updateMovement(float deltaTime, Player* player) override;

    void setBoundingBox();
    
    ProjectileCaster getCaster() override;

private:
    float angle;
    float orbitRadius;
    int previousHalfCycle;
};

#endif