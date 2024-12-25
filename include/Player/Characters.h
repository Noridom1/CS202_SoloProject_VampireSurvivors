#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Animation.h"

//#include "Texture.h"

using namespace std;

enum class CharacterType {
    Lucy,
    Kael,
    Astra,
    Samurai,
    Wizard,
    // Add more characters as needed
};

struct CharacterStats {
    float HP;
    float armor;
    float base_damage;
    float move_speed;

    CharacterStats() = default;
    CharacterStats(float HP, float armor, float base_damage, float move_speed) :
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
    {CharacterType::Samurai, "../assets/textures/characters/Samurai.png"},
    {CharacterType::Astra, "D:\\CS202_SoloProject_VampireSurvivors\\assets\\textures\\characters\\NightBorne.png"},
    {CharacterType::Lucy, "..\\assets\\textures\\characters\\Warrior.png"},
    {CharacterType::Wizard, "../assets/textures/characters/Wizard.png"},
    {CharacterType::Kael, "../assets/textures/characters/Necromancer.png"},


};

const unordered_map<CharacterType, CharacterStats> characterStats = {
    {CharacterType::Samurai, {150, 5, 20, 180.0}},
    {CharacterType::Astra, {120, 3, 25, 200.f}},
    {CharacterType::Lucy, {120, 2, 10, 220.0}},
    {CharacterType::Wizard, {100, 2, 30, 220.0}},
    {CharacterType::Kael, {120, 2, 10, 180.0f}},
};

const unordered_map<CharacterType, TexturesAnimation> characterAnimations = {
    {CharacterType::Samurai, {4, {10, 16, 7, 4}, {0.1f, 0.1f, 0.1f, 0.1f}}},
    {CharacterType::Astra, {5, {9, 6, 12, 5, 23}, {0.1f, 0.1f, 0.1f, 0.08f, 0.1f}}},
    {CharacterType::Lucy, {5, {6, 8, 12, 4, 11}, {0.1f, 0.1f, 0.1f, 0.1f, 0.1f}}},
    {CharacterType::Wizard, {5, {8, 8, 7, 4, 4}, {0.1f, 0.1f, 0.1f, 0.1f, 0.3f}}},
    {CharacterType::Kael, {5, {8, 8, 17, 5, 8}, {0.1f, 0.1f, 0.1f, 0.1f, 0.3f}}},

};

#endif