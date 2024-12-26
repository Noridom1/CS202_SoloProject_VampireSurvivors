#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Image {

public:
    Image(const string& filename);

    sf::Texture& getTexture();

    sf::Sprite& getSprite();

    void setPosition(sf::Vector2f pos);

    void setPosition(float posX, float posY);
    
    void draw(sf::RenderWindow *window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif