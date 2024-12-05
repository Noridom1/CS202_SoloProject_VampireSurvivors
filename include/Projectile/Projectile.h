#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Animation.h"
#include "ProjectileFlyweightFactory.h"

class Projectile : public Entity {
public:
    Projectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed)
        : sprite(&ProjectileFlyweightFactory::getProjectileImg(type).getSprite()),
          position(startPos),
          direction(direction),
          move_speed(speed)
    {
        sf::Texture& texture = ProjectileFlyweightFactory::getProjectileImg(type).getTexture();
        TexturesAnimation texture_animation = ProjectileAnimations.at(type);
        animation = Animation(&texture, texture_animation.numSprites, texture_animation.imageCount, texture_animation.switchTime);
    }

    void updateAnimation(float deltaTime) {
        animation.update(0, deltaTime, true);
    }

    void updatePosition(float deltaTime) {
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0.0f) {
            direction /= magnitude;
        }
        this->move(direction * move_speed * deltaTime);
    }

    virtual void update(float deltaTime) {
        updateAnimation(deltaTime);
        updatePosition(deltaTime);
    }

    void draw(sf::RenderWindow* window) {
        this->sprite->setPosition(position);
        this->sprite->setTextureRect(animation.uvRect);
        window->draw(*sprite);
    }

    void move(sf::Vector2f movement) {
        position += movement;
        //sprite.setPosition(position);
    }

    bool isOutOfBounds() {
        return false;
    }
protected:
    sf::Sprite* sprite;
    sf::Vector2f position;
    sf::Vector2f direction;
    Animation animation;
    float move_speed;
};


#endif 