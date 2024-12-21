#ifndef SKILL_H
#define SKILL_H

#include <SFML/Graphics.hpp>
#include "Image.h"
#include "Animation.h"

class Skill {
public:
    virtual void execute(sf::Vector2f position) = 0;

    virtual void render(sf::RenderWindow *window) = 0;

    virtual void updateAnimation(float deltaTime, bool faceRight) = 0;

    virtual void resetAnimation() = 0;
    
    virtual ~Skill() = default;

private:
    bool inProgress;
    Image *img;
    Animation animation;

    float curCooldown;
    float cooldown;
    
};

#endif