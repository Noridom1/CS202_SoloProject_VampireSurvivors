#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {

public:
    Entity() {}
    void setBoundingBox();
    void getBoundingBox();
private:
    sf::RectangleShape boundingBox;
};

#endif