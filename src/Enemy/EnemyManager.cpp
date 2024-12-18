#include "Enemy/EnemyManager.h"

EnemyManager::~EnemyManager()
{
    for (auto enemy : enemies)
        delete enemy;
}

EnemyManager &EnemyManager::getInstance()
{
    static EnemyManager instance;
    return instance;
}

void EnemyManager::update(float deltaTime, sf::Vector2f playerPosition)
{
    for (auto enemy : enemies) {
        enemy->update(deltaTime, playerPosition);
    }
    //cout << "There are " << enemies.size() << "enemies\n";
}

void EnemyManager::draw(sf::RenderWindow *window)
{
    for (auto enemy : enemies) {
        enemy->draw(window);
    }
}

void EnemyManager::spawnRandomly(EnemyType type, sf::Vector2f playerPos)
{
    const float spawnRadius = 1000.f;
    sf::Vector2f spawnPos;
    spawnPos.x = playerPos.x + rand() / (500.f + spawnRadius);
    spawnPos.y = playerPos.x + rand() / (500.f + spawnRadius);

    spawnEnemy(type, spawnPos);
}

void EnemyManager::spawnEnemy(EnemyType type, sf::Vector2f spawnPosition)
{
    this->enemies.push_back(EnemyFactory::createEnemy(type, spawnPosition));
    cout << "Spawn an enemy at: " << spawnPosition.x << " " << spawnPosition.y  << endl;
}

vector<Enemy *>& EnemyManager::getEnemies()
{
    return enemies;
}

void EnemyManager::cleanup()
{
    for (auto it = enemies.begin(); it != enemies.end();) {
        if ((*it)->isMarkedDelete()) {
            delete *it;
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
}
