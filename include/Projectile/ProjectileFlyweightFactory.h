#ifndef PROJECTILEFLYWEIGHTFACTORY_H
#define PROJECTILEFLYWEIGHTFACTORY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include "Image.h"

using namespace std;

enum class ProjectileType {
    Boomerang,
};

static const std::unordered_map<ProjectileType, std::string> ProjectilePaths = {
        { ProjectileType::Boomerang, "../assets/textures/projectiles/Boomerang.png" },
        //{ ProjectileType::Bullet,    "../Bullet.png" },
        //{ ProjectileType::Laser,     "../Laser.png" }
};

const unordered_map<ProjectileType, TexturesAnimation> ProjectileAnimations = {
    {ProjectileType::Boomerang, {1, {8}, {0.03f}}},

};

class ProjectileFlyweightFactory {
public:
    static Image& getProjectileImg(ProjectileType type) {
        static std::unordered_map<ProjectileType, std::unique_ptr<Image>> projectileImage;

        string filename = ProjectilePaths.at(type);
        if (projectileImage.find(type) == projectileImage.end()) {
            projectileImage[type] = std::make_unique<Image>(filename);
        }
        return *projectileImage[type];
    }
};


#endif