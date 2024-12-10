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

struct Tileset {
    unsigned firstGID;
    string imgSource;
    unsigned tileCount;
    unsigned tileWidth;
    unsigned tileHeight;
    unsigned columns; // Optional: Useful for calculating tile positions
    unsigned rows;

    Image *img = nullptr;
    ~Tileset() {
        if(img) delete img;
    }

    friend ostream& operator<<(ostream& out, const Tileset& tileset) {
        out << tileset.firstGID << endl;
        out << tileset.tileCount << endl;
        out << tileset.tileWidth << endl;
        out << tileset.tileHeight << endl;
        out << tileset.columns << endl;
        out << tileset.rows << endl;
        return out;
    }
};

class MapLoader {
public:
    MapLoader(const MapLoader&) = delete;

    MapLoader& operator=(const MapLoader&) = delete;

    ~MapLoader();

    static MapLoader& getInstance();

    bool loadTileSets(XMLElement *mapElement, const string& map_name);

    bool loadLayers(XMLElement *mapElement);

    bool loadObjects(XMLElement *mapElemnt);

    const Tileset* getTilesetForGID(unsigned gid);

    sf::IntRect getTileInTileset(unsigned gid);

    bool load(const string& tmx_filename);

    vector<Tileset*>& getTilesets();

    vector<vector<vector<unsigned>>>& getLayers();

    vector<sf::FloatRect>& getObjects();

    unsigned getMapSize();
    
    unsigned getTileSize();

    void printTilesets();

    void printLayers();

    void printTilesetsId();
private:
    MapLoader() {}
    unsigned mapSize, tileSize;
    vector<Tileset*> tilesets;
    vector<vector<vector<unsigned>>> layers;
    vector<sf::FloatRect> objects;
    unordered_map<unsigned, const Tileset*> gidToTileset;
};

#endif
