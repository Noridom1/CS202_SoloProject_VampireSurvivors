#ifndef BODSPAWNINGSTATE_H
#define BODSPAWNINGSTATE_H

#include "Enemy/BringerOfDeath/BringerOfDeathStates.h"

class SpawningState : public BODState {
public:
    SpawningState() : BODState(0) {} // Row 0 for spawning animation

    ~SpawningState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;
};


#endif
