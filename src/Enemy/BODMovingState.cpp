#include "Enemy/BODMovingState.h"
#include "Enemy/BODChargingState.h"
#include "Enemy/BODHurtingState.h"

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

    if (enemy.getElapsedTime() >= enemy.getAtkTime()) {
        enemy.setState(std::make_unique<ChargingState>());
        enemy.setAnimationRow(2);
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
