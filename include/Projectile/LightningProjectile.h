#ifndef LIGHTNINGPROJECTILE_H
#define LIGHTNINGPROJECTILE_H

#include "Projectile.h"

class LightningProjectile : public Projectile {

public:
    LightningProjectile(sf::Vector2f startPos, float damage);

    void updateMovement(float deltaTime, Player* player) override;
    
    void update(float deltaTime, Player *player) override;

    void setBoundingBox();
    
    ProjectileCaster getCaster() override;
    
private:

};

#endif