#include "GameManagement/Game.h"
#include <iostream>
#include <filesystem>
#include "GameManagement/Gameplay.h"
#include "GameManagement/MainMenu.h"
#include "GameManagement/GameOver.h"
#include "Projectile/ProjectileManager.h"
#include <fstream>

using namespace std;

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
    loadCharacters();
}

Game::~Game()
{
    delete this->window;
}

void Game::saveStages()
{
    ofstream fout("../data/stages.txt");
    if (!fout) {
        throw runtime_error("Cannot open file!\n");
    }

    fout << this->numUnlockedStages << endl;
    fout.close();
}

void Game::saveCharacters()
{
    ofstream fout("../data/characters.txt");
    if (!fout) {
        throw runtime_error("Cannot open file!\n");
    }

    fout << this->numUnlockedCharacters << endl;
    fout.close();
}

void Game::updateStages(int completedStage)
{
    if (completedStage == numUnlockedStages) {
        numUnlockedStages = min(maxNumStages, numUnlockedStages + 1);
        numUnlockedCharacters = min(maxNumCharacters, numUnlockedCharacters + 1);
        saveStages();
        saveCharacters();
    }
}

void Game::loadStages()
{
    ifstream fin("../data/stages.txt");
    if (!fin) {
        cout << "Cannot load stages\n";
        throw runtime_error("Cannot load stages!\n");
    }

    fin >> this->numUnlockedStages;
    fin.close();
}

void Game::loadCharacters()
{
    ifstream fin("../data/characters.txt");
    if (!fin) {
        cout << "Cannot load stages\n";
        throw runtime_error("Cannot load characters!\n");
    }

    fin >> this->numUnlockedCharacters;
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

int Game::getNumUnlockedCharacters()
{
    return this->numUnlockedCharacters;
}

int Game::getSelectedStage()
{
    return this->selectedStage;
}

int Game::getSelectedCharacter()
{
    return this->selectedCharacter;
}

void Game::selectStage(int stage)
{
    this->selectedStage = stage;
}

void Game::selectCharacter(int character)
{
    this->selectedCharacter = character;
}
