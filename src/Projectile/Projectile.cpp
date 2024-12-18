#include "Projectile/Projectile.h"

Projectile::Projectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float destroyedAfter, float damage)
        : MovingEntity(startPos),
          sprite(&ProjectileFlyweightFactory::getProjectileImg(type).getSprite()),
          direction(direction),
          move_speed(speed),
          destroyedAfter(destroyedAfter),
          totalExistedTime(0.f),
          markedDelete(false),
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

void Projectile::update(float deltaTime) 
{   
    this->totalExistedTime += deltaTime;
    this->updateAnimation(deltaTime);
    this->updateMovement(deltaTime);
    if (totalExistedTime >= destroyedAfter)
        markDelete();
}

void Projectile::draw(sf::RenderWindow* window) {
    this->sprite->setPosition(position);
    this->sprite->setTextureRect(animation.uvRect);
    window->draw(*sprite);
    this->drawBoundingBox(window);
    //cout << "Drawn bbox" << endl;
}

void Projectile::move(sf::Vector2f movement) {
    //cout << "Projectile::move with movement: " << movement.x << " " << movement.y << endl;
    this->position += movement;
    this->moveBoundingBox(movement);
    // cout << "Bouding box: " << this->boundingBox.left << " " << this->boundingBox.top << " "
    //     << this->boundingBox.width << " " << this->boundingBox.height << endl;
    //sprite.setPosition(position);
}

bool Projectile::isMarkedDelete() 
{
    //cout << "Total time: " << totalExistedTime << endl;
    return this->markedDelete;
}

float Projectile::getDamage()
{
    return this->damage;
}
void Projectile::markDelete() {
    this->markedDelete = true;
}