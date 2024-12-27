#include "Weapon/Boomerang.h"

Boomerang::Boomerang(Player *player) : 
    Weapon(player, 10.0f, 2.5f), 
    move_speed(500.0f), 
    num_projectiles(1),
    delayedTime(0.15f),
    totalTime(0.0f)
{

}

void Boomerang::cast(sf::Vector2f position, sf::Vector2f direction)
{
    ProjectileManager::getInstance().spawnProjectile(ProjectileType::Boomerang, position, direction, move_speed, 5.f, damage);
}

void Boomerang::update(sf::RenderWindow *window, Player *player, float deltaTime)
{
    if (isCasting) {
        totalTime += deltaTime;
        if (totalTime >= delayedTime) {
            totalTime -= delayedTime;
            //sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePos = window->mapPixelToCoords(mousePosWindow); 
            sf::Vector2f position = player->getPosition();
            sf::Vector2f direction = mousePos - position;
            this->cast(position, direction);
            num_casted++;
        }
        if (num_casted >= num_projectiles) {
            num_casted = 0;
            isCasting = false;
            totalTime = 0;
        }
    }
    else {
        totalTime += deltaTime;
        if (totalTime >= cooldown) {
            totalTime -= cooldown ;
            isCasting = true;
            sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePos = window->mapPixelToCoords(mousePosWindow); // Maps to world coordinates

            sf::Vector2f position = player->getPosition();
            sf::Vector2f direction = mousePos - position;

            // Debug output to verify the values
            // std::cout << "Mouse Window Position: " << mousePosWindow.x << ", " << mousePosWindow.y << std::endl;
            // std::cout << "Mapped Mouse Position (World): " << mousePos.x << ", " << mousePos.y << std::endl;
            // std::cout << "Player Position: " << position.x << ", " << position.y << std::endl;
            // std::cout << "Direction: " << direction.x << ", " << direction.y << std::endl;
            
            this->cast(position, direction);
            num_casted++;
        }
    }
}

void Boomerang::levelUp()
{
    this->level++;
    //this->move_speed *= 1.2f;
    this->damage *= 1.1f;
    this->num_projectiles++;
    this->cooldown *= 0.9f;
    cout << "Boomerang::levelUp()\n";
}
