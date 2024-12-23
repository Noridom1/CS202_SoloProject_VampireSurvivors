#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <Image.h>

using namespace std;
using namespace tinyxml2;

class MapLoader {
public:
    MapLoader(const MapLoader&) = delete;

    MapLoader& operator=(const MapLoader&) = delete;

    ~MapLoader();

    static MapLoader& getInstance();

    bool loadObjects(XMLElement *mapElemnt);

    bool load(const string& tmx_filename);

    vector<sf::FloatRect>& getObjects();
    
    vector<int> getObjectIds();

    Image* getBackground();

    unsigned getMapSize();
    
    unsigned getTileSize();
    
    void reset();

private:
    MapLoader() {}
    unsigned mapSize, tileSize;
    vector<sf::FloatRect> objects;
    vector<int> object_ids;

    Image *background;
};

#endif