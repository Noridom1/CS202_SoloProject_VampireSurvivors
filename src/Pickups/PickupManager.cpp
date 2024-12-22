#include "Pickups/PickupManager.h"
#include "Pickups/PickupFactory.h"
#include "Sound/SoundManager.h"
#include "GUI/GameplayGUIManager.h"

PickupManager &PickupManager::getInstance()
{
    static PickupManager instance;
    return instance;
}

void PickupManager::spawnPickup(PickupType type, sf::Vector2f pos, float lifetime, float timeScale)
{
    Pickup *newPickup = PickupFactory::createPickup(type, pos, lifetime, timeScale);
    
    newPickup->addObserver(this->soundManager);
    newPickup->addObserver(this->gpGUIManager);

    pickups.push_back(newPickup);
}

void PickupManager::update(float deltaTime, Player *player)
{
    for (auto pickup : pickups) {
        pickup->update(deltaTime, player);
    }
}

void PickupManager::draw(sf::RenderWindow *window)
{
    for (auto pickup : pickups) {
        pickup->draw(window);
    }
}

void PickupManager::addSoundManager(SoundManager *soundManager)
{
    this->soundManager = soundManager;
}

void PickupManager::addGUIManager(GameplayGUIManager *gpGUIManager)
{
    this->gpGUIManager = gpGUIManager;
}
void PickupManager::cleanUp()
{
    for (auto it = pickups.begin(); it != pickups.end();) {
        if ((*it)->isMarkedForDelete()) {
            delete *it;
            it = pickups.erase(it);
            --numPickups;
        } else {
            ++it;
        }
    }
}
