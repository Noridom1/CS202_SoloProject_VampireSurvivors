#include "Weapon/WeaponManager.h"

WeaponManager::~WeaponManager()
{
    for (Weapon* weapon: weapons){
        delete weapon;
    }
}

WeaponManager &WeaponManager::getInstance()
{
    static WeaponManager instance;
    return instance;
}

void WeaponManager::addWeapon(WeaponType type)
{
    if (exitedWeapons.find(type) != exitedWeapons.end()) {
        exitedWeapons[type]->levelUp();
        return;
    }

    switch (type)
    {
        case WeaponType::Boomerang:
            this->weapons.emplace_back(new Boomerang());
            break;
        
        default:
            break;
    }
    this->exitedWeapons[type] = weapons.back();
    cout << "Added one weapon\n";
}

void WeaponManager::castWeapons(sf::RenderWindow *window, Player *player, float deltaTime)
{
    for (auto weapon: weapons){
        weapon->update(window, player, deltaTime);
    }
}
