#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include "Player/Player.h"
#include <vector>
#include <unordered_map>
#include "Boomerang.h"
#include <iostream>

using namespace std;

class WeaponManager {

public:
    WeaponManager(const WeaponManager& other) = delete;

    WeaponManager& operator=(const WeaponManager&) = delete;

    ~WeaponManager();

    static WeaponManager& getInstance();

    void addWeapon(WeaponType type, Player *player);

    void castWeapons(sf::RenderWindow *window, Player *player, float deltaTime);

    vector<WeaponType> randomWeapons(int num = 3);

    int getLevelByType(WeaponType type);

private:
    WeaponManager() {}
    unordered_map<WeaponType, Weapon*> exitedWeapons;
    vector<Weapon*> weapons;
    float totalTime;
};

#endif