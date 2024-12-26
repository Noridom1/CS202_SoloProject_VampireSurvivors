#include "CollisionHandling/CollisionHandler.h"
#include "CollisionHandling/CollisionMediator.h"

CollisionHandler::CollisionHandler(sf::FloatRect bound)
    : quadtree(new Quadtree(0, bound)) 
{

}

CollisionHandler::~CollisionHandler()
{
    delete quadtree;
}

void CollisionHandler::handlePlayerCollision(
    Player *player, 
    vector<StationaryEntity *> &obstacles, 
    vector<Enemy *> &enemies, 
    vector<Projectile *> &projectiles
    )
{
    vector<Entity*> allEntities;
    allEntities.insert(allEntities.end(), obstacles.begin(), obstacles.end());
    allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
    allEntities.insert(allEntities.end(), projectiles.begin(), projectiles.end());

    quadtree->clear();
    for (auto entity : allEntities) {
        quadtree->insert(entity);
    }

    vector<Entity*> nearbyEntities;
    quadtree->retrieveNearBy(nearbyEntities, player);
    
    for (auto other : nearbyEntities) {
        CollisionMediator::handleCollision(player, other);
    }
}

void CollisionHandler::handleEnemiesCollision(vector<Enemy *> &enemies, vector<StationaryEntity *> &obstacles, vector<Projectile *> &projectiles)
{
    vector<Entity*> allEntities;
    //allEntities.insert(allEntities.end(), obstacles.begin(), obstacles.end());
    allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
    allEntities.insert(allEntities.end(), projectiles.begin(), projectiles.end());

    quadtree->clear();
    for (auto entity : allEntities) {
        quadtree->insert(entity);
        if (entity->getType() == EntityType::Projectile) {
            //cout << "One projectile\n";
        }
    }

    for (auto enemy : enemies) {
        vector<Entity*> nearbyEntities;
        quadtree->retrieveNearBy(nearbyEntities, enemy);

        for (auto other : nearbyEntities) {
            // if (other->getType() == EntityType::Projectile) {
            //     cout << "One projectile nearby\n";
            // }
            if (enemy != other && enemy->getBoundingBox().intersects(other->getBoundingBox()))
                CollisionMediator::handleCollision(enemy, other);
        }
    }
}
