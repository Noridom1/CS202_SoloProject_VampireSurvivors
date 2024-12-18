#include "Projectile/BoomerangProjectile.h"

BoomerangProjectile::BoomerangProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed) : 
    Projectile(ProjectileType::Boomerang, startPos, direction, speed, 5.0f, 10), acceleration(-750.0f)
{
    this->setBoundingBox();
    this->sprite->setScale(0.6f, 0.6f);
    this->sprite->setOrigin(this->animation.uvRect.width / 2.f, this->animation.uvRect.height / 2.f);
}

void BoomerangProjectile::updateMovement(float deltaTime)
{
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude != 0.0f)
        direction /= magnitude;

    move_speed += acceleration * deltaTime;

    if (move_speed < 0)
        acceleration = -1000.0f;

    this->move(direction * move_speed * deltaTime);
}

void BoomerangProjectile::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 20, 20);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
}

// void BoomerangProjectile::update(float deltaTime)
// {
//         //std::cout << "Boomerang::update()\n";
//         Projectile::updateAnimation(deltaTime);
//         updateMovement(deltaTime, map);
// }
