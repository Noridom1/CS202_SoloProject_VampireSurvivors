#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "EnemyFlyweightFactory.h"
#include "Enemy/Ghost.h"
#include "Enemy/Demon.h"
#include "Enemy/Microwave.h"

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, sf::Vector2f startPos, float timeScale) {
        if (type == EnemyType::Ghost) {
            return new Ghost(startPos, timeScale);
        } 
        else if (type == EnemyType::Demon) {
            return new Demon(startPos, timeScale);
        }
        else if (type == EnemyType::Microwave) {
            return new Microwave(startPos, timeScale);
        }
        else {
            throw std::invalid_argument("Unknown enemy type!");
        }
    }
};

#endif