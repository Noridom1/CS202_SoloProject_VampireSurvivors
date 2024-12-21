#ifndef CHARACTERFACTORY_H
#define CHARACTERFACTORY_H

#include "Lucy.h"

class CharacterFactory {
public:
    static Player* createPlayer(CharacterType type, sf::Vector2f startPos) {
        if (type == CharacterType::Lucy) {
            return new Lucy(startPos);
        } 
        // else if (type == CharacterType::NightBorne) {
        //     return new NightBorne(startPos);
        // }
        // else if (type == CharacterType::Chest) {
        //     return new Chest(startPos, lifetime, timeScale);
        // }
        else {
            throw std::invalid_argument("Unknown pickup type!");
        }
    }
};

#endif 