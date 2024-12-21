#include "GameManagement/Menu.h"

Menu::Menu(sf::RenderWindow *wd) : GameState(wd)
{
    font.loadFromFile("../assets/fonts/Poppins-Bold.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    text.setString("This is Menu!");
    cout << "Switch to Menu!\n";
}

void Menu::handleEvents(sf::Event &ev)
{
    while(window->pollEvent(ev)){
        if (ev.type == sf::Event::Closed){
            window->close();
        }
    }
}
void Menu::update(float deltaTime)
{
}
void Menu::render()
{
    window->clear(sf::Color::White);

    window->draw(text);

    window->display();
}