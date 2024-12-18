#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy/Enemy.h"
#include "EnemyFlyweightFactory.h"
#include "Enemy/Ghost.h"

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, sf::Vector2f startPos) {
        if (type == EnemyType::Ghost) {
            return new Ghost(startPos);
        } 
        else {
            throw std::invalid_argument("Unknown enemy type!");
        }
    }
};

#endif