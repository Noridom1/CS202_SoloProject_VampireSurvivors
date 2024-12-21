#ifndef PICKUP_H
#define PICKUP_H

#include "Entity/MovingEntity.h"
#include "Image.h"
#include "GUI/Subject.h"
#include "Player/Player.h"

enum class PickupType {
    ExpGem,
    Chicken,
    Chest,
    MaxType,
};

class Pickup : public MovingEntity, public Subject {

enum class PickupState {
    Stationary,
    Moving,
};

public:
    Pickup(PickupType type, sf::Vector2f pos, float lifetime, float timeScale);

    ~Pickup() {};
    
    void update(float deltaTime, Player *player); 

    void updateMovement(float deltaTime) override {}

    void updateMovement(float deltaTime, Player *player);

    void move(sf::Vector2f movement) override;

    void draw(sf::RenderWindow *window);
    
    virtual void applyEffect(Player *player) = 0;

    EntityType getType() const override { return EntityType::Pickup; }

    void switchState();

    virtual PickupType getPickUpType() const = 0;



private:
    Image *img;
    PickupState state;

    float acceleration;
    float move_speed;

    float lifeTime;
    float existedTime;

};

#endif 