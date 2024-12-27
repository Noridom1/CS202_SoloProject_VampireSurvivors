#include "Enemy/BringerOfDeath/BODCastingState.h"
#include "Enemy/BringerOfDeath/BODMovingState.h"
#include "Projectile/ProjectileManager.h"

CastingState::CastingState() : 
    BODState(4) 
{}

void CastingState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
{
    if (enemy.isAnimationFinished(getAnimationRow())) {
        enemy.setState(std::make_unique<MovingState>());
        enemy.setAnimationRow(3);
        enemy.resetElapsedTime();
    }
}