#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "EnemyFactory.h"
#include "GUI/DamageTextManager.h"
#include "Sound/SoundManager.h"
#include "Stages/StageDifficultyStrategy.h"

enum class PickupType;

class DamageTextManager;

class EnemyManager {
public:
    // Delete copy constructor and assignment operator
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;

    // Destructor
    ~EnemyManager();

    // Get singleton instance
    static EnemyManager& getInstance();

    void addDamageTextManager(DamageTextManager *dtManager);
    
    void addSoundManager(SoundManager *soundManager);

    // Update all enemies
    void update(float deltaTime, sf::Vector2f playerPosition);

    // Draw all enemies
    void draw(sf::RenderWindow* window);

    void spawnRandomly(EnemyType type, sf::Vector2f playerPos, float strengthMultiplier);

    // Spawn a new enemy
    void spawnEnemy(EnemyType type, sf::Vector2f spawnPosition, float strengthMultiplier);

    vector<Enemy*>& getEnemies();

    EnemyType getRandomEnemyType(const std::vector<EnemyType>& enemyPool);

    PickupType chooseRandomPickup(EnemyType enemyType);

    int getNumEnemies();

    void onGameWin();
    // Clean up enemies that are no longer active
    void cleanup();

    void reset();

    void setStage(int stage);

    float getWinningTime();
private:

    // Private constructor
    EnemyManager() {}

    // List of active enemies
    std::vector<Enemy*> enemies;

    DamageTextManager* damageTextManager;
    SoundManager *soundManager;
    
    StageDifficultyStrategy* difficultyStrategy;
    static bool isEnding;  
    static float totalTime;
    static float spawningTime;
    static float elapsedTime;
    static float bossSpawningTimer;
    static int maxNumEnemies;
    static int numEnemies;
    static float timeScale;
    static const float minSpawningDist;
    static const float maxSpawningDist;
    static const float minSpawningTime;

};

#endif // ENEMY_MANAGER_H
