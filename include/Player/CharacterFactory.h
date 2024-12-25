#ifndef CHARACTERFACTORY_H
#define CHARACTERFACTORY_H

#include "Lucy.h"
#include "Kael.h"
#include "Astra.h"


class CharacterFactory {
public:
    static Player* createPlayer(CharacterType type, sf::Vector2f startPos) {
        if (type == CharacterType::Lucy) {
            return new Lucy(startPos);
        } 
        else if (type == CharacterType::Astra) {
            return new Astra(startPos);
        }
        // else if (type == CharacterType::Chest) {
        //     return new Chest(startPos, lifetime, timeScale);
        // }
        else if (type == CharacterType::Kael) {
            return new Kael(startPos);
        }
        else {
            throw std::invalid_argument("Unknown player type!");
        }
    }
};

#endif 