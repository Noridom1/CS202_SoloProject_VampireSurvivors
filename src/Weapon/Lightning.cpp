#include "Weapon/Lightning.h"
#include "CollisionHandling/Quadtree.h"
#include "GameManagement/Gameplay.h"
#include "Enemy/EnemyManager.h"
#include "Projectile/ProjectileManager.h"

Lightning::Lightning(Player *player) :
    Weapon(player, 10.f, 3.5f), numEnemyCast(2), totalTime(0.f), effectiveRadius(400.f)
{

}

void Lightning::levelUp()
{
    if (level >= maxLevel) 
        return;
    ++level;
    this->damage *= 1.2f;
    this->cooldown *= 0.85f;
    ++this->numEnemyCast;
    this->effectiveRadius += 25.f;
}

void Lightning::update(sf::RenderWindow *window, Player *player, float deltaTime)
{
    totalTime += deltaTime;
    if (totalTime >= cooldown) {
        totalTime -= cooldown;
        this->cast();
    }
}

vector<Entity*> Lightning::getRandomEnemyPos()
{
    float s = Gameplay::getMapSize();
    Quadtree* quadtree = new Quadtree(0, sf::FloatRect(0.f, 0.f, s, s));

    vector<Enemy*> enemies = EnemyManager::getInstance().getEnemies();

    for (auto enemy : enemies) {
        quadtree->insert(enemy);
    }

    vector<Entity*> nearbyEnemies;
    quadtree->retrieveInCircle(nearbyEnemies, player->getPosition(), effectiveRadius);

    int numNearby = nearbyEnemies.size();
    vector<Entity*> positions;
    for (int i = min(numNearby, numEnemyCast) - 1; i >= 0; --i) {
        positions.push_back(nearbyEnemies[i]);
    }

    delete quadtree;
    return positions;
}

WeaponType Lightning::getType() const
{
    return WeaponType::LightningRing;
}
void Lightning::cast()
{   
    vector<Entity*> positions = this->getRandomEnemyPos();
    for (auto pos : positions) {
        ProjectileManager::getInstance().spawnProjectile(ProjectileType::Lightning, pos->getPosition(), {0.f, 0.f}, 0.f, 10.f, this->damage);
    }
}
