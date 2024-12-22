#ifndef STAGEMENUGUIMANAGER_H
#define STAGEMENUGUIMANAGER_H

#include "GUIManager.h"
#include "Observer.h"
#include "Button.h"

class StageSelectionMenu;

class StageMenuGUIManager : public GUIManager {
private:
    sf::Font font;
    StageSelectionMenu *menu;

    Image* title;
    Image* background;

    vector<Button*> buttons;
    vector<Image*> stagePreviews;

    int curStagePreview;
public:
    StageMenuGUIManager(sf::RenderWindow *wd, StageSelectionMenu *menu, int numStagesUnlocked);

    ~StageMenuGUIManager();

    void update(float dt) override;

    void render(sf::RenderWindow* window) override;

    void handleEvent(const sf::Event& event) override;

    void onBackButtonClicked();

    void onStageButtonClicked(int stage);

    //void onNotify(const Event *event) override;

};

#endif