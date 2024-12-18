#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>
class Collider {
public:
    Collider(sf::FloatRect bbox);
    ~Collider();
    
    void move(float dx, float dy);

    bool checkCollision(Collider& other, float push);

    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();
private:
    sf::FloatRect bbox;

};

#endif