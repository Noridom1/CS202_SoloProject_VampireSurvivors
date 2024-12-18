#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

enum class EntityType {
    None,
    Enemy,
    Player,
    Projectile,
    Obstacle
};

class Entity {

public:
    Entity(sf::Vector2f pos) : position(pos) {}

    Entity(sf::FloatRect bbox) : boundingBox(bbox) {
        this->position.x = bbox.left + bbox.width / 2.f;
        this->position.y = bbox.top + bbox.height / 2.f;
    }
    
    sf::FloatRect& getBoundingBox();

    sf::Vector2f getPosition();

    virtual void setBoundingBox() = 0;

    virtual void move(sf::Vector2f movement) = 0;

    virtual void drawBoundingBox(sf::RenderWindow *window);

    sf::Vector2f getHalfSize();

    virtual EntityType getType() const = 0;
    
protected:
    sf::Vector2f position;
    sf::FloatRect boundingBox;
    
    bool markedForDrawing = false;

public:
    int id = 0;
};

#endif