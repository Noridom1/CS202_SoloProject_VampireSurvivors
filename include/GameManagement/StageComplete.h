#ifndef STAGECOMPLETE_H
#define STAGECOMPLETE_H

#include "GameState.h"

class StageCompleteGUIManager;

class StageComplete : public GameState {
    friend StageCompleteGUIManager;
public:
    explicit StageComplete(sf::RenderWindow *wd);

    ~StageComplete();

    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;

private:

    StageCompleteGUIManager *guiManager;

};

#endif