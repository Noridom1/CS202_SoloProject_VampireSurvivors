#ifndef COLLISIONMEDIATOR_H
#define COLLISIONMEDIATOR_H

#include <SFML/Graphics.hpp>
#include <Entity/Entity.h>
#include <Player.h>
#include <Projectile/Projectile.h>
#include "Entity/StationaryEntity.h"
#include "Enemy/Enemy.h"
#include "Pickups/Pickup.h"

class CollisionMediator
{
public:
    CollisionMediator(/* args */);
    ~CollisionMediator();

    static void handleCollision(Entity* entity1, Entity* entity2);

private:
    //void handlePlayerEnemyCollision(Player* player, Enemy* projectile);
    static void handlePlayerObjectCollision(Player* player, StationaryEntity* object);
    
    static void handlePlayerProjectileCollision(Player* player, Projectile* Projectile);

    static void handlePlayerEnemyCollision(Player* player, Enemy* enemy);

    static void handleEnemyProjectileCollision(Enemy* enemy, Projectile* projectile);

    static void handleEnemiesCollision(Enemy *enemy1, Enemy *enemy2);

    static void handleEnemyObjectCollision(Enemy *enemy, StationaryEntity* object);
    
    static void handlePlayerPickupCollision(Player *player, Pickup *pickup);

    static bool handleCollisionWithPush(Entity* entity1, Entity* entity2, float push, float overlap_x = 0.f, float overlap_y = 0.f);
    
    static std::unordered_map<Enemy*, sf::Clock> playerDamageTimers; // Tracks time for each enemy.
    static const float damageInterval;

    static bool checkCircleRectCollision(sf::CircleShape &circle, sf::FloatRect &rect);
};


#endif