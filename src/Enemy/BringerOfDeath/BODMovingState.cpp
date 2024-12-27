#include "Enemy/BringerOfDeath/BODMovingState.h"
#include "Enemy/BringerOfDeath/BODChargingState.h"
#include "Enemy/BringerOfDeath/BODHurtingState.h"
#include "Enemy/BringerOfDeath/BODCastingState.h"


void MovingState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
{
    sf::Vector2f movement = playerPos - enemy.getPosition();

    float magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);

    if (magnitude)
        movement /= magnitude;
    movement *= enemy.getMoveSpeed() * deltaTime;

    bool textureDirection = enemy.getTextureDirection();
    if (std::abs(movement.x) > 0.01f) { // Add a small threshold for precision issues
        enemy.setFacing((movement.x > 0) ? textureDirection : !textureDirection);
        enemy.setBoundingBoxFace();
    }

    if(movement.x && movement.y) {
        movement /= static_cast<float>(sqrt(2));
    }
    enemy.move(movement);

    if (enemy.getElapsedTime() >= enemy.getAtkTime() && enemy.getPhase() == 0) {
        enemy.setState(std::make_unique<ChargingState>());
        enemy.setAnimationRow(2);
        enemy.switchPhase();
    }

    if (enemy.getElapsedTime() >= enemy.getCastingTime() && enemy.getPhase() == 1) {
        enemy.setState(make_unique<CastingState>());
        enemy.setAnimationRow(4);
        enemy.switchPhase();
    }

    //enemy.setAnimationRow(getAnimationRow());
    //cout << "AnimationRow set to " << getAnimationRow();
    //enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
}
void MovingState::onTakingDamage(BringerOfDeath &enemy)
{
    enemy.setAnimationRow(5);
    enemy.setState(std::make_unique<HurtingState>());
}
