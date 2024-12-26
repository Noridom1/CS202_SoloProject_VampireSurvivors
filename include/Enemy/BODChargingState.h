#ifndef CHARGINGSTATE_H
#define CHARGINGSTATE_H

#include "BringerOfDeathStates.h"

class ChargingState : public BODState {
public:
    ChargingState(); // Row 0 for spawning animation

    ~ChargingState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;
};


#endif
