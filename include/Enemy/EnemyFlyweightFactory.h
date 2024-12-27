#ifndef ENEMYFLYWEIGHTFACTORY_H
#define ENEMYFLYWEIGHTFACTORY_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include "Animation.h"
#include "Image.h"

using namespace std;

enum class EnemyType {
    Ghost,
    BringerOfDeath,
    Microwave,
    Demon,
};

static const std::unordered_map<EnemyType, std::string> EnemyPaths = {
        { EnemyType::Ghost, "../assets/textures/enemies/Ghost.png" },
        { EnemyType::Demon, "../assets/textures/enemies/Demon.png"},
        { EnemyType::Microwave, "../assets/textures/enemies/Microwave.png"},
        { EnemyType::BringerOfDeath, "../assets/textures/enemies/BringerOfDeath.png"},
        
        //{ EnemyType::Bullet,    "../Bullet.png" },
        //{ ProjectileType::Laser,     "../Laser.png" }
};

const unordered_map<EnemyType, TexturesAnimation> EnemyAnimations = {
    {EnemyType::Ghost, {4, {6, 4, 7, 7}, {0.06f, 0.1f, 0.1f, 0.1f}}},
    {EnemyType::Demon, {5, {20, 6, 6, 12, 6}, {0.05f, 0.05f, 0.1f, 0.2f, 0.1f}}},
    {EnemyType::Microwave, {5, {5, 6, 15, 4, 8}, {0.1f, 0.1f, 0.1f, 0.05f, 0.1f}}},
    {EnemyType::BringerOfDeath, {7, {5, 8, 4, 6, 9, 3, 10}, {0.1f, 0.1f, 0.3f, 0.05f, 0.1f, 0.1f, 0.2f}}},


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