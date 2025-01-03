#ifndef BODHURTINGSTATE_H
#define BODHURTINGSTATE_H

#include "Enemy/BringerOfDeath/BringerOfDeathStates.h"

class HurtingState : public BODState {
public:
    HurtingState();

    ~HurtingState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;
};


#endif
