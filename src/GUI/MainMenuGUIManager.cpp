#include "GUI/MainMenuGUIManager.h"
#include "GameManagement/MainMenu.h"
#include "GUI/Button.h"
#include "GameManagement/Game.h"
#include "GameManagement/StageSelectionMenu.h"

MainMenuGUIManager::MainMenuGUIManager(sf::RenderWindow *wd, MainMenu *menu) :
    GUIManager(wd), menu(menu)
{
    playButton = new Button(
        540.f, 305.f,
        "../assets/GUI/MainMenu/PlayButton_Normal.png",
        "../assets/GUI/MainMenu/PlayButton_Hover.png");
        playButton->setOnClick([this]() {
            cout << "PlayButton clicked\n";
            onPlayButtonClicked();
        });

    gameTitle = new Image("../assets/GUI/MainMenu/GameTitle.png");
    background = new Image("../assets/GUI/MainMenu/MenuBG_Default.png");
    gameTitle->setPosition(320.f, 35.f);
    background->setPosition(0.f, 0.f);
}

MainMenuGUIManager::~MainMenuGUIManager()
{
    delete gameTitle;
    delete background;
}

void MainMenuGUIManager::update(float dt)
{
    GUIManager::update(dt);
    playButton->update(window);
}

void MainMenuGUIManager::render(sf::RenderWindow *window)
{
    background->draw(window);
    gameTitle->draw(window);

    playButton->render(window);
    GUIManager::render(window);
}

void MainMenuGUIManager::handleEvent(const sf::Event &event)
{
    GUIManager::handleEvent(event);
    playButton->handleEvent(event);
}

void MainMenuGUIManager::onPlayButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<StageSelectionMenu>(window));

}
// void MenuGUIManager::onNotify(const Event *event)
// {

// }
