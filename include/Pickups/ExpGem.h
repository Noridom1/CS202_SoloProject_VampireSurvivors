#ifndef EXPGEM_H
#define EXPGEM_H

#include "Pickups/Pickup.h"

class ExpGem : public Pickup {

public:
    ExpGem(sf::Vector2f pos, float lifeTime, float timeScale) 
        : Pickup(PickupType::ExpGem, pos, lifeTime, timeScale) {
        setBoundingBox();
        this->exp = 5.f * (timeScale);
    }
    ~ExpGem();

    void setBoundingBox() override {
        float width = 8.f;
        float height = 10.f;
        this->boundingBox = sf::FloatRect(
            this->position.x - width / 2.f,
            this->position.y - height / 2.f,
            width,
            height
        );
    };

    float getExp() const { return this->exp; }

    void applyEffect(Player *player) override {
        player->gainExp(this->exp);
    }

    PickupType getPickUpType() const override { return PickupType::ExpGem; }

private:
    float exp;
};

#endif