#ifndef CHICKEN_H
#define CHICKEN_H

#include "Pickups/Pickup.h"

class Chicken : public Pickup {
    
public:
    Chicken(sf::Vector2f pos, float lifeTime, float timeScale) : Pickup(PickupType::Chicken, pos, lifeTime, timeScale) {
        setBoundingBox();
        this->hpAmount = min(10.f + (timeScale - 1) * 5.f, 100.f);
    }
    ~Chicken() {}

    void setBoundingBox() override {
        float width = 12.f;
        float height = 12.f;
        this->boundingBox = sf::FloatRect(
            this->position.x - width / 2.f,
            this->position.y - height / 2.f,
            width,
            height
        );
    };

    float getHPAmount() const { return hpAmount; }

    void applyEffect(Player *player) override {
        player->loseHP(-this->hpAmount);
    }

    PickupType getPickUpType() const override { return PickupType::Chicken; }


private:
    float hpAmount;
};


#endif