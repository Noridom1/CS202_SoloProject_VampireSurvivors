#include "Entity/Entity.h"

sf::FloatRect& Entity::getBoundingBox()
{
    return this->boundingBox;
}

sf::Vector2f Entity::getPosition()
{
    return this->position;
}

void Entity::drawBoundingBox(sf::RenderWindow *window)
{
    //Visualize bounding box:
    //cout << "Bounding box: " << this->boundingBox.left << " " << this->boundingBox.top
    //   << " " << this->boundingBox.width << " " << this->boundingBox.height << endl;
    sf::RectangleShape bbox(sf::Vector2f(this->boundingBox.width, this->boundingBox.height));
    bbox.setFillColor(sf::Color::Transparent);
    bbox.setOutlineColor(sf::Color::Green);
    bbox.setOutlineThickness(1.0f);
    bbox.setPosition(this->boundingBox.left, this->boundingBox.top);
    window->draw(bbox);
}

sf::Vector2f Entity::getHalfSize()
{
    return sf::Vector2f(boundingBox.width / 2.f, boundingBox.height / 2.f);
}
