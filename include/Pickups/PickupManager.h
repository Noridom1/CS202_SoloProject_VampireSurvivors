#ifndef PICKUPMANAGER_H
#define PICKUPMANAGER_H

#include "Pickups/Pickup.h"
#include "Pickups/PickupFactory.h"

class SoundManager;
class GameplayGUIManager;

class PickupManager {
public:
    PickupManager(const PickupManager&) = delete;
    PickupManager& operator=(const PickupManager&) = delete;

    static PickupManager& getInstance();

    void spawnPickup(PickupType type, sf::Vector2f pos, float lifetime, float timeScale);

    void update(float deltaTime, Player *player);

    void draw(sf::RenderWindow *window);

    void addSoundManager(SoundManager *soundManager);

    void addGUIManager(GameplayGUIManager *gpGUIManager);

    void cleanUp();

private:
    PickupManager() {}

private:
    vector<Pickup*> pickups;
    int numPickups;

    SoundManager *soundManager;
    GameplayGUIManager *gpGUIManager;
};

#endif