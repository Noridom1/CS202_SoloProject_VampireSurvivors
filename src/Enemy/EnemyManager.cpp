#include "Enemy/EnemyManager.h"
#include <random>
#include <cmath>
#include "GUI/DamageTextManager.h"
#include "Pickups/PickupManager.h"

bool EnemyManager::isEnding = false;
float EnemyManager::spawningTime = 2.5f;
float EnemyManager::totalTime = 0.f;
float EnemyManager::elapsedTime = 0.f;
int EnemyManager::maxNumEnemies = 15;
int EnemyManager::numEnemies = 0; 
float EnemyManager::timeScale = 1.f;
const float EnemyManager::minSpawningDist = 200.f;
const float EnemyManager::maxSpawningDist = 1500.f;
const float EnemyManager::minSpawningTime = 0.3f;
float EnemyManager::bossSpawningTimer = 0.f;


EnemyManager::~EnemyManager()
{   
    reset();
    if (this->difficultyStrategy)
        delete this->difficultyStrategy;
}

EnemyManager &EnemyManager::getInstance()
{
    static EnemyManager instance;
    return instance;
}

void EnemyManager::addDamageTextManager(DamageTextManager *dtManager) {

    this->damageTextManager = dtManager;
}

void EnemyManager::addSoundManager(SoundManager *soundManager)
{
    this->soundManager = soundManager;
}

void EnemyManager::update(float deltaTime, sf::Vector2f playerPosition)
{  
    if (!isEnding) {
        totalTime += deltaTime;
        elapsedTime += deltaTime;
        bossSpawningTimer += deltaTime;

        timeScale = 1 + static_cast<int>(totalTime / 30.f);
        float bossSpawningTime = difficultyStrategy->getBossSpawningTime();
        spawningTime = difficultyStrategy->getSpawningTime(totalTime);
        maxNumEnemies = difficultyStrategy->getMaxEnemies(totalTime);
        float enemyStrengthMultiplier = difficultyStrategy->getEnemyStrengthMultiplier(totalTime);
        vector<EnemyType> enemiesPool = difficultyStrategy->getEnemyPool();
        //cout << timeScale << endl;

        //spawningTime = max(1.f - (timeScale - 1) / 10.f, minSpawningTime);
        
        //maxNumEnemies += static_cast<int> ((timeScale - 1) * 15);

        if (elapsedTime >= spawningTime) {
            elapsedTime -= spawningTime;
            if (numEnemies < maxNumEnemies) {
                // Randomly select the distance within the min and max range
                float distance = minSpawningDist + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (maxSpawningDist - minSpawningDist));

                // Randomly select the angle between 0 and 2π
                float pi = 2 * static_cast<float>(acos(0));
                float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * pi;

                // Convert polar coordinates (distance, angle) to Cartesian coordinates (x, y)
                sf::Vector2f spawningPos;
                spawningPos.x = playerPosition.x + distance * cos(angle);
                spawningPos.y = playerPosition.y + distance * sin(angle);

                // Get the random enemy type and spawn the enemy
                EnemyType type = getRandomEnemyType(enemiesPool);
                spawnEnemy(type, spawningPos, enemyStrengthMultiplier);
            }
        }
        if (bossSpawningTimer >= bossSpawningTime) {
            bossSpawningTimer -= bossSpawningTime;
            float distance = minSpawningDist + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (maxSpawningDist - minSpawningDist));

            float pi = 2 * static_cast<float>(acos(0));
            float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * pi;

            sf::Vector2f spawningPos;
            spawningPos.x = playerPosition.x + distance * cos(angle);
            spawningPos.y = playerPosition.y + distance * sin(angle);

            vector<EnemyType> bosses = difficultyStrategy->getBosses();
            EnemyType type = getRandomEnemyType(bosses);
            spawnEnemy(type, spawningPos, enemyStrengthMultiplier);
            cout << "Spawned Boss\n";
        }
    }
    for (auto enemy : enemies) {
        enemy->update(deltaTime, playerPosition);
    }
}

void EnemyManager::draw(sf::RenderWindow *window)
{
    for (auto enemy : enemies) {
        enemy->draw(window);
    }
}

void EnemyManager::spawnRandomly(EnemyType type, sf::Vector2f playerPos, float strengthMultiplier)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 randomEngine(seed);  // Mersenne Twister engine
    std::uniform_real_distribution<float> dist(-1.f, 1.f);  // Random float between -1 and 1

    // Use random engine to generate random positions around the player
    const float spawnRadius = 1000.f;
    sf::Vector2f spawnPos;

    // Generate random offset
    spawnPos.x = playerPos.x + dist(randomEngine) * spawnRadius;
    spawnPos.y = playerPos.y + dist(randomEngine) * spawnRadius;
    spawnEnemy(type, spawnPos, strengthMultiplier);
}

void EnemyManager::spawnEnemy(EnemyType type, sf::Vector2f spawnPosition, float strengthMultiplier)
{   
    cout << "EnemyManager::spawnEnemy\n";
    Enemy* newEnemy = EnemyFactory::createEnemy(type, spawnPosition, strengthMultiplier);
    if (newEnemy) {
        newEnemy->addObserver(this->damageTextManager);
        newEnemy->addObserver(this->soundManager);
        this->enemies.push_back(newEnemy);
        this->numEnemies++;
    }
}

vector<Enemy *>& EnemyManager::getEnemies()
{
    return enemies;
}

EnemyType EnemyManager::getRandomEnemyType(const std::vector<EnemyType>& enemyPool)
{
    cout << "EnemyManager::getRandomEnemyType\n";

    // Create a random number generator with a seed based on the system time
    std::random_device rd;
    std::mt19937 gen(rd());

    // Uniform distribution to select a random index between 0 and size of enemyPool - 1
    std::uniform_int_distribution<int> dist(0, enemyPool.size() - 1);

    // Get the random index
    int randomIndex = dist(gen);

    // Return the enemy type corresponding to the random index in the pool
    return enemyPool[randomIndex];
}

PickupType EnemyManager::chooseRandomPickup(EnemyType enemyType)
{
    cout << "EnemyManager::chooseRandomPickup\n";
    std::vector<int> weights = difficultyStrategy->getPickupDistribution();

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    int randomIndex = dist(gen);
    return static_cast<PickupType>(randomIndex);
}

int EnemyManager::getNumEnemies()
{
    return numEnemies;
}
void EnemyManager::onGameWin()
{   
    isEnding = true;
    for (auto enemy : enemies) {
        enemy->takeDamage(enemy->getCurHP());
    }
}

void EnemyManager::cleanup()
{
    for (auto it = enemies.begin(); it != enemies.end();) {
        if ((*it)->isMarkedForDelete()) {
            PickupType type = chooseRandomPickup((*it)->getEnemyType());
            PickupManager::getInstance().spawnPickup(type, (*it)->getPosition(), 20.f, timeScale);
            if ((*it)->isBoss()) {
                PickupManager::getInstance().spawnPickup(PickupType::Chest, (*it)->getPosition(), 30.f, timeScale);
            }
            delete *it;
            it = enemies.erase(it);
            --numEnemies;
        } else {
            ++it;
        }
    }
}

void EnemyManager::reset()
{
    for (auto enemy : enemies)
        delete enemy;

    enemies.clear();

    EnemyManager::isEnding = false;
    EnemyManager::spawningTime = 2.5f;
    EnemyManager::totalTime = 0.f;
    EnemyManager::elapsedTime = 0.f;
    EnemyManager::maxNumEnemies = 10;
    EnemyManager::numEnemies = 0; 
    EnemyManager::timeScale = 1.f;
    bossSpawningTimer = 0.f;

    damageTextManager = nullptr; // Or delete if it's owned
    soundManager = nullptr;

    cout << "deleted enmies\n";
    cout << "EnemyManager::reset()\n";
}

void EnemyManager::setStage(int stage)
{
    cout << "Setting stage difficulty\n";
    switch (stage) {
        case 0:
            difficultyStrategy = new Stage1Difficulty();
            cout << "Stage 1\n";
            break;
        case 1:
            difficultyStrategy = new Stage2Difficulty();
            cout << "Stage 2\n";
            break;
        case 2:
            difficultyStrategy = new Stage3Difficulty();
            cout << "Stage 3\n";
            break;
        default:
            difficultyStrategy = new Stage1Difficulty();
    }
}

float EnemyManager::getWinningTime()
{
    return this->difficultyStrategy->getWinningTime();
}
