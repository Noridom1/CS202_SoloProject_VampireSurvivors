#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

class Menu : public GameState {
public:
    explicit Menu(sf::RenderWindow *wd);

    ~Menu() = default;

    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;
    
private:
    sf::Text text;
    sf::Font font;

};

#endif