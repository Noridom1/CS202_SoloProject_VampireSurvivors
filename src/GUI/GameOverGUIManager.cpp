#include "GUI/GameOverGUIManager.h"
#include "GameManagement/MainMenu.h"
#include "GUI/Button.h"
#include "GameManagement/Game.h"
#include "GameManagement/StageSelectionMenu.h"
#include "GameManagement/GameOver.h"

GameOverGUIManager::GameOverGUIManager(sf::RenderWindow *wd, GameOver *menu) :
    GUIManager(wd), menu(menu)
{
    homeButton = new Button(
        450.f, 375.f,
        "../assets/GUI/GameOver/HomeButton_Normal.png",
        "../assets/GUI/GameOver/HomeButton_Hover.png"
        );

    homeButton->setOnClick([this]() {
        cout << "Home Button clicked\n";
        onHomeButtonClicked();
    });

    newGameButton = new Button(
        653.f, 375.f,
        "../assets/GUI/GameOver/NewGameButton_Normal.png",
        "../assets/GUI/GameOver/NewGameButton_Hover.png"
        );

    newGameButton->setOnClick([this]() {
        cout << "NewGame Button clicked\n";
        onNewGameButtonClicked();
    });

    gameTitle = new Image("../assets/GUI/GameOver/GameTitle.png");
    background = new Image("../assets/GUI/MenuBG_Shadow.png");
    gameTitle->setPosition(310.f, 115.f);
    background->setPosition(0.f, 0.f);
}

GameOverGUIManager::~GameOverGUIManager()
{
    delete gameTitle;
    delete background;
    delete homeButton;
    delete newGameButton;
}

void GameOverGUIManager::update(float dt)
{
    GUIManager::update(dt);
    homeButton->update(window);
    newGameButton->update(window);
}

void GameOverGUIManager::render(sf::RenderWindow *window)
{
    background->draw(window);
    gameTitle->draw(window);

    homeButton->render(window);
    newGameButton->render(window);
    GUIManager::render(window);
}

void GameOverGUIManager::handleEvent(const sf::Event &event)
{
    GUIManager::handleEvent(event);
    homeButton->handleEvent(event);
    newGameButton->handleEvent(event);
}

void GameOverGUIManager::onHomeButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<MainMenu>(window));

}
// void MenuGUIManager::onNotify(const Event *event)
void GameOverGUIManager::onNewGameButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<StageSelectionMenu>(window));

}