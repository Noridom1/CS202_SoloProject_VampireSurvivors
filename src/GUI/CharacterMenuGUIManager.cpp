#include "GUI/CharacterMenuGUIManager.h"
#include "GameManagement/CharacterSelectionMenu.h"
#include "GameManagement/Game.h"
#include "GameManagement/MainMenu.h"
#include "GameManagement/Gameplay.h"
#include "GUI/CharacterFrame.h"

CharacterMenuGUIManager::CharacterMenuGUIManager(sf::RenderWindow *wd, CharacterSelectionMenu *menu, int numCharacterUnlocked) :
    GUIManager(wd), menu(menu)
{

    if (!font.loadFromFile("../assets/fonts/GUIfont.ttf")) {
        cout << "Cannot load font\n";
    }
    title = new Image("../assets/GUI/SelectCharacter/CharacterTitle.png");
    background = new Image("../assets/GUI/MenuBG_Shadow.png");

    title->setPosition(320.f, -23.f);
    background->setPosition(0.f, 0.f);

    this->buttons.resize(4);

    Button* backButton = new Button (
        30.f, 30.f,
        "../assets/GUI/StageSelection/BackButton_Normal.png",
        "../assets/GUI/StageSelection/BackButton_Hover.png"
    );

    backButton->setOnClick([this] {
        onBackButtonClicked();
    });

    this->buttons[0] = backButton;

    cout << "added backButton \n";
    float x = 130.f;
    float y = 270.f;
    float dist_x = 370.f;

    int cnt = 1;
    for (int i = 0; i < 3; ++i) {
        if (cnt <= numCharacterUnlocked) {
            buttons[cnt] = new CharacterFrame(
                x, y,
                "../assets/GUI/SelectCharacter/CharacterFrame_Normal.png",
                "../assets/GUI/SelectCharacter/CharacterFrame_Hover.png",
                font,
                i
            );
            buttons[cnt]->setOnClick([this, i] {
                onCharacterFrameClicked(i);
            });
        }

        else {
            buttons[cnt] = new Button (
                x, y,
                "../assets/GUI/SelectCharacter/CharacterLocked_Normal.png",
                "../assets/GUI/SelectCharacter/CharacterLocked_Hover.png"
            );
        }
            
        ++cnt;
        x += dist_x;
    }
    cout << "added characterFrame \n";


}

CharacterMenuGUIManager::~CharacterMenuGUIManager()
{
    for (auto button : buttons) {
        delete button;
    }
    delete background;
    delete title;

}

void CharacterMenuGUIManager::update(float dt)
{
    for (auto button : buttons) {
        button->update(window);
    }
}

void CharacterMenuGUIManager::render(sf::RenderWindow *window)
{
    background->draw(window);
    title->draw(window);
    for (auto button : buttons) {
        button->render(window);
    }  
    if (curStagePreview == -1)
        return;
}

void CharacterMenuGUIManager::handleEvent(const sf::Event &event)
{
    for (auto button : buttons) {
        button->handleEvent(event);
    }
}

void CharacterMenuGUIManager::onBackButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<MainMenu>(window));
}

void CharacterMenuGUIManager::onCharacterFrameClicked(int character)
{
    cout << "Character " << character << " button clicked\n";
    Game::getInstance().selectCharacter(character);
    Game::getInstance().setGameState(std::make_unique<Gameplay>(
        window,
        static_cast<MapName>(Game::getInstance().getSelectedStage()),
        static_cast<CharacterType>(Game::getInstance().getSelectedCharacter())
    ));
}