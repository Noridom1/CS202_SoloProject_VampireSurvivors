#include "Pickups/PickupManager.h"
#include "Pickups/PickupFactory.h"


PickupManager &PickupManager::getInstance()
{
    static PickupManager instance;
    return instance;
}

void PickupManager::spawnPickup(PickupType type, sf::Vector2f pos, float lifetime, float timeScale)
{
    pickups.push_back(PickupFactory::createPickup(type, pos, lifetime, timeScale));
    cout << "Spawned a pickup\n";
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

void PickupManager::cleanUp()
{
    for (auto it = pickups.begin(); it != pickups.end();) {
        if ((*it)->isMarkedForDelete()) {
            delete *it;
            it = pickups.erase(it);
            --numPickups;
            cout << "Cleaned up a pickup\n";
        } else {
            ++it;
        }
    }
}
