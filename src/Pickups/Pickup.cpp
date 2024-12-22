#include "Pickups/Pickup.h"
#include "Pickups/PickupFlyweightFactory.h"
#include "GUI/Events.h"

Pickup::Pickup(PickupType type, sf::Vector2f pos, float lifetime, float timeScale)
        : MovingEntity(pos), state(PickupState::Stationary), acceleration(500.f), move_speed(120.f),
        lifeTime(lifetime), existedTime(0.f),
        img(&PickupFlyweightFactory::getPickupImg(type))
{
    this->img->getSprite().setScale(0.5f, 0.5f);
    
    sf::FloatRect bound = this->img->getSprite().getLocalBounds();
    this->img->getSprite().setOrigin(bound.left + bound.width / 2.f, bound.top + bound.height / 2.f);
}

void Pickup::update(float deltaTime, Player *player)
{
    existedTime += deltaTime;
    if (existedTime >= lifeTime && this->state != PickupState::Moving) {
        markForDelete();
    }
    updateMovement(deltaTime, player);

}

void Pickup::updateMovement(float deltaTime, Player *player)
{
    sf::Vector2f direction = player->getPosition() - this->position;

    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (this->state == PickupState::Stationary) {
        if (magnitude <= player->getPickupArea().getRadius())
            switchState();
        return;
    }

    if (magnitude <= 10.f) {
        applyEffect(player);
        player->notifyPickup();
        markForDelete();
    }

    if (magnitude) 
        direction /= magnitude;
    
    move_speed += acceleration * deltaTime;

    this->move(direction * move_speed * deltaTime);

}

void Pickup::move(sf::Vector2f movement)
{
    this->position += movement;
    moveBoundingBox(movement);
}

void Pickup::draw(sf::RenderWindow *window)
{
    img->setPosition(this->position);
    img->draw(window);
    this->drawBoundingBox(window);
}

void Pickup::switchState()
{
    this->state = PickupState::Moving;
}
