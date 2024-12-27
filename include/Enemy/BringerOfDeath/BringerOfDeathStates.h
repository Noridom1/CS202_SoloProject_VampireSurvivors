#ifndef BRINGEROFDEATHSTATES_H
#define BRINGEROFDEATHSTATES_H

#include "Enemy/BringerOfDeath/BringerOfDeath.h"
#include <memory>

class BODState;
class SpawingState;
class MovingState;

class BODState {
public:
    explicit BODState(unsigned row) : animationRow(row) {}
    virtual ~BODState() = default;

    virtual void onTakingDamage(BringerOfDeath& enemy) {}
    virtual void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) = 0;
    virtual void onHit(BringerOfDeath& enemy) {}

    unsigned getAnimationRow() const { return animationRow; } // Provide row access

protected:
    unsigned animationRow;
};



#endif