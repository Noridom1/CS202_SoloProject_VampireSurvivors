#include "Enemy/BODVanishingState.h"

void VanishingState::update(float deltaTime, BringerOfDeath &enemy, sf::Vector2f playerPos)
{
    cout << "Update VanishingState\n";
    if (enemy.isAnimationFinished(getAnimationRow())) {
        cout << "Marking for delete\n";
        enemy.markForDelete();
    }
}