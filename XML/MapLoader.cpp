#include "MapLoader.h"
#include <iostream>

// Load tilesets and populate gidToTileset map
vector<Tileset>& MapLoader::loadTileSets(XMLElement *mapElement) 
{
    // Loop through all <tileset> elements
    for (XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
         tilesetElement; 
         tilesetElement = tilesetElement->NextSiblingElement("tileset")) {
        
        Tileset tileset;
        tileset.firstGID = tilesetElement->UnsignedAttribute("firstgid");

        // External tileset reference (tsx file)
        const char* source = tilesetElement->Attribute("source");
        if (source) {
            XMLDocument tsxDoc;
            if (tsxDoc.LoadFile(source) == XML_SUCCESS) {
                XMLElement* tsxRoot = tsxDoc.FirstChildElement("tileset");
                if (tsxRoot) {
                    XMLElement* imageElement = tsxRoot->FirstChildElement("image");
                    if (imageElement) {
                        tileset.imgSource = imageElement->Attribute("source");
                        tileset.tileWidth = tsxRoot->UnsignedAttribute("tilewidth");
                        tileset.tileHeight = tsxRoot->UnsignedAttribute("tileheight");
                        tileset.columns = tsxRoot->UnsignedAttribute("columns");
                    }
                }
            }
        } else {
            // Inline tileset definition
            XMLElement* imageElement = tilesetElement->FirstChildElement("image");
            if (imageElement) {
                tileset.imgSource = imageElement->Attribute("source");
                tileset.tileWidth = tilesetElement->UnsignedAttribute("tilewidth");
                tileset.tileHeight = tilesetElement->UnsignedAttribute("tileheight");
                tileset.columns = tilesetElement->UnsignedAttribute("columns");
            }
        }

        tilesets.push_back(tileset);

        // Populate gidToTileset map for all tiles in this tileset
        for (unsigned gid = tileset.firstGID; 
             gid < tileset.firstGID + tileset.columns * tileset.tileHeight / tileset.tileWidth;
             ++gid) {
            gidToTileset[gid] = &tilesets.back();
        }
    }

    return tilesets;
}

// Load layers
vector<vector<vector<unsigned>>>& MapLoader::loadLayers(XMLElement *mapElement) 
{
    // Loop through all <layer> elements
    for (XMLElement* layerElement = mapElement->FirstChildElement("layer");
         layerElement; 
         layerElement = layerElement->NextSiblingElement("layer")) {
        
        unsigned width = layerElement->UnsignedAttribute("width");
        unsigned height = layerElement->UnsignedAttribute("height");

        // Initialize the 2D grid for this layer
        vector<vector<unsigned>> layer(height, vector<unsigned>(width, 0));

        XMLElement* dataElement = layerElement->FirstChildElement("data");
        if (dataElement) {
            const char* encoding = dataElement->Attribute("encoding");
            if (encoding && string(encoding) == "csv") {
                // Parse CSV-encoded data
                string csvData = dataElement->GetText();
                size_t pos = 0, row = 0, col = 0;
                while ((pos = csvData.find(',')) != string::npos || !csvData.empty()) {
                    unsigned gid = stoi(csvData.substr(0, pos));
                    layer[row][col] = gid;
                    col++;
                    if (col >= width) {
                        col = 0;
                        row++;
                    }
                    if (pos == string::npos) break;
                    csvData.erase(0, pos + 1);
                }
            } else {
                cerr << "Error: Unsupported encoding or missing data." << endl;
            }
        }

        layers.push_back(layer);
    }

    return layers;
}

// Retrieve the tileset for a specific GID
const Tileset* MapLoader::getTilesetForGID(unsigned gid) {
    auto it = gidToTileset.find(gid);
    return (it != gidToTileset.end()) ? it->second : nullptr;
}

bool MapLoader::load()
{
    XMLDocument doc;
    if (doc.LoadFile(tmx_filename.c_str()) != XML_SUCCESS) {
        cerr << "Error loading TMX file: " << tmx_filename << endl;
        return false;
    }

    XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        cerr << "Error: No <map> element found in TMX file." << endl;
        return false;
    }

    loadTileSets(mapElement);
    loadLayers(mapElement);

    return true;
}


void MapLoader::printTilesets()
{
    for (auto tileset : tilesets) {
        cout << "Tileset:\n";
        cout << "    FirstGID: " << tileset.firstGID << endl;
        cout << "    Source: " << tileset.imgSource << endl;
        cout << "    Width: " << tileset.tileWidth << endl;
        cout << "    Height: " << tileset.tileHeight << endl;
        cout << "    Columns: " << tileset.columns << endl;
    }
}

void MapLoader::printLayers()
{
    for (auto layer : layers) {
        cout << "Layer:\n";
        for (int i = 0; i < layer.size(); ++i) {
            cout << "    ";
            for (int j = 0; j < layer.size(); ++j) {
                cout << layer[i][j] << " ";
            }
            cout << endl;
        }
    }
}