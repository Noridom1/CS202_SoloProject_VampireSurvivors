#include "Projectile/KingBibleProjectile.h"
#include <cmath>

KingBibleProjectile::KingBibleProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifetime, float damage) :
    Projectile(ProjectileType::KingBible, startPos, direction, speed, lifetime, damage), angle(0.f), orbitRadius(100.f),
    previousHalfCycle(-1)
{
    this->setBoundingBox();
}

void KingBibleProjectile::updateMovement( float deltaTime, Player *player)
{   
    const float M_PI = 2 * acos(0);
    float angular_speed = this->move_speed; // Angular speed in radians per second
    this->angle += angular_speed * deltaTime;

    // Keep the angle within the range [0, 2π] for numerical stability.
    if (this->angle >= 2 * M_PI)
        this->angle -= 2 * M_PI;    

    int currentHalfCycle = (this->angle < M_PI) ? 0 : 1;

    // If the half-cycle changes, clear the hitEnemies vector.
    if (currentHalfCycle != this->previousHalfCycle) {
        hitEnemies.clear();
        this->previousHalfCycle = currentHalfCycle;
    }
    // Get the current player's position.
    sf::Vector2f playerPosition = player->getPosition();

    // Compute the target position of the projectile in the circular orbit.
    sf::Vector2f targetPosition;
    targetPosition.x = playerPosition.x + orbitRadius * std::cos(this->angle);
    targetPosition.y = playerPosition.y + orbitRadius * std::sin(this->angle);

    // Calculate the movement offset required to reach the target position.
    sf::Vector2f offset = targetPosition - this->position;

    // Use the move function to update the position, which handles both sprite and bounding box.
    this->move(offset);
}

void KingBibleProjectile::setBoundingBox()
{
    float width = 12.f;
    float height = 18.f;
    this->boundingBox = sf::FloatRect(
        this->position.x - width / 2.f + 12.f,
        this->position.y - height / 2.f + 12.f,
        width,
        height
    );
}

ProjectileCaster KingBibleProjectile::getCaster()
{
    return ProjectileCaster::PLayer;
}
