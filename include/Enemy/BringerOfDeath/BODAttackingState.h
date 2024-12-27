#ifndef ATTACKINGSTATE_H
#define ATTACKINGSTATE_H

#include "Enemy/BringerOfDeath/BringerOfDeath.h"
#include "Enemy/BringerOfDeath/BringerOfDeathStates.h"


class AttackingState : public BODState {
public:
    AttackingState(sf::Vector2f direction);

    ~AttackingState() {}

    void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override;
private:
    sf::Vector2f attackDir;
};


#endif
