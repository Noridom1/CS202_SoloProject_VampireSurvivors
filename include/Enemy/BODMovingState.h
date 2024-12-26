#ifndef BODMOVINGSTATE_H
#define BODMOVINGSTATE_H

#include "BringerOfDeathStates.h"

class MovingState : public BODState {
public:
    MovingState() : BODState(1) {}

    ~MovingState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;

    void onTakingDamage(BringerOfDeath& enemy) override;
};

#endif