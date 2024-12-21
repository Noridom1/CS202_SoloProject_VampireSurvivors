#include <CollisionHandling/CollisionMediator.h>
#include "Enemy/Ghost.h"

unordered_map<Enemy*, sf::Clock> CollisionMediator::playerDamageTimers; // Tracks time for each enemy.
const float CollisionMediator::damageInterval = 1.f;

CollisionMediator::CollisionMediator(/* args */)
{
}

CollisionMediator::~CollisionMediator()
{
}

void CollisionMediator::handleCollision(Entity *entity1, Entity *entity2)
{
    if (dynamic_cast<Player*>(entity1) && dynamic_cast<StationaryEntity*>(entity2)) {
        handlePlayerObjectCollision(
            dynamic_cast<Player*>(entity1),
            dynamic_cast<StationaryEntity*>(entity2)
        );
    } 

    else if (dynamic_cast<Enemy*>(entity1) && dynamic_cast<Projectile*>(entity2)) {
        handleEnemyProjectileCollision(
            dynamic_cast<Enemy*>(entity1), 
            dynamic_cast<Projectile*>(entity2)
        );
    } 

    else if (dynamic_cast<Player*>(entity1) && dynamic_cast<Enemy*>(entity2)) {
        handlePlayerEnemyCollision(
            dynamic_cast<Player*>(entity1), 
            dynamic_cast<Enemy*>(entity2)
        );
    }

    else if (dynamic_cast<Player*>(entity1) && dynamic_cast<Projectile*>(entity2)) {
        handlePlayerProjectileCollision(
            dynamic_cast<Player*>(entity1),
            dynamic_cast<Projectile*>(entity2)
        );
    }

    else if (dynamic_cast<Enemy*>(entity1) && dynamic_cast<Enemy*>(entity2)) {
        handleEnemiesCollision (
            dynamic_cast<Enemy*>(entity1),
            dynamic_cast<Enemy*>(entity2)
        );
    }

    else if (dynamic_cast<Enemy*>(entity1) && dynamic_cast<StationaryEntity*>(entity2)) {
        handleEnemyObjectCollision(
            dynamic_cast<Enemy*>(entity1),
            dynamic_cast<StationaryEntity*>(entity2)
        );
    }

    else if (dynamic_cast<Player*>(entity1) && dynamic_cast<Pickup*>(entity2)) {
        handlePlayerPickupCollision(
            dynamic_cast<Player*>(entity1),
            dynamic_cast<Pickup*>(entity2)
        );
    }
}   

void CollisionMediator::handlePlayerObjectCollision(Player *player, StationaryEntity *object)
{
    //cout << "Handling Player-Object collision\n";
    handleCollisionWithPush(player, object, 0.f);
}

void CollisionMediator::handlePlayerProjectileCollision(Player *player, Projectile *projectile)
{
    if (projectile->getCaster() == ProjectileCaster::Enemy && !projectile->isMarkedHit() && projectile->getBoundingBox().intersects(player->getBoundingBox())) {
        player->takeDamage(projectile->getDamage());
        projectile->markHit();
        //cout << "Projectile hit player\n";
    }
}

void CollisionMediator::handlePlayerEnemyCollision(Player *player, Enemy *enemy)
{  
    if (!handleCollisionWithPush(player, enemy, 0.5f, 10.f, 15.f)) {
        playerDamageTimers.erase(enemy);
        return;
    }

    if (playerDamageTimers.find(enemy) == playerDamageTimers.end()) {
        // First-time collision: deal damage and start the clock.
        player->takeDamage(enemy->getDamage());
        playerDamageTimers[enemy].restart();
    } 

    else {
        // Check if enough time has elapsed.
        if (playerDamageTimers[enemy].getElapsedTime().asSeconds() >= damageInterval) {
            player->takeDamage(enemy->getDamage());
            playerDamageTimers[enemy].restart(); // Reset the timer for this enemy.
        }
    }
}

void CollisionMediator::handleEnemyProjectileCollision(Enemy *enemy, Projectile *projectile)
{   
    //cout << "handleEnemyProjectileCollision\n";
    if (projectile->getCaster() == ProjectileCaster::PLayer && projectile->getBoundingBox().intersects(enemy->getBoundingBox())) {
        projectile->updateHitEnemies(enemy);
        //cout << "projectile hit enemy\n";
    }
    //projectile->markDelete();
}

void CollisionMediator::handleEnemiesCollision(Enemy *enemy1, Enemy *enemy2)
{
    handleCollisionWithPush(enemy1, enemy2, 0.5f, 10.f, 15.f);
    //cout << "Handle enemy-enemy collision\n";
}

void CollisionMediator::handleEnemyObjectCollision(Enemy *enemy, StationaryEntity *object)
{
    handleCollisionWithPush(enemy, object, 0.f);
}

void CollisionMediator::handlePlayerPickupCollision(Player *player, Pickup *pickup)
{
    if (checkCircleRectCollision(player->getPickupArea(), pickup->getBoundingBox())) {
        pickup->switchState();
    }
}
bool CollisionMediator::handleCollisionWithPush(Entity *entity1, Entity *entity2, float push, float overlap_x, float overlap_y)
{
    sf::Vector2f firstPosition = entity1->getPosition();
    sf::Vector2f secondPosition = entity2->getPosition();
    sf::Vector2f firstHalfSize = entity1->getHalfSize();
    sf::Vector2f secondHalfSize = entity2->getHalfSize();

    //cout << "First entity's position: " << firstPosition.x << " " << firstPosition.y << endl;
    //cout << "Second entity's position: " << secondPosition.x << " " << secondPosition.y << endl;

    float deltaX = firstPosition.x - secondPosition.x;
    float deltaY = firstPosition.y - secondPosition.y;

    float intersectX = abs(deltaX) - firstHalfSize.x - secondHalfSize.x + overlap_x;
    float intersectY = abs(deltaY) - firstHalfSize.y - secondHalfSize.y + overlap_y;

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = min(1.f, max(0.f, push));
        if (intersectX > intersectY) {
            if (deltaX < 0.f) {
                entity1->move(sf::Vector2f(intersectX * (1.f - push), 0.f));
                entity2->move(sf::Vector2f(-intersectX * push, 0.f));
            }
            else {
                entity1->move(sf::Vector2f(-intersectX * (1.f - push), 0.f));
                entity2->move(sf::Vector2f(intersectX * push, 0.f));
            }
        }
        else {
            if (deltaY < 0.f) {
                entity1->move(sf::Vector2f(0.f, intersectY * (1.f - push)));
                entity2->move(sf::Vector2f(0.f, -intersectY * push));
            }
            else {
                entity1->move(sf::Vector2f(0.f, -intersectY * (1.f - push)));
                entity2->move(sf::Vector2f(0.f, intersectY * push));
            }
        }
        return true;
    }

    return false;
}

bool CollisionMediator::checkCircleRectCollision(sf::CircleShape &circle, sf::FloatRect &rect)
{
    sf::Vector2f center = circle.getOrigin();
    float radius = circle.getRadius();
    // Find the nearest point on the rectangle to the circle's center
    float nearestX = max(rect.left, min(center.x, rect.left + rect.width));
    float nearestY = max(rect.top, min(center.y, rect.top + rect.height));

    // Calculate the distance between the circle's center and the nearest point
    float deltaX = center.x - nearestX;
    float deltaY = center.y - nearestY;

    // Check if the distance is less than or equal to the circle's radius
    return (deltaX * deltaX + deltaY * deltaY) <= (radius * radius);
}
