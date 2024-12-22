#ifndef CHEST_H
#define CHEST_H

#include "Pickups/Pickup.h"
#include "GUI/Events.h"

class Chest : public Pickup {

public:
    Chest(sf::Vector2f pos, float lifeTime, float timeScale) : Pickup(PickupType::Chest, pos, lifeTime, timeScale) {
        setBoundingBox();
    }
    ~Chest() {}

    void setBoundingBox() override {
        float width = 15.f;
        float height = 10.f;
        this->boundingBox = sf::FloatRect(
            this->position.x - width / 2.f,
            this->position.y - height / 2.f,
            width,
            height
        );
    }

    void applyEffect(Player *player) override {
        const PickupChest pickupChestEvent;
        cout << "Notifying PickupChest event\n";
        notify(&pickupChestEvent);
    }

    PickupType getPickUpType() const override { return PickupType::Chest; }

private:
};

#endif