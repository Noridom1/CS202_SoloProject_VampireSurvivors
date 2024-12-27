#ifndef CASTINGSTATE_H
#define CASTINGSTATE_H

#include "Enemy/BringerOfDeath/BringerOfDeathStates.h"


class CastingState : public BODState {
public:
    CastingState(); // Row 0 for spawning animation

    ~CastingState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;
};


#endif
