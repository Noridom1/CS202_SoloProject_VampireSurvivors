#include "Skills/BladeThunder.h"

BladeThunder::BladeThunder(sf::Vector2f dimension)
{
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

void BladeThunder::execute(sf::Vector2f position)
{
    effectArea.setPosition(position);
    rect.setPosition(position);
    std::cout << "BladeThunder::execute() at " << effectArea.getPosition().x << " " << effectArea.getPosition().y << endl;
}

void BladeThunder::render(sf::RenderWindow *window)
{
    //window->draw(this->effectArea);
    window->draw(this->rect);
}

void BladeThunder::updateAnimation(float deltaTime, bool faceRight)
{
    animation.update(0, deltaTime, faceRight);
    rect.setTextureRect(animation.uvRect);
}

void BladeThunder::resetAnimation()
{
    this->animation.reset();
}
