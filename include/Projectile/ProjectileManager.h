#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>
#include "Projectile.h"
#include "ProjectileFlyweightFactory.h"
#include "Boomerang.h"

class ProjectileManager {
public:
    ~ProjectileManager() {
        for (auto& projectile : projectiles) {
            delete projectile;
        }
    }
    void update(float deltaTime) {
        for (auto& projectile : projectiles) {
            projectile->update(deltaTime);
            //cout << "Update one projectile\n";
        }
    }

    void draw(sf::RenderWindow* window) {
        for (auto& projectile : projectiles) {
            projectile->draw(window);
            //cout << "Drawn a projectile\n";
        }
    }

    void spawnProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
        cout << "Spawning one projectile at " << startPos.x << " " << startPos.y << endl;
        switch (type)
        {
            case ProjectileType::Boomerang:
                projectiles.emplace_back(new Boomerang(startPos, direction, speed));
                cout << "Spawned one boomerang at " << startPos.x << " " << startPos.y << endl;
                break;
        }
    }

    void cleanup() {
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            if ((*it)->isOutOfBounds()) {
                delete *it; // Delete the projectile object
                it = projectiles.erase(it); // Erase the pointer and update iterator
            } else {
                ++it; // Move to the next projectile
            }
        }
        cout << "Number of projectile: " << projectiles.size() << endl;
    }


private:
    std::vector<Projectile*> projectiles;
    //std::vector<std::unique_ptr<Projectile>> inactiveProjectiles;
};


#endif