#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "EnemyFlyweightFactory.h"
#include "Enemy/Ghost.h"
#include "Enemy/Demon.h"
#include "Enemy/Microwave.h"

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, sf::Vector2f startPos, float strengthMultiplier) {
        if (type == EnemyType::Ghost) {
            return new Ghost(startPos, strengthMultiplier);
        } 
        else if (type == EnemyType::Demon) {
            return new Demon(startPos, strengthMultiplier);
        }
        else if (type == EnemyType::Microwave) {
            return new Microwave(startPos, strengthMultiplier);
        }
        else {
            throw std::invalid_argument("Unknown enemy type!");
        }
    }
};

#endif