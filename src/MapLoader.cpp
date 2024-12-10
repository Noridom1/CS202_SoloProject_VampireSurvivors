#include <iostream>
#include "Map/MapLoader.h"

bool MapLoader::loadTileSets(XMLElement *mapElement, const string& map_name) 
{
    // Loop through all <tileset> elements
    for (XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
         tilesetElement; 
         tilesetElement = tilesetElement->NextSiblingElement("tileset")) {
        
        Tileset *tileset = new Tileset;
        tileset->firstGID = tilesetElement->UnsignedAttribute("firstgid");
        cout << tileset->firstGID << endl;

        // External tileset reference (tsx file)
        const char* source = tilesetElement->Attribute("source");
        XMLElement* imageElement = tilesetElement->FirstChildElement("image");
        if (imageElement) {
            tileset->imgSource = imageElement->Attribute("source");
            tileset->img = new Image(map_name + "/" + tileset->imgSource);
            tileset->tileWidth = tilesetElement->UnsignedAttribute("tilewidth");
            tileset->tileHeight = tilesetElement->UnsignedAttribute("tileheight");
            tileset->columns = tilesetElement->UnsignedAttribute("columns");
            tileset->tileCount = tilesetElement->UnsignedAttribute("tilecount");
            tileset->rows = tileset->tileCount / tileset->columns;
        }

        tilesets.push_back(tileset);
        //cout << "push back tileset " << tileset->firstGID << endl;
        // Populate gidToTileset map for all tiles in this tileset
        for (unsigned gid = tileset->firstGID; gid - tileset->firstGID < tileset->tileCount; ++gid) {
            gidToTileset[gid] = tilesets.back();
            //cout << gid << endl;
            if (gid == 484u) {
                if (gidToTileset[gid] != nullptr)
                    cout << gidToTileset[gid]->firstGID;
                else {
                    cout << "nulllptr\n";
                    return false;
                }
            }
        }
    }

    cout << "Finished loading tilesets\n";
    this->printTilesets();
    return true;
}

// Load layers
bool MapLoader::loadLayers(XMLElement *mapElement) 
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
                return false;
            }
        }

        layers.push_back(layer);
    }
    return true;
}

bool MapLoader::loadObjects(XMLElement *mapElement)
{
    XMLElement* objectGroup = mapElement->FirstChildElement("objectgroup");
    if (objectGroup == nullptr) {
        std::cerr << "No object group found in the XML!" << std::endl;
        return false;
    }

    for (XMLElement* obj = objectGroup->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object")) {
        // Extract the attributes (x, y, width, height)
        float x = obj->FloatAttribute("x");
        float y = obj->FloatAttribute("y");
        float width = obj->FloatAttribute("width");
        float height = obj->FloatAttribute("height");

        // Create a FloatRect for each object and add it to the vector
        objects.push_back(sf::FloatRect(x, y, width, height));
    }

    // Output the results to verify
    for (const auto& rect : objects) {
        std::cout << "Object: x=" << rect.left << ", y=" << rect.top << ", width=" << rect.width << ", height=" << rect.height << std::endl;
    }
    return true;
}

const Tileset* MapLoader::getTilesetForGID(unsigned gid) {
    // auto it = gidTotileset->find(gid);
    // return (it != gidTotileset->end()) ? it->second : nullptr;
    if (gid == 0) {
        return nullptr;
    }
    if (gid == 484) {
        cout << "Get Tileset for 484: " << gidToTileset[gid] << endl;
    }
    return gidToTileset[gid];
}

bool MapLoader::load(const string& tmx_filename)
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

    this->mapSize = mapElement->UnsignedAttribute("width");
    this->tileSize = mapElement->UnsignedAttribute("tilewidth");

    const string map_name = tmx_filename;
    size_t slashPosition = map_name.find_last_of('/');
    string name = map_name.substr(0, slashPosition + 1);
    cout << name << endl;
    
    try
    {
        if(!loadTileSets(mapElement, name))
            throw("Failed to load Tilesets");
        if (!loadLayers(mapElement))
            throw("Failed to load Layers");
        if (!loadObjects(mapElement))
            throw("Failed to load Objects");
    }
    catch(const string& error)
    {
        std::cerr << error << "\n";
    }
    


    cout << "Loaded succesfully from " + tmx_filename << endl;
    return true;
}


void MapLoader::printTilesets()
{
    for (auto tileset : tilesets) {
        cout << "Tileset:\n";
        cout << "    FirstGID: " << tileset->firstGID << endl;
        cout << "    Source: " << tileset->imgSource << endl;
        cout << "    Width: " << tileset->tileWidth << endl;
        cout << "    Height: " << tileset->tileHeight << endl;
        cout << "    Columns: " << tileset->columns << endl;
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

void MapLoader::printTilesetsId()
{
    for (auto ts : this->tilesets){
        cout << ts << endl;
    }
    //cout << "Tileset with id 484: " << *this->gidToTileset[484] << endl;
}

sf::IntRect MapLoader::getTileInTileset(unsigned gid)
{
    sf::IntRect rect(0, 0, 0, 0);
    if (gid) {
        const Tileset* ts = getTilesetForGID(gid);
        unsigned lid = gid - ts->firstGID;
        rect.left = (lid % ts->columns) * ts->tileWidth;
        rect.top = (lid / ts->columns) * ts->tileHeight;
        rect.width = ts->tileWidth;
        rect.height = ts->tileHeight;
        //cout << "MapLoader::getTileInTileset: " << gid << endl;
    }

    return rect;

}

vector<Tileset*>& MapLoader::getTilesets()
{
    return tilesets;
}

vector<vector<vector<unsigned>>>& MapLoader::getLayers()
{
    return layers;
}

vector<sf::FloatRect>& MapLoader::getObjects()
{
    return objects;
}
unsigned MapLoader::getMapSize()
{
    return mapSize;    
}

unsigned MapLoader::getTileSize()
{
    return tileSize;
}

MapLoader &MapLoader::getInstance()
{
    static MapLoader mapLoader;
    return mapLoader;
}

MapLoader::~MapLoader()
{
    for (auto ts : tilesets) {
        delete ts;
    }
}