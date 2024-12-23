#include "Enemy/EnemyManager.h"
#include <random>
#include <cmath>
#include "GUI/DamageTextManager.h"
#include "Pickups/PickupManager.h"

float EnemyManager::spawningTime = 4.f;
float EnemyManager::totalTime = 0.f;
float EnemyManager::elapsedTime = 0.f;
int EnemyManager::maxNumEnemies = 10;
int EnemyManager::numEnemies = 0; 
float EnemyManager::timeScale = 1.f;
const float EnemyManager::minSpawningDist = 200.f;
const float EnemyManager::maxSpawningDist = 1500.f;
const float EnemyManager::minSpawningTime = 0.3f;

EnemyManager::~EnemyManager()
{   
    reset();
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
    totalTime += deltaTime;
    elapsedTime += deltaTime;

    timeScale = 1 + static_cast<int>(totalTime) / 45;

    //cout << timeScale << endl;

    spawningTime = max(1.f - (timeScale - 1) / 10.f, minSpawningTime);
    
    maxNumEnemies += static_cast<int> ((timeScale - 1) * 10);

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
            EnemyType type = getRandomEnemyType();
            spawnEnemy(type, spawningPos);
        }

    }
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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 randomEngine(seed);  // Mersenne Twister engine
    std::uniform_real_distribution<float> dist(-1.f, 1.f);  // Random float between -1 and 1

    // Use random engine to generate random positions around the player
    const float spawnRadius = 1000.f;
    sf::Vector2f spawnPos;

    // Generate random offset
    spawnPos.x = playerPos.x + dist(randomEngine) * spawnRadius;
    spawnPos.y = playerPos.y + dist(randomEngine) * spawnRadius;
    spawnEnemy(type, spawnPos);
}

void EnemyManager::spawnEnemy(EnemyType type, sf::Vector2f spawnPosition)
{   
    Enemy* newEnemy = EnemyFactory::createEnemy(type, spawnPosition, timeScale);
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

EnemyType EnemyManager::getRandomEnemyType()
{
    // Random number generator
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(EnemyType::Microwave));

    // Get a random index and return the corresponding enum value
    int randomIndex = dist(gen);
    return static_cast<EnemyType>(randomIndex);
}

PickupType EnemyManager::chooseRandomPickup(EnemyType enemyType)
{
    std::random_device rd;
    std::mt19937 gen{rd()};  // Random number generator

    vector<int> weights;
    // Adjust the weights based on the enemy type
    switch (enemyType) {
        case EnemyType::Demon:
            // For Basic enemies, maybe you want ExpGem to be more likely
            weights = {0, 0, 100};  // ExpGem has 50% chance, Chicken 30%, Chest 20%
            break;
        default:
            weights = {95, 5, 0};  // Equal chances by default
            break;
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());

    // Randomly choose the PickupType based on the distribution
    int randomIndex = dist(gen);

    // Map the index to the corresponding PickupType
    switch (randomIndex) {
        case 0: return PickupType::ExpGem;
        case 1: return PickupType::Chicken;
        case 2: return PickupType::Chest;
        default: return PickupType::ExpGem;  // Default case (should never be reached)
    }
}

void EnemyManager::cleanup()
{
    for (auto it = enemies.begin(); it != enemies.end();) {
        if ((*it)->isMarkedForDelete()) {
            PickupType type = chooseRandomPickup((*it)->getEnemyType());
            PickupManager::getInstance().spawnPickup(type, (*it)->getPosition(), 20.f, timeScale);
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

    EnemyManager::spawningTime = 4.f;
    EnemyManager::totalTime = 0.f;
    EnemyManager::elapsedTime = 0.f;
    EnemyManager::maxNumEnemies = 10;
    EnemyManager::numEnemies = 0; 
    EnemyManager::timeScale = 1.f;

    damageTextManager = nullptr; // Or delete if it's owned
    soundManager = nullptr;

    cout << "deleted enmies\n";
    cout << "EnemyManager::reset()\n";
}
