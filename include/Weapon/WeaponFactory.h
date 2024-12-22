#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H

#include "Boomerang.h"
#include "KingBible.h"

class WeaponFactory {

public:
    static Weapon* createWeapon(WeaponType type, Player *player) {
        if (type == WeaponType::Boomerang) {
            return new Boomerang(player);
        }
        if (type == WeaponType::KingBible) {
            return new KingBible(player);
        }
    }

};

#endif