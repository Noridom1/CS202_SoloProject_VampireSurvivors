#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H

#include "Boomerang.h"
#include "KingBible.h"
#include "Lightning.h"

class WeaponFactory {

public:
    static Weapon* createWeapon(WeaponType type, Player *player) {
        if (type == WeaponType::Boomerang) {
            return new Boomerang(player);
        }
        else if (type == WeaponType::KingBible) {
            return new KingBible(player);
        }
        else if (type == WeaponType::LightningRing) {
            return new Lightning(player);
        }
    }

};

#endif