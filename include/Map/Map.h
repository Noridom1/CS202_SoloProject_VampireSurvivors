#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Map/MapLoader.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "Image.h"
#include "Tile.h"
#include "Entity/StationaryEntity.h"

#include <iostream>
using namespace std;

enum class MapName {
    Snow,
    Beach,
};

class Map {
public:
    //Map(unsigned tile_size, int mapSize);
    Map(const string& filename);
    ~Map();

    void update(sf::RenderWindow *window, sf::View *view);

    void updateRenderRegion(sf::View *view);
    
    void updateMousePos(sf::RenderWindow *window, sf::View *view);

    void drawBackground(sf::RenderWindow *window);

    void draw(sf::RenderWindow *window);

    int getMapSize();

    float getTileSize();

    float getWorldSize();

    vector<StationaryEntity*>& getObjects();

    sf::Vector2f getCenterPosition();

private:
    unsigned uTileSize;
    float fTileSize;
    int mapSize;
    int numLayers;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    sf::RectangleShape tile;
    sf::RectangleShape tileSelector;

    sf::Font font;
    sf::Text MouseInfo;

    vector<vector<vector<unsigned>>> layers;
    vector<vector<sf::RectangleShape>> gridMap;
    vector<vector<vector<Tile*>>> tileLayers;
    vector<StationaryEntity*> objects;

    sf::Vector2i renderFrom, renderTo;

    Image* background;
    //vector<sf::Vector2f> imaginaryMapPostions;

};
#endif