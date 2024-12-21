#include "Entity/MovingEntity.h"

void MovingEntity::moveBoundingBox(sf::Vector2f movement)
{
    boundingBox.left += movement.x;
    boundingBox.top += movement.y;
}