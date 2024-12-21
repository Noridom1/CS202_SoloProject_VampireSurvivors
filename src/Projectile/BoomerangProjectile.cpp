#include "Projectile/BoomerangProjectile.h"

BoomerangProjectile::BoomerangProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime, float damage) : 
    Projectile(ProjectileType::Boomerang, startPos, direction, speed, lifeTime, damage), acceleration(-750.0f),
    reversed(false)
{
    this->setBoundingBox();
    this->sprite->setScale(0.6f, 0.6f);
    this->sprite->setOrigin(this->animation.uvRect.width / 2.f, this->animation.uvRect.height / 2.f);
}

void BoomerangProjectile::updateMovement(float deltaTime, Player *player)
{
    if (move_speed < 0.f) {
        if (!reversed) {
            reversed = true;
            this->hitEnemies.clear();
            acceleration = -1000.0f;
        }
        direction = this->getPosition() - player->getPosition();
    }
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (reversed && magnitude < 10.f) {
        this->markForDelete();
    }
    
    if (magnitude != 0.0f)
        direction /= magnitude;

    move_speed += acceleration * deltaTime;

    this->move(direction * move_speed * deltaTime);
}

void BoomerangProjectile::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 20, 20);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
}

ProjectileCaster BoomerangProjectile::getCaster()
{
    return ProjectileCaster::PLayer;
}
// void BoomerangProjectile::update(float deltaTime)
// {
//         //std::cout << "Boomerang::update()\n";
//         Projectile::updateAnimation(deltaTime);
//         updateMovement(deltaTime, map);
// }
