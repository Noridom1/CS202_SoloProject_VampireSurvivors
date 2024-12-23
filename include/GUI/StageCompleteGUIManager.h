#ifndef STAGECOMPLETEGUIMANAGER_H
#define STAGECOMPLETEGUIMANAGER_H

#include "GUIManager.h"
#include "Observer.h"
#include "Button.h"

class StageComplete;

class StageCompleteGUIManager : public GUIManager {
private:
    sf::Font font;
    StageComplete *menu;

    Image* gameTitle;
    Image* background;

    Button* homeButton;
    Button* newGameButton;

public:
    StageCompleteGUIManager(sf::RenderWindow *wd, StageComplete *menu);

    ~StageCompleteGUIManager();

    void update(float dt) override;

    void render(sf::RenderWindow* window) override;

    void handleEvent(const sf::Event& event) override;

    void onHomeButtonClicked();

    void onNewGameButtonClicked();
    //void onNotify(const Event *event) override;

};

#endif