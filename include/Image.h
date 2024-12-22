#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Image {

public:
    Image(const string& filename) {
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture from " + filename);
        }
        sprite.setTexture(texture);
    }

    sf::Texture& getTexture() {
        return this->texture;
    }

    sf::Sprite& getSprite() {
        return this->sprite;
    }

    void setPosition(sf::Vector2f pos) {
        this->sprite.setPosition(pos);
    }

    void setPosition(float posX, float posY) {
        this->sprite.setPosition(sf::Vector2f(posX, posY));
    }
    
    void draw(sf::RenderWindow *window) {
        window->draw(this->sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif