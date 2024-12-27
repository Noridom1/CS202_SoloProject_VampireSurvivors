#include "Enemy/BringerOfDeath/BODHurtingState.h"
#include "Enemy/BringerOfDeath/BODMovingState.h"

HurtingState::HurtingState() : 
    BODState(5) 
{}

void HurtingState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
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

    //enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
    if (enemy.isAnimationFinished(getAnimationRow())) {
        enemy.setState(std::make_unique<MovingState>());
        enemy.setAnimationRow(1);
    }
    //enemy.setAnimationRow(getAnimationRow());

}
