#include "GUI/StageCompleteGUIManager.h"
#include "GameManagement/MainMenu.h"
#include "GameManagement/Game.h"
#include "GameManagement/StageSelectionMenu.h"
#include "GameManagement/StageComplete.h"

StageCompleteGUIManager::StageCompleteGUIManager(sf::RenderWindow *wd, StageComplete *menu) :
    GUIManager(wd), menu(menu)
{
    homeButton = new Button(
        430.f, 385.f,
        "../assets/GUI/HomeButton_Normal.png",
        "../assets/GUI/HomeButton_Hover.png"
        );

    homeButton->setOnClick([this]() {
        cout << "Home Button clicked\n";
        onHomeButtonClicked();
    });

    newGameButton = new Button(
        650.f, 385.f,
        "../assets/GUI/NewGameButton_Normal.png",
        "../assets/GUI/NewGameButton_Hover.png"
        );

    newGameButton->setOnClick([this]() {
        cout << "NewGame Button clicked\n";
        onNewGameButtonClicked();
    });

    gameTitle = new Image("../assets/GUI/StageComplete/GameTitle.png");
    background = new Image("../assets/GUI/MenuBG_Shadow.png");
    gameTitle->setPosition(265.f, 90.f);
    background->setPosition(0.f, 0.f);
}

StageCompleteGUIManager::~StageCompleteGUIManager()
{
    delete gameTitle;
    delete background;
    delete homeButton;
    delete newGameButton;
}

void StageCompleteGUIManager::update(float dt)
{
    GUIManager::update(dt);
    homeButton->update(window);
    newGameButton->update(window);
}

void StageCompleteGUIManager::render(sf::RenderWindow *window)
{
    background->draw(window);
    gameTitle->draw(window);

    homeButton->render(window);
    newGameButton->render(window);
    GUIManager::render(window);
}

void StageCompleteGUIManager::handleEvent(const sf::Event &event)
{
    GUIManager::handleEvent(event);
    homeButton->handleEvent(event);
    newGameButton->handleEvent(event);
}

void StageCompleteGUIManager::onHomeButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<MainMenu>(window));

}
// void MenuGUIManager::onNotify(const Event *event)
void StageCompleteGUIManager::onNewGameButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<StageSelectionMenu>(window));

}