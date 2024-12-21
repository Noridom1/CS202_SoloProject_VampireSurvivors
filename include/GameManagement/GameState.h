#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
//#include "Game.h"
#include <iostream>
using namespace std;

class GameState {
public:
    static const float WIDTH;
    static const float HEIGHT;
    explicit GameState(sf::RenderWindow *wd): window(wd) {cout << "Hello\n";}
    
    virtual ~GameState() = default;
    
    virtual void handleEvents(sf::Event &ev) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

    void resizeView(sf::RenderWindow& window, sf::View& view, const sf::Event::SizeEvent& sizeEvent);
    sf::Vector2i getMousePosition() const;

protected:
    sf::RenderWindow *window;
};



#endif