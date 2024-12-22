#include "Weapon/WeaponManager.h"
#include "Weapon/WeaponFactory.h"

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

void WeaponManager::addWeapon(WeaponType type, Player *player)
{
    if (exitedWeapons.find(type) != exitedWeapons.end()) {
        exitedWeapons[type]->levelUp();
        return;
    }

    this->weapons.push_back(WeaponFactory::createWeapon(type, player));
    this->exitedWeapons[type] = weapons.back();
    cout << "Added one weapon\n";
}

void WeaponManager::castWeapons(sf::RenderWindow *window, Player *player, float deltaTime)
{
    for (auto weapon: weapons){
        weapon->update(window, player, deltaTime);
    }
}
