#include "Weapon/KingBible.h"

KingBible::KingBible(Player *player) :
    Weapon(player, 12.f, 4.f),
    move_speed(4.0f), 
    num_projectiles(2),
    delayedTime(1.3f),
    duration(4.f),
    totalTime(0.0f)
{

}

void KingBible::cast()
{
    sf::Vector2f position = player->getPosition() + sf::Vector2f(30.f, 0.f);
    sf::Vector2f r = position - player->getPosition();
    sf::Vector2f direction(r.y, -r.x);    
    ProjectileManager::getInstance().spawnProjectile(ProjectileType::KingBible, position, direction, move_speed, duration, damage);
}

void KingBible::update(sf::RenderWindow *window, Player *player, float deltaTime)
{
    if (isCasting) {
        totalTime += deltaTime;
        if (totalTime >= delayedTime && num_casted < num_projectiles) {
            totalTime -= delayedTime;
            this->cast();
            num_casted++;
        }
        if (num_casted >= num_projectiles && totalTime >= duration) {
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
            this->cast();
            num_casted++;
        }
    }
}

void KingBible::levelUp()
{
    this->level++;
    this->move_speed *= 1.2f;
    this->damage *= 1.1f;
    this->duration *= 1.1f;
    this->delayedTime *= 0.85f;
    if (level == 2 || level == 4 || level == 5 || level == 6)
        this->num_projectiles++;
    this->cooldown *= 0.95f;
    this->isCasting = false;
    this->num_casted = 0;
    this->totalTime = cooldown;
    if (level == 8)
        this->cooldown = 0.f;
    cout << "KingBible::levelUp()\n";
}
