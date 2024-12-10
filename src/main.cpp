#include <iostream>

#include <SFML/Graphics.hpp>
#include "GameManagement/Game.h"
#include "Map/MapLoader.h"
using namespace std;

int main()
{
    //cout << "hello world!";
    // MapLoader::getInstance().load("../assets/map/forest/map.tmx");
    // MapLoader::getInstance().printTilesets();
    // MapLoader::getInstance().printLayers();
    // MapLoader::getInstance().printTilesetsId();
    Game::getInstance().run();
    return 0;
}