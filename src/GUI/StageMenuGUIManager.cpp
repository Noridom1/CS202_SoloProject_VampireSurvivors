#include "GameManagement/Game.h"
#include "GameManagement/MainMenu.h"
#include "GameManagement/Gameplay.h"
#include "GUI/StageMenuGUIManager.h"
#include "GUI/StageButton.h"

StageMenuGUIManager::StageMenuGUIManager(sf::RenderWindow *wd, StageSelectionMenu *menu, int numStagesUnlocked) :
    GUIManager(wd), menu(menu), curStagePreview(-1)
{
    title = new Image("../assets/GUI/StageSelection/StageTitle.png");
    background = new Image("../assets/GUI/MenuBG_Shadow.png");

    title->setPosition(320.f, -23.f);
    background->setPosition(0.f, 0.f);

    this->buttons.resize(7);

    Button* backButton = new Button (
        30.f, 30.f,
        "../assets/GUI/StageSelection/BackButton_Normal.png",
        "../assets/GUI/StageSelection/BackButton_Hover.png"
    );

    backButton->setOnClick([this] {
        onBackButtonClicked();
    });

    this->buttons[0] = backButton;

    float start_x = 260.f;
    float start_y = 243.f;
    float x = 260;
    float y = 243.f;
    float dist_x = 140.f;
    float dist_y = 173.f;

    int cnt = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (cnt <= numStagesUnlocked) {
                int stage = cnt;
                buttons[cnt] = new StageButton(
                    x, y,
                    "../assets/GUI/StageSelection/StageBG.png",
                    "../assets/GUI/StageSelection/StageBG_Hover.png",
                    font,
                    stage
                );
                buttons[cnt]->setOnClick([this, stage] {
                    onStageButtonClicked(stage);
                });

                buttons[cnt]->setOnHover([this, cnt] {
                    this->curStagePreview = cnt - 1;
                });
            }

            else {
                buttons[cnt] = new Button (
                    x, y,
                    "../assets/GUI/StageSelection/StageBGLocked_Normal.png",
                    "../assets/GUI/StageSelection/StageBGLocked_Hover.png"
                );
            }
            
            ++cnt;
            x += dist_x;
        }
        x = start_x;
        y += dist_y;
    }

    for (int i = 0; i < numStagesUnlocked; ++i) {
        stagePreviews.push_back(new Image("../assets/GUI/StageSelection/Stage" + to_string(i + 1) + "_preview.png"));
        stagePreviews.back()->setPosition(640.f, 243.f);
    }

}

StageMenuGUIManager::~StageMenuGUIManager()
{
    for (auto button : buttons) {
        delete button;
    }
    for (auto stage_pre : stagePreviews) {
        delete stage_pre;
    }
    delete background;
    delete title;

}

void StageMenuGUIManager::update(float dt)
{
    for (auto button : buttons) {
        button->update(window);
    }
}

void StageMenuGUIManager::render(sf::RenderWindow *window)
{
    background->draw(window);
    title->draw(window);
    for (auto button : buttons) {
        button->render(window);
    }  
    if (curStagePreview == -1)
        return;
    stagePreviews[curStagePreview]->draw(window);
}

void StageMenuGUIManager::handleEvent(const sf::Event &event)
{
    for (auto button : buttons) {
        button->handleEvent(event);
    }
}

void StageMenuGUIManager::onBackButtonClicked()
{
    Game::getInstance().setGameState(std::make_unique<MainMenu>(window));
}

void StageMenuGUIManager::onStageButtonClicked(int stage)
{
    cout << "Stage " << stage << " button clicked\n";
    //Game::getInstance().setGameState(std::make_unique<Gameplay>(window, static_cast<MapName>(stage)));
}
