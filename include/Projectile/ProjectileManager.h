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

    ~ProjectileManager();
    
    static ProjectileManager& getInstance();

    void update(float deltaTime, Player *player);

    void draw(sf::RenderWindow* window);

    void spawnProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime, float damage);

    void cleanup();

    vector<Projectile*>& getProjectiles();

private:
    ProjectileManager() {}
    std::vector<Projectile*> projectiles;
};

#endif // PROJECTILEMANAGER_H
