#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Image.h"
#include <iostream>
#include <Map/MapLoader.h>


class Tile{
public:
    Tile(int GId) : 
        GId(GId), 
        rect(MapLoader::getInstance().getTileInTileset(GId)), 
        tileset(MapLoader::getInstance().getTilesetForGID(GId))
    {
        //cout << "Loaded tile with GId: " << GId << endl;
    }
    
    int getGId() {
        return this->GId;
    }

    void draw(sf::RenderWindow *window, sf::Vector2f pos) {
        if (GId == 0)
            return;
        //cout << GId << endl;
        //cout << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << endl;
        sf::Sprite& sprite = tileset->img->getSprite();
        //cout << "Got Sprite of " << GId << endl;
        sprite.setTextureRect(rect);
        sprite.setPosition(pos);
        window->draw(sprite);
    }
private:
    int GId;
    const Tileset* tileset;
    sf::IntRect rect;
};

class TileFlyweightFactory {
public:
    
    static Tile& getTileImg(int GId) {
        static std::unordered_map<int, std::unique_ptr<Tile>> tileImage;
        //std::cout << "GId: " << GId << endl;

        if (tileImage.find(GId) == tileImage.end()) {
            tileImage[GId] = std::make_unique<Tile>(GId);
        }
        return *tileImage[GId];
    }

private:
    std::vector<Tileset> *tilesets;
};

#endif