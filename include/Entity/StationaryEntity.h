#ifndef STATIONARYENTITY_H
#define STATIONARYENTITY_H

#include "Entity/Entity.h"
#include <string>

class StationaryEntity : public Entity {
public:
    StationaryEntity(sf::FloatRect bbox, int id) : Entity(bbox) {
        font.loadFromFile("../assets/fonts/Poppins-Bold.ttf");
        txt.setFillColor(sf::Color::Blue);
        txt.setCharacterSize(20);
        txt.setPosition(
            this->boundingBox.left + this->boundingBox.width / 2.f,
            this->boundingBox.top + this->boundingBox.height / 2.f
        );
        this->id = id;
        txt.setString(std::to_string(id));
    }

    void setBoundingBox() override {}

    void move(sf::Vector2f movement) override {}

    void drawBoundingBox(sf::RenderWindow *window) override {
        Entity::drawBoundingBox(window);
        if(isMouseOver(window))
            window->draw(txt);
    }

    bool isMouseOver(sf::RenderWindow *window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        return mousePos.x >= boundingBox.left && mousePos.x <= boundingBox.left + boundingBox.width &&
               mousePos.y >= boundingBox.top && mousePos.y <= boundingBox.top + boundingBox.height;
    }

    EntityType getType() const override {
        return EntityType::Obstacle;
    }

private:
    sf::Text txt;
    sf::Font font;
};
#endif