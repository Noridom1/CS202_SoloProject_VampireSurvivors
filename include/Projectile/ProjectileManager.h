#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>
#include <memory>
#include "Projectile.h"
#include "ProjectileFlyweightFactory.h"
#include "BoomerangProjectile.h"
#include <SFML/Graphics.hpp>

class ProjectileManager {
public:
    ProjectileManager(const ProjectileManager&) = delete;
    ProjectileManager& operator=(const ProjectileManager&) = delete;

    static ProjectileManager& getInstance() {
        static ProjectileManager instance; 
        return instance;
    }

    ~ProjectileManager() {
        for (auto& projectile : projectiles) {
            delete projectile;
        }
    }

    void update(float deltaTime) {
        for (auto& projectile : projectiles) {
            projectile->update(deltaTime);
        }
    }

    void draw(sf::RenderWindow* window) {
        for (auto& projectile : projectiles) {
            projectile->draw(window);
        }
    }

    void spawnProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
        switch (type) {
            case ProjectileType::Boomerang:
                projectiles.emplace_back(new BoomerangProjectile(startPos, direction, speed));
                break;
        }
    }

    void cleanup() {
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            if ((*it)->isOutOfBounds()) {
                delete *it;
                it = projectiles.erase(it);
            } else {
                ++it;
            }
        }
    }

private:
    ProjectileManager() {}
    std::vector<Projectile*> projectiles;
};

#endif // PROJECTILEMANAGER_H
