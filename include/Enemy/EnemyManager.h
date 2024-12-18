#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "EnemyFactory.h"

class EnemyManager {
public:
    // Delete copy constructor and assignment operator
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;

    // Destructor
    ~EnemyManager();

    // Get singleton instance
    static EnemyManager& getInstance();

    // Update all enemies
    void update(float deltaTime, sf::Vector2f playerPosition);

    // Draw all enemies
    void draw(sf::RenderWindow* window);

    void spawnRandomly(EnemyType type, sf::Vector2f playerPos);

    // Spawn a new enemy
    void spawnEnemy(EnemyType type, sf::Vector2f spawnPosition);

    vector<Enemy*>& getEnemies();

    // Clean up enemies that are no longer active
    void cleanup();

private:
    // Private constructor
    EnemyManager() {}

    // List of active enemies
    std::vector<Enemy*> enemies;
};

#endif // ENEMY_MANAGER_H
