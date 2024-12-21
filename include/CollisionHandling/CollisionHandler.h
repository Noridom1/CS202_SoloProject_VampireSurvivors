#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Enemy/Enemy.h"
#include "Player.h"
#include "Entity/StationaryEntity.h"
#include "Projectile/Projectile.h"
#include "Quadtree.h"


class CollisionHandler {
public:

    CollisionHandler(sf::FloatRect bound);
    ~CollisionHandler();

    //static void handleEnemiesOverlap(vector<Enemy*> &enemies);

    //void handlePlayerObstacles(Player* player, vector<StationaryEntity*> &obstacles);

    //void handlePlayerEnemies(Player *player, vector<Enemy*> &enemies);

    //void handleEnemiesObstacles(vector<Enemy*> &enemies, vector<StationaryEntity*> &obstacles);
    
    //void handleProjectilesEnemies(vector<Projectile*> &projectiles, vector<Enemy*> &enemies);

    void handlePlayerCollision(Player* player, vector<StationaryEntity*> &obstacles, vector<Enemy*> &enemies, vector<Projectile*>& projectile);

    void handleEnemiesCollision(vector<Enemy*> &enemies, vector<StationaryEntity*> &obstacles, vector<Projectile*> &projectiles);

    void updateQuadtrees(vector<Enemy*> &enemies, vector<StationaryEntity*> &obstacles, vector<Projectile*> &projectiles);


private:
    // Quadtree obstaclesQuadtree;
    // Quadtree enemiesQuadtree;
    // Quadtree projectilesQuadtree;
    Quadtree *quadtree;
};

#endif