#include "Enemy/BODSpawningState.h"
#include "Enemy/BODMovingState.h"

void SpawningState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
{
    //enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
    if (enemy.isAnimationFinished(getAnimationRow())) {
        enemy.setState(std::make_unique<MovingState>());
        enemy.setAnimationRow(1);
    }
    //enemy.setAnimationRow(getAnimationRow());

}