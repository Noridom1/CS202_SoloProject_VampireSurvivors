#include <iostream>
#include <vector>
#include <string>
#include "Map/MapLoader.h"
using namespace tinyxml2;

int main() {
    const std::string tmxFile = "map.tmx"; // Replace with your map file
    MapLoader loader(tmxFile);
    loader.load();
    loader.printTilesets();
    loader.printLayers();
    system("pause");
    return 0;
}
