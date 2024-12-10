#ifndef BLADETHUNDER_H
#define BLADETHUNDER_H

#include "Skill.h"
#include "Animation.h"
#include "Texture.h"
#include <iostream>

class BladeThunder : public Skill {
public:
    BladeThunder(sf::Vector2f dimension);

    void execute(sf::Vector2f position) override;

    void render(sf::RenderWindow* window) override;

    void updateAnimation(float deltaTime, bool faceRight) override;

    void resetAnimation() override;

private:
    sf::RectangleShape effectArea;
    //sf::Sprite sprite;
    sf::RectangleShape rect;
    sf::Texture *texture;
    Animation animation;
    float timeDelay;
};


#endif