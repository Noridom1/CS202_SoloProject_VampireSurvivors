#include "Entity/MovingEntity.h"

void MovingEntity::moveBoundingBox(sf::Vector2f movement)
{
    boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
}