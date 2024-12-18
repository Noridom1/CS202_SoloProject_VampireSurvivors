#ifndef ENEMYFLYWEIGHTFACTORY_H
#define ENEMYFLYWEIGHTFACTORY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include "Animation.h"
#include "Image.h"

using namespace std;

enum class EnemyType {
    Ghost,
};

static const std::unordered_map<EnemyType, std::string> EnemyPaths = {
        { EnemyType::Ghost, "../assets/textures/enemies/Ghost.png" },
        //{ ProjectileType::Bullet,    "../Bullet.png" },
        //{ ProjectileType::Laser,     "../Laser.png" }
};

const unordered_map<EnemyType, TexturesAnimation> EnemyAnimations = {
    {EnemyType::Ghost, {4, {6, 4, 7, 7}, {0.03f, 0.01f, 0.01f, 0.03f}}},
};

class EnemyFlyweightFactory {
public:
    static Image& getEnemyImg(EnemyType type) {
        static std::unordered_map<EnemyType, std::unique_ptr<Image>> enemyImage;

        string filename = EnemyPaths.at(type);
        if (enemyImage.find(type) == enemyImage.end()) {
            enemyImage[type] = std::make_unique<Image>(filename);
        }
        return *enemyImage[type];
    }
};


#endif