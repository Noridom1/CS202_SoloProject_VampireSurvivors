#include "GameManagement/Game.h"
#include <iostream>
#include <filesystem>
#include "GameManagement/Gameplay.h"
#include "GameManagement/MainMenu.h"
#include "GameManagement/GameOver.h"
#include <fstream>

using namespace std;

int Game::numUnlockedStages = 0;

Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::run()
{   
    sf::Clock clock;
    while (window->isOpen()) {
        sf::Event ev;
        this->deltaTime = clock.restart().asSeconds();
        
        //this->handleEvents();
        this->gameState->handleEvents(ev);
        this->gameState->update(this->deltaTime);
        this->gameState->render();
        
        if (nextState) {
            this->gameState = move(nextState);
        }
    }
}

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Survive");
    window->setKeyRepeatEnabled(false);
    this->gameState = make_unique<MainMenu>(this->window);
    loadStages();
}

Game::~Game()
{
    delete this->window;
}

void Game::saveStages()
{
    ofstream fout("../data/save.txt");
    if (!fout) {
        cout << "Cannot load stages\n";
        throw runtime_error("Cannot load stages!\n");
    }

    fout << this->numUnlockedStages << endl;
    fout.close();
}

void Game::updateStages(int completedStage)
{
    if (completedStage == numUnlockedStages) {
        numUnlockedStages = min(maxNumStages, numUnlockedStages + 1);
        saveStages();
    }
}

void Game::loadStages()
{
    ifstream fin("../data/save.txt");
    if (!fin) {
        cout << "Cannot load stages\n";
        throw runtime_error("Cannot load stages!\n");
    }

    fin >> this->numUnlockedStages;
    fin.close();
}

void Game::setGameState(unique_ptr<GameState> newState)
{
    this->nextState = move(newState);
}

int Game::getNumUnlockedStages()
{
    return this->numUnlockedStages;
}
