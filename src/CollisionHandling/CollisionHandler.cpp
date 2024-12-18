#include "CollisionHandling/CollisionHandler.h"
#include "CollisionHandling/CollisionMediator.h"

// void CollisionHandler::handleEnemiesOverlap(vector<Enemy *> &enemies)
// {
//     for (auto enemy : enemies) {
//         vector<Entity*> nearbyEnemies;
//         enemiesQuadtree.retrieveNearBy(nearbyEnemies, enemy);

//         for (auto other : nearbyEnemies) {
//             CollisionMediator::handleCollision(enemy, other);
//         }
//     }
// }]

CollisionHandler::CollisionHandler(sf::FloatRect bound)
    : quadtree(new Quadtree(0, bound)) 
{

}

CollisionHandler::~CollisionHandler()
{
    delete quadtree;
}

// void CollisionHandler::handlePlayerObstacles(Player *player, vector<StationaryEntity *> &obstacles)
// {
//     vector<Entity*> nearbyObstacles;
//     obstaclesQuadtree.retrieveNearBy(nearbyObstacles, player);

//     for (auto obstacle : nearbyObstacles) {
//         CollisionMediator::handleCollision(player, obstacle);
//     }
// }

// void CollisionHandler::handlePlayerEnemies(Player *player, vector<Enemy *> &enemies)
// {
//     vector<Entity*> nearbyEnemies;
//     obstaclesQuadtree.retrieveNearBy(nearbyEnemies, player);

//     for (auto enemy : nearbyEnemies) {
//         CollisionMediator::handleCollision(player, enemy);
//     }
// }

// void CollisionHandler::handlePlayerCollision(Player *player, vector<StationaryEntity *> &obstacles, vector<Enemy *> &enemies)
// {
//     vector<Entity*> allEntities;
//     allEntities.insert(allEntities.end(), obstacles.begin(), obstacles.end());
//     allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());

//     quadtree.clear();
//     for (auto entity : allEntities) {
//         quadtree.insert(entity);
//     }

//     vector<Entity*> nearbyEntities;
//     quadtree.retrieveNearBy(nearbyEntities, player);

//     for (auto other : nearbyEntities) {
//         CollisionMediator::handleCollision(player, other);
//     }
// }

void CollisionHandler::handlePlayerCollision(Player *player, vector<StationaryEntity *> &obstacles, vector<Enemy *> &enemies, vector<Projectile *> &projectiles)
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
    allEntities.insert(allEntities.end(), obstacles.begin(), obstacles.end());
    allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
    allEntities.insert(allEntities.end(), projectiles.begin(), projectiles.end());

    quadtree->clear();
    for (auto entity : allEntities) {
        quadtree->insert(entity);
    }

    for (auto enemy : enemies) {
        vector<Entity*> nearbyEntities;
        quadtree->retrieveNearBy(nearbyEntities, enemy);

        for (auto other : nearbyEntities) {
            if (enemy != other && enemy->getBoundingBox().intersects(other->getBoundingBox()))
                CollisionMediator::handleCollision(enemy, other);
        }
    }
}

void CollisionHandler::updateQuadtrees(vector<Enemy *> &enemies, vector<StationaryEntity *> &obstacles, vector<Projectile *> &projectiles)
{
}