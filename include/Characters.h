#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <string>
#include <unordered_map>

using namespace std;

enum class CharacterType {
    ImeldaBelpaese,
    Mage,
    Archer,
    // Add more characters as needed
};

struct CharacterStats {
    int HP;
    int armor;
    int base_damage;
    float move_speed;

    CharacterStats() = default;
    CharacterStats(int HP, int armor, int base_damage, float move_speed) :
        HP(HP), armor(armor), base_damage(base_damage), move_speed(move_speed) {}

    CharacterStats(const CharacterStats& other)
        : HP(other.HP), armor(other.armor), base_damage(other.base_damage), move_speed(other.move_speed) {}
        
    CharacterStats& operator=(const CharacterStats& other) {
        if (this != &other) {  // Check for self-assignment
            this->HP = other.HP;
            this->armor = other.armor;
            this->base_damage = other.base_damage;
            this->move_speed = other.move_speed;
        }
        return *this;
    }
};

const unordered_map<CharacterType, string> characterTextures = {
    {CharacterType::ImeldaBelpaese, "../assets/textures/characters/ImeldaBelpaese.png"},
    {CharacterType::Mage, "textures/mage.png"},
    {CharacterType::Archer, "textures/archer.png"},
};

const unordered_map<CharacterType, CharacterStats> characterStats = {
    {CharacterType::ImeldaBelpaese, {150, 5, 20, 180.0}},
    {CharacterType::Mage, {120, 3, 25, 200.0}},
    {CharacterType::Archer, {100, 2, 30, 220.0}},
};

#endif