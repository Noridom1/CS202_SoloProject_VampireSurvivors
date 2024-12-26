#include "Enemy/BODChargingState.h"
#include "Enemy/BODAttackingState.h"

ChargingState::ChargingState() : 
    BODState(2) 
{}

void ChargingState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
{
    //enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
    if (enemy.isAnimationFinished(getAnimationRow())) {
        enemy.setState(std::make_unique<AttackingState>(playerPos - enemy.getPosition()));
        enemy.setAnimationRow(3);
    }
    //enemy.setAnimationRow(getAnimationRow());

}
