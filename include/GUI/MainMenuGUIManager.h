#ifndef MAINMENUGUIMANAGER_H
#define MAINMENUGUIMANAGER_H


#include "GUIManager.h"
#include "Observer.h"
#include "Button.h"

class MainMenu;

class MainMenuGUIManager : public GUIManager {
private:
    sf::Font font;
    MainMenu *menu;

    Image* gameTitle;
    Image* background;

    Button* playButton;
public:
    MainMenuGUIManager(sf::RenderWindow *wd, MainMenu *menu);

    ~MainMenuGUIManager();

    void update(float dt) override;

    void render(sf::RenderWindow* window) override;

    void handleEvent(const sf::Event& event) override;

    void onPlayButtonClicked();

    //void onNotify(const Event *event) override;

};

#endif