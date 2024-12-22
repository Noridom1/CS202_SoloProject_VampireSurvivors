#include "Weapon/WeaponManager.h"
#include "Weapon/WeaponFactory.h"
#include <random>

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
    cout << "Added one weapon of type " << static_cast<int>(type) << endl;
    for (auto weapon : weapons) {
        if (!weapon) {
            cout << "Error\n";
        }
        cout << int(weapon->getType());
    }
}

void WeaponManager::castWeapons(sf::RenderWindow *window, Player *player, float deltaTime)
{
    for (auto weapon : weapons) {
        weapon->update(window, player, deltaTime);
    }
}

vector<WeaponType> WeaponManager::randomWeapons(int num)
{
    std::vector<WeaponType> selectedWeapons;

        // Determine the range of the WeaponType enum
        int weaponCount = static_cast<int>(WeaponType::MaxType); // Update this as you add more enums

        std::random_device rd;  // Seed for random number generator
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine
        std::uniform_int_distribution<> dis(0, weaponCount - 1);

        // Generate random weapon types
        for (int i = 0; i < num; ++i) {
            int randomValue = dis(gen);
            selectedWeapons.push_back(static_cast<WeaponType>(randomValue));
        }

        return selectedWeapons;
}

int WeaponManager::getLevelByType(WeaponType type)
{
    if (this->exitedWeapons.find(type) == exitedWeapons.end())
        return 0;
    else return exitedWeapons[type]->getLevel();
}
