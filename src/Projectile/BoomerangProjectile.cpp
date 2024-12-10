#include "Projectile/BoomerangProjectile.h"

BoomerangProjectile::BoomerangProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed) : 
        Projectile(ProjectileType::Boomerang, startPos, direction, speed), acceleration(-750.0f) {}

void BoomerangProjectile::updatePosition(float deltaTime)
{
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0.0f)
    {
        direction /= magnitude;
    }
    move_speed += acceleration * deltaTime;
    if (move_speed < 0)
    {
        acceleration = -1000.0f;
    }
    this->move(direction * move_speed * deltaTime);
}

void BoomerangProjectile::update(float deltaTime)
{
        //std::cout << "Boomerang::update()\n";
        Projectile::updateAnimation(deltaTime);
        updatePosition(deltaTime);
}
