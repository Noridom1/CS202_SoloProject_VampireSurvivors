#include <iostream>
#include "Map/MapLoader.h"


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
        int id = obj->IntAttribute("id");

        // Create a FloatRect for each object and add it to the vector
        objects.push_back(sf::FloatRect(x, y, width, height));
        object_ids.push_back(id);
    }

    // Output the results to verify
    // for (const auto& rect : objects) {
    //     std::cout << "Object: x=" << rect.left << ", y=" << rect.top << ", width=" << rect.width << ", height=" << rect.height << std::endl;
    // }
    return true;
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
    
    cout << "Loading objects\n";
    try
    {
        if (!loadObjects(mapElement))
            throw("Failed to load Objects");
    }

    catch(const string& error)
    {
        std::cerr << error << "\n";
    }

    cout << "Loaded objects\n";
    size_t dotpos = map_name.find_last_of('.');
    string bg_path = map_name.substr(0, dotpos + 1) + "png";
    background = new Image(bg_path);

    cout << "Loaded succesfully from " + tmx_filename << endl;
    return true;
}


vector<int> MapLoader::getObjectIds()
{
    return this->object_ids;
}


vector<sf::FloatRect>& MapLoader::getObjects()
{
    return objects;
}

Image *MapLoader::getBackground()
{
    return background;
}

unsigned MapLoader::getMapSize()
{
    return mapSize;    
}

unsigned MapLoader::getTileSize()
{
    return tileSize;
}

void MapLoader::reset()
{
    this->objects.clear();
    this->object_ids.clear();
}

MapLoader &MapLoader::getInstance()
{
    static MapLoader mapLoader;
    return mapLoader;
}

MapLoader::~MapLoader()
{
    // for (auto ts : tilesets) {
    //     delete ts;
    // }
    delete background;
}