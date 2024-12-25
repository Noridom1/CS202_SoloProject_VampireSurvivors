#ifndef CHARACTERMENUGUIMANAGER_H
#define CHARACTERMENUGUIMANAGER_H

#include "GUIManager.h"
#include "Observer.h"
#include "Button.h"

class CharacterSelectionMenu;

class CharacterMenuGUIManager : public GUIManager {
private:
    sf::Font font;
    CharacterSelectionMenu *menu;

    Image* title;
    Image* background;

    vector<Button*> buttons;

    int curStagePreview;
public:

    CharacterMenuGUIManager(sf::RenderWindow *wd, CharacterSelectionMenu *menu, int numStagesUnlocked);

    ~CharacterMenuGUIManager();

    void update(float dt) override;

    void render(sf::RenderWindow* window) override;

    void handleEvent(const sf::Event& event) override;

    void onBackButtonClicked();

    void onCharacterFrameClicked(int stage);

    //void onNotify(const Event *event) override;

};

#endif