#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "tinyxml2.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace tinyxml2;

struct Tileset {
    unsigned firstGID;
    string imgSource;
    unsigned tileWidth;
    unsigned tileHeight;
    unsigned columns; // Optional: Useful for calculating tile positions
};

class MapLoader {
public:
    MapLoader(const string& tmx_filename) : tmx_filename(tmx_filename) {}

    vector<Tileset>& loadTileSets(XMLElement *mapElement);
    vector<vector<vector<unsigned>>>& loadLayers(XMLElement *xmlElement);
    const Tileset* getTilesetForGID(unsigned gid);
    bool load();

    void printTilesets();
    void printLayers();
private:
    string tmx_filename;
    vector<Tileset> tilesets;
    vector<vector<vector<unsigned>>> layers;
    unordered_map<unsigned, const Tileset*> gidToTileset;
};

#endif
