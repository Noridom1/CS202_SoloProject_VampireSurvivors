#include <CollisionHandling/CollisionMediator.h>

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

    // else if (dynamic_cast<Enemy*>(&entity1) && dynamic_cast<Projectile*>(&entity2)) {
    //     handleEnemyProjectileCollision(
    //         dynamic_cast<Enemy*>(entity1), 
    //         dynamic_cast<Projectile*>(entity2)
    //     );
    // } 

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
}

void CollisionMediator::handlePlayerObjectCollision(Player *player, StationaryEntity *object)
{
    //cout << "Handling Player-Object collision\n";
    handleCollisionWithPush(player, object, 0.f);
}

void CollisionMediator::handlePlayerProjectileCollision(Player *player, Projectile *Projectile)
{
    player->takeDamage(Projectile->getDamage());
    Projectile->markDelete();
}

void CollisionMediator::handleProjectilesCollision(Projectile *projectile1, Projectile *projectile2)
{
    handleCollisionWithPush(projectile1, projectile2, 0.5f);
}

void CollisionMediator::handlePlayerEnemyCollision(Player *player, Enemy *enemy)
{   
    handleCollisionWithPush(enemy, player, 0.f);
}
void CollisionMediator::handleEnemiesCollision(Enemy *enemy1, Enemy *enemy2)
{
    handleCollisionWithPush(enemy1, enemy2, 0.5f, 10.f, 15.f);
    //cout << "Handle enemy-enemy collision\n";
}

void CollisionMediator::handelEnemyObjectCollision(Enemy *enemy, StationaryEntity *object)
{
    handleCollisionWithPush(enemy, object, 0.f);
}

void CollisionMediator::handleCollisionWithPush(Entity *entity1, Entity *entity2, float push, float overlap_x, float overlap_y)
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
    }
}
