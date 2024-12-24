#include "Projectile/LightningProjectile.h"

LightningProjectile::LightningProjectile(sf::Vector2f startPos, float damage) :
    Projectile(ProjectileType::Lightning, startPos, {0.f, 0.f}, 0.f, 0.f, damage)
{
    this->setBoundingBox();
    
    sf::IntRect localBounds = animation.uvRect;
    sprite->setOrigin(
        localBounds.width / 2.f,
        localBounds.height / 2.f + boundingBox.height / 2.f + 5.f
    );
    this->sprite->setScale(1.5f, 2.5f);

}

void LightningProjectile::updateMovement(float deltaTime, Player *player)
{
}

void LightningProjectile::update(float deltaTime, Player *player)
{
    this->updateAnimation(deltaTime);
    if (animation.isFinished(0)) {
        markForDelete();
    }
}

void LightningProjectile::setBoundingBox()
{
    float width = 30.f;
    float height = 30.f;
    this->boundingBox = sf::FloatRect(
        this->position.x - width / 2.f,
        this->position.y - height / 2.f,
        width,
        height
    );
}

ProjectileCaster LightningProjectile::getCaster()
{
    return ProjectileCaster::PLayer;
}
