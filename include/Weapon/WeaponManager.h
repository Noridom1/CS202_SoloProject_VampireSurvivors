#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include "Player.h"
#include <vector>
#include <unordered_map>
#include "Weapon.h"
#include "Boomerang.h"
#include <iostream>

using namespace std;


enum class WeaponType {
    Boomerang,
};

class WeaponManager {

public:
    WeaponManager(const WeaponManager& other) = delete;

    WeaponManager& operator=(const WeaponManager&) = delete;

    ~WeaponManager();

    static WeaponManager& getInstance();

    void addWeapon(WeaponType type);

    void castWeapons(sf::RenderWindow *window, Player *player, float deltaTime);

private:
    WeaponManager() {}
    unordered_map<WeaponType, Weapon*> exitedWeapons;
    vector<Weapon*> weapons;
    float totalTime;
};

#endif