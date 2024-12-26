#include "Image.h"
#include "Texture.h"

Image::Image(const string &filename)
{
    // if (!texture.loadFromFile(filename)) {
    //     throw std::runtime_error("Failed to load texture from " + filename);
    // }
    texture = TextureManagement::getTextureByString(filename);
    sprite.setTexture(texture);
}

sf::Texture &Image::getTexture()
{
    return this->texture;
}

sf::Sprite &Image::getSprite()
{
    return this->sprite;
}

void Image::setPosition(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Image::setPosition(float posX, float posY)
{
    this->sprite.setPosition(sf::Vector2f(posX, posY));
}

void Image::draw(sf::RenderWindow *window)
{
    window->draw(this->sprite);
}
