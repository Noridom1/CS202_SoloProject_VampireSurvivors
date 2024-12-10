#include "Projectile/ProjectileManager.h"

ProjectileManager &ProjectileManager::getInstance()
{
    static ProjectileManager instance; 
    return instance;
}

ProjectileManager::~ProjectileManager()
{
    for (auto& projectile : projectiles) {
        delete projectile;
    }
}
void ProjectileManager::update(float deltaTime)
{
    for (auto& projectile : projectiles) {
        projectile->update(deltaTime);
    }
}

void ProjectileManager::draw(sf::RenderWindow *window)
{
    for (auto& projectile : projectiles) {
        projectile->draw(window);
    }
}

void ProjectileManager::spawnProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed)
 {
    switch (type) {
        case ProjectileType::Boomerang:
            projectiles.emplace_back(new BoomerangProjectile(startPos, direction, speed));
            break;
    }
}

void ProjectileManager::cleanup()
{
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it)->isOutOfBounds()) {
            delete *it;
            it = projectiles.erase(it);
        } else {
            ++it;
        }
    }
}
