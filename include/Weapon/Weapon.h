#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "Projectile/ProjectileManager.h"
#include "Player/Player.h"

enum class WeaponType {
    Boomerang,
    KingBible,
};

class Weapon {
public:
    Weapon(Player *player, float damage, float cooldown);
    ~Weapon() {}

    virtual void levelUp() = 0;
    
    virtual void update(sf::RenderWindow *window, Player *player, float deltaTime) = 0;
    
protected:
    float damage;
    float cooldown;
    int level;
    bool isCasting;
    
    static const int maxLevel;

    Player *player;

};

#endif