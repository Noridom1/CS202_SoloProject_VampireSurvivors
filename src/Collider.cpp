#include "Collider.h"
#include <algorithm>

using namespace std;

Collider::Collider(sf::FloatRect bbox) : bbox(bbox)
{
}

void Collider::move(float dx, float dy)
{
    this->bbox.left += dx;
    this->bbox.top += dy;
}

bool Collider::checkCollision(Collider &other, float push)
{
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = this->getPosition();
    sf::Vector2f thisHalfSize = this->getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - thisHalfSize.x - otherHalfSize.x;
    float intersectY = abs(deltaY) - thisHalfSize.y - otherHalfSize.y;

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = min(1.f, max(0.f, push));

        if (intersectX > intersectY) {
            if (deltaX > 0.f){
                this->move(intersectX * (1.f - push), 0.f);
                other.move(-intersectX * push, 0.f);
            }
            else {
                this->move(-intersectX * (1.f - push), 0.f);
                other.move(intersectX * push, 0.f);
            }
        }

        else {
            if (deltaY > 0.f){
                this->move(0.f, intersectY * (1.f - push));
                other.move(0.f, -intersectY * push);
            }
            else {
                this->move(0.f, -intersectY * (1.f - push));
                other.move(0.f, intersectY * push);
            }
        }
        return true;
    }
    return false;
}

sf::Vector2f Collider::getPosition()
{
    return sf::Vector2f(bbox.left, bbox.top) + this->getHalfSize();
}

sf::Vector2f Collider::getHalfSize()
{
    return sf::Vector2f(bbox.width / 2.0f, bbox.height / 2.0f);
}
