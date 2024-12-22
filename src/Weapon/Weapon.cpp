#include "Weapon/Weapon.h"

const int Weapon::maxLevel = 8;

Weapon::Weapon(Player *player, float damage, float cooldown) 
    : player(player), damage(damage), cooldown(cooldown), isCasting(false), level(0)
{

}