#include "Projectile/ExplodingProjectile.h"

using namespace std;

ExplodingProjectile::ExplodingProjectile(sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime, float damage) :
    Projectile(ProjectileType::ExplodingProjectile, startPos, direction, speed, lifeTime, damage),
    explodingRadius(35.f), row(0u),
    effectiveArea(explodingRadius), playerExploded(false), hasExploded(false)
{
    this->setBoundingBox();
    this->sprite->setScale(1.5f, 1.5f);
    this->sprite->setOrigin(this->animation.uvRect.width / 2.f, this->animation.uvRect.height / 2.f);
    effectiveArea.setOrigin(explodingRadius / 2.f, explodingRadius / 2.f);
}

void ExplodingProjectile::updateMovement(float deltaTime, Player *player)
{
    this->animation.update(row, deltaTime, true);
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude != 0.0f)
        direction /= magnitude;

    this->move(direction * move_speed * deltaTime);
}

void ExplodingProjectile::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 13.f, 13.f);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
}

void ExplodingProjectile::update(float deltaTime, Player *player)
{
    this->totalExistedTime += deltaTime;
    if ((totalExistedTime >= lifeTime || this->isMarkedHit()) && !hasExploded)
        explode(player);

    if (row == 1) {
        updateExplosion(deltaTime);
    }
    else {
        updateMovement(deltaTime, player);
    }
}

void ExplodingProjectile::markHit()
{
    this->markedHit = true;
}

void ExplodingProjectile::updateExplosion(float deltaTime)
{
    this->animation.update(row, deltaTime, true);
    if (animation.isFinished(row)) {
        markForDelete();
    }
}

ProjectileCaster ExplodingProjectile::getCaster()
{
    return ProjectileCaster::Enemy;
}
void ExplodingProjectile::explode(Player *player)
{   
    this->effectiveArea.setPosition(this->position);

    if (checkCollisionWith(player->getBoundingBox())) {
        player->takeDamage(this->damage + 10.f);
    }
    hasExploded = true;
    row = 1;
}

bool ExplodingProjectile::checkCollisionWith(const sf::FloatRect &rect)
{
    sf::Vector2f center = this->position;
    // Find the nearest point on the rectangle to the circle's center
    float nearestX = max(rect.left, min(center.x, rect.left + rect.width));
    float nearestY = max(rect.top, min(center.y, rect.top + rect.height));

    // Calculate the distance between the circle's center and the nearest point
    float deltaX = center.x - nearestX;
    float deltaY = center.y - nearestY;

    // Check if the distance is less than or equal to the circle's radius
    return (deltaX * deltaX + deltaY * deltaY) <= (explodingRadius * explodingRadius);
}
