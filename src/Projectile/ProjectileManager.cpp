#include "Projectile/ProjectileManager.h"
#include "Projectile/ProjectileFactory.h"

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
void ProjectileManager::update(float deltaTime, Player* player)
{
    for (auto& projectile : projectiles) {
        projectile->update(deltaTime, player);
    }
}

void ProjectileManager::draw(sf::RenderWindow *window)
{
    for (auto& projectile : projectiles) {
        projectile->draw(window);
    }
}

void ProjectileManager::spawnProjectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime, float damage)
{
    projectiles.push_back(ProjectileFactory::createProjectile(type, startPos, direction, speed, lifeTime, damage));
}

void ProjectileManager::cleanup()
{
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it)->isMarkedForDelete()) {
            delete *it;
            it = projectiles.erase(it);
            //cout << "Clean up 1 projectile!\n";
        } else {
            ++it;
        }
    }
    //cout << "Number of projectiles: " << this->projectiles.size() << endl;
}

vector<Projectile*>& ProjectileManager::getProjectiles() {
    return projectiles;
}