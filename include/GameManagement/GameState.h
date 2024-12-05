#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "Player.h"
//#include "Game.h"
#include <iostream>
using namespace std;

class GameState {
public:
    static const float WIDTH;
    static const float HEIGHT;
    explicit GameState(sf::RenderWindow *wd): window(wd) {}

    virtual void handleEvents(sf::Event &ev) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

    void resizeView(sf::RenderWindow *window, sf::View& view);
    sf::Vector2i getMousePosition() const;

protected:
    sf::RenderWindow *window;
};

class MenuState : public GameState {
public:
    explicit MenuState(sf::RenderWindow *wd) : GameState(wd) {}
    ~MenuState() = default;
    void handleEvents(sf::Event &ev) override {}
    void update(float deltaTime) override {}
    void render() override {
        std::cout << "This is MenuEvent\n";
    }
private:

};



#endif