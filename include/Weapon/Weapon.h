#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "Projectile/ProjectileManager.h"
#include "Player/Player.h"

class Weapon {
public:
    Weapon(float damage, float cooldown) : damage(damage), cooldown(cooldown) {};
    ~Weapon() {}

    virtual void levelUp() = 0;
    
    //virtual void draw(sf::RenderWindow *window)  = 0;
    virtual void update(sf::RenderWindow *window, Player *player, float deltaTime) = 0;
    
    virtual void cast(sf::Vector2f position, sf::Vector2f direction) = 0;

protected:
    float damage;
    float cooldown;
    int level;
};


#endif