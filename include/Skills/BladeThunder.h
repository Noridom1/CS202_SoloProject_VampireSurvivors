#ifndef BLADETHUNDER_H
#define BLADETHUNDER_H

#include "Skill.h"
#include "Animation.h"
#include "Texture.h"
#include <iostream>

class BladeThunder : public Skill {
public:
    BladeThunder(sf::Vector2f dimension) {

        this->texture = &TextureManagement::getSkillTexture(SkillType::BLadeThunder);

        const auto& skillAnimation = skillAnimations.at(SkillType::BLadeThunder);
        this->animation = Animation(
            this->texture,
            skillAnimation.numSprites,
            skillAnimation.imageCount, 
            skillAnimation.switchTime
        );
        this->rect.setTexture(this->texture);
        sf::Vector2i animation_size = animation.uvRect.getSize();
        this->rect.setOrigin(dimension.x / 2.0f, dimension.y / 2.0f);
        effectArea.setSize(dimension);
        this->rect.setSize(dimension);
        effectArea.setFillColor(sf::Color(255, 0, 0, 100));
        effectArea.setOrigin(dimension.x / 2.0f, dimension.y / 2.0f);

    }

    void execute(sf::Vector2f position) override {
        effectArea.setPosition(position);
        rect.setPosition(position);
        std::cout << "BladeThunder::execute() at " << effectArea.getPosition().x << " " << effectArea.getPosition().y << endl;
    }

    void render(sf::RenderWindow* window) override {
        window->draw(this->effectArea);
        window->draw(this->rect);
    }

    void updateAnimation(float deltaTime, bool faceRight) override {
        animation.update(0, deltaTime, faceRight);
        rect.setTextureRect(animation.uvRect);
    }

    void resetAnimation() override {
        this->animation.reset();
    }

private:
    sf::RectangleShape effectArea;
    //sf::Sprite sprite;
    sf::RectangleShape rect;
    sf::Texture *texture;
    Animation animation;
    float timeDelay;
};


#endif