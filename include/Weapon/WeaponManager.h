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

    ~WeaponManager() {
        for (Weapon* weapon: weapons){
            delete weapon;
        }
    }

    static WeaponManager& getInstance() {
        static WeaponManager instance;
        return instance;
    }

    void addWeapon(WeaponType type) {
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

    void castWeapons(sf::RenderWindow *window, Player *player, float deltaTime) {
        for (auto weapon: weapons){
            weapon->update(window, player, deltaTime);
        }
    }

private:
    WeaponManager() {}
    unordered_map<WeaponType, Weapon*> exitedWeapons;
    vector<Weapon*> weapons;
    float totalTime;
};

#endif