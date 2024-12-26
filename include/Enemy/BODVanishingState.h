#ifndef BODVANISHINGSTATE_H
#define BODVANISHINGSTATE_H

#include "BringerOfDeathStates.h"

class VanishingState : public BODState {
public:
    VanishingState() : BODState(6) {cout << "VanishingState\n";}

    ~VanishingState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;
};


#endif
