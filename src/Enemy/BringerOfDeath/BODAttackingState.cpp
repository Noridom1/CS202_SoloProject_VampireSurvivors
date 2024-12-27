#include "Enemy/BringerOfDeath/BODAttackingState.h"
#include "Enemy/BringerOfDeath/BODMovingState.h"

AttackingState::AttackingState(sf::Vector2f direction): BODState(3), attackDir(direction) {
    float magnitude = sqrt(attackDir.x * attackDir.x + attackDir.y * attackDir.y);
    if (magnitude)
        attackDir /= 4 * magnitude;
}

void AttackingState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
{
    //enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
    sf::Vector2f movement = enemy.getMoveSpeed() * 10.f * deltaTime * attackDir;

    if(movement.x && movement.y) {
        movement /= static_cast<float>(sqrt(2));
    }

    enemy.move(movement);
    
    if (enemy.isAnimationFinished(getAnimationRow())) {
        enemy.setState(std::make_unique<MovingState>());
        enemy.resetElapsedTime();
        enemy.setAnimationRow(1);
        //cout << "Spawning finished\n";
    }
    //enemy.setAnimationRow(getAnimationRow());

}
