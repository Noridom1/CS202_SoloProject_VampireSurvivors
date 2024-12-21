#include "Projectile/Projectile.h"

Projectile::Projectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float destroyedAfter, float damage)
        : MovingEntity(startPos),
          sprite(&ProjectileFlyweightFactory::getProjectileImg(type).getSprite()),
          direction(direction),
          move_speed(speed),
          lifeTime(destroyedAfter),
          totalExistedTime(0.f),
          markedDelete(false), markedHit(false),
          damage(damage)
{
    sf::Texture& texture = ProjectileFlyweightFactory::getProjectileImg(type).getTexture();
    TexturesAnimation texture_animation = ProjectileAnimations.at(type);
    animation = Animation(&texture, texture_animation.numSprites, texture_animation.imageCount, texture_animation.switchTime);
}

void Projectile::updateAnimation(float deltaTime) 
{
    animation.update(0, deltaTime, true);
}

// void Projectile::updateMovement(float deltaTime, Map *map) {
//     float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//     if (magnitude != 0.0f) {
//         direction /= magnitude;
//     }
//     this->move(direction * move_speed * deltaTime, map);
// }

void Projectile::update(float deltaTime, Player* player) 
{   
    this->totalExistedTime += deltaTime;
    this->updateAnimation(deltaTime);
    this->updateMovement(deltaTime, player);
    if (totalExistedTime >= lifeTime)
        markForDelete();
}

void Projectile::draw(sf::RenderWindow* window) {
    this->sprite->setPosition(position);
    this->sprite->setTextureRect(animation.uvRect);
    window->draw(*sprite);
    this->drawBoundingBox(window);
}

void Projectile::move(sf::Vector2f movement) {
    this->position += movement;
    this->moveBoundingBox(movement);
}

void Projectile::markHit()
{
    markedHit = true;
    markForDelete();
}
bool Projectile::isMarkedHit()
{
    return this->markedHit;
}
float Projectile::getDamage()
{
    return this->damage;
}

void Projectile::updateHitEnemies(Enemy * enemy)
{   
    if (hitEnemies.find(enemy) == hitEnemies.end()) { // If not already hit.
        hitEnemies.insert(enemy); // Mark as hit.
        enemy->takeDamage(damage); // Call the enemy's takeDamage function.
    }
}