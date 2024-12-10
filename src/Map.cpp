#include "Map/Map.h"
#include <algorithm>

// Map::Map(unsigned tile_size, int mapSize) : uTileSize(tile_size), fTileSize(static_cast<float>(uTileSize)), mapSize(mapSize) 
// {
//     font.loadFromFile("../assets/fonts/Poppins-Bold.ttf");
//     MouseInfo.setColor(sf::Color::Blue);
//     MouseInfo.setCharacterSize(30);
//     MouseInfo.setFont(font);

//     tile.setSize(sf::Vector2f(fTileSize, fTileSize));
//     tile.setFillColor(sf::Color::White);

//     tileSelector.setSize(sf::Vector2f(fTileSize, fTileSize));
//     tileSelector.setFillColor(sf::Color::Transparent);
//     tileSelector.setOutlineColor(sf::Color::Green);
//     tileSelector.setOutlineThickness(1.0f);

//     gridMap.resize(mapSize, vector<sf::RectangleShape>(mapSize));
//     for (int i = 0; i < mapSize; ++i) {
//         //cout << i << endl;
//         gridMap[i].resize(mapSize);
//         for (unsigned j = 0; j < mapSize; ++j) {
//             gridMap[i][j].setFillColor(sf::Color::White);
//             gridMap[i][j].setOutlineColor(sf::Color::Black);
//             gridMap[i][j].setOutlineThickness(1.f);
//             gridMap[i][j].setSize(sf::Vector2f(fTileSize, fTileSize));
//             gridMap[i][j].setPosition(i * fTileSize, j * fTileSize);
//         }
//     }
// }

Map::Map(const string &filename)
{
    font.loadFromFile("../assets/fonts/Poppins-Bold.ttf");
    MouseInfo.setColor(sf::Color::Blue);
    MouseInfo.setCharacterSize(30);
    MouseInfo.setFont(font);

    try {
        if (!MapLoader::getInstance().load(filename))
            throw("Cannot load map from " + filename);
    }
        
    catch (string str) {
        cout << str << endl;
    }

    this->uTileSize = MapLoader::getInstance().getTileSize();
    this->fTileSize = static_cast<float>(uTileSize);
    this->mapSize = MapLoader::getInstance().getMapSize();

    tile.setSize(sf::Vector2f(fTileSize, fTileSize));
    tile.setFillColor(sf::Color::White);

    tileSelector.setSize(sf::Vector2f(fTileSize, fTileSize));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineColor(sf::Color::Green);
    tileSelector.setOutlineThickness(1.0f);

    this->layers = MapLoader::getInstance().getLayers();
    this->objects = MapLoader::getInstance().getObjects();
    this->numLayers = layers.size();

    tileLayers.resize(numLayers, vector<vector<Tile*>>(mapSize));
    cout << "Resized tileLayers successfully" << endl;
    //gridMap.resize(mapSize, vector<sf::RectangleShape>(mapSize));

    for (int k = 0; k < numLayers; ++k) {
        tileLayers[k].resize(mapSize, vector<Tile*>(mapSize));
        for (int i = 0; i < mapSize; ++i) {
            tileLayers[k][i].resize(mapSize);
            for (int j = 0; j < mapSize; ++j) {
                if (layers[k][i][j] == 0) {
                    tileLayers[k][i][j] = nullptr;
                }
                else tileLayers[k][i][j] = &TileFlyweightFactory::getTileImg(layers[k][i][j]);
            }
        }
        cout << "Finished layer " << k << endl;
    }
    // for (unsigned i = 0; i < mapSize; ++i) {
    //     //cout << i << endl;
    //     gridMap[i].resize(mapSize);

    //     for (unsigned j = 0; j < mapSize; ++j) {
    //         tileMap[i][j] = TileFlyweightFactory::getTileImg();
    //         gridMap[i][j].setFillColor(sf::Color::White);
    //         gridMap[i][j].setOutlineColor(sf::Color::Black);
    //         gridMap[i][j].setOutlineThickness(1.f);
    //         gridMap[i][j].setSize(sf::Vector2f(fTileSize, fTileSize));
    //         gridMap[i][j].setPosition(i * fTileSize, j * fTileSize);
    //     }

    // }
    cout << "Constructed map successfully from " + filename << endl;
}

Map::~Map()
{
    for (auto tileLayer : tileLayers){
        for (int i = 0; i < mapSize; ++i) {
            for (int j = 0; j < mapSize; ++j)
                if (tileLayer[i][j])
                    delete tileLayer[i][j];
        }
    }
}

void Map::update(sf::RenderWindow *window, sf::View *view, sf::Vector2f playerPos)
{
    updateMousePos(window, view);
    updateRenderRegion(view);
}

void Map::updateRenderRegion(sf::View *view)
{
    sf::Vector2f playerPos = view->getCenter();
    //cout << "Player position: " << playerPos.x << " " << playerPos.y << "\n";
    renderFrom = sf::Vector2i(playerPos.y / uTileSize - 10, playerPos.x / uTileSize - 10);
    renderFrom.x = max(renderFrom.x, 0);
    renderFrom.x = min(renderFrom.x, mapSize - 1);
    renderFrom.y = max(renderFrom.y, 0);
    renderFrom.y = min(renderFrom.y, mapSize - 1);
    renderTo = sf::Vector2i(playerPos.y / uTileSize + 10, playerPos.x / uTileSize + 10);
    renderTo.x = max(renderTo.x, 0);
    renderTo.x = min(renderTo.x, mapSize - 1);
    renderTo.y = max(renderTo.y, 0);
    renderTo.y = min(renderTo.y, mapSize - 1);

}

void Map::updateMousePos(sf::RenderWindow *window, sf::View *view)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);
    window->setView(*view);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
    mousePosGrid.x = mousePosView.x / uTileSize - (mousePosView.x < 0);
    mousePosGrid.x = max(0, mousePosGrid.x);
    mousePosGrid.x = min(mousePosGrid.x, mapSize - 1);
    mousePosGrid.y = mousePosView.y / uTileSize - (mousePosView.y < 0);
    mousePosGrid.y = max(0, mousePosGrid.y);
    mousePosGrid.y = min(mousePosGrid.y, mapSize - 1);

    window->setView(window->getDefaultView());

    std::stringstream ss;
    ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
        << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
        << "View: "  << mousePosView.x << " " << mousePosView.y << "\n"
        << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
        << "Render: from " << renderFrom.x << " " << renderFrom.y << " to " << renderTo.x << " " << renderTo.y << "\n"
        << "Tile GID: " << this->tileLayers[0][mousePosGrid.x][mousePosGrid.y]->getGId();

    MouseInfo.setString(ss.str());
    MouseInfo.setPosition(view->getCenter().x - view->getSize().x / 2.0f, view->getCenter().y - view->getSize().y / 2.f);
    tileSelector.setPosition(mousePosGrid.x * fTileSize, mousePosGrid.y * fTileSize);
}

void Map::draw(sf::RenderWindow *window)
{
    //window->draw(tile);
    //int cnt = 0;
    for (auto tileLayer : tileLayers) {
        //if (cnt != 0) continue;;
        for (int i = renderFrom.x; i <= renderTo.x; ++i) {
            for (int j = renderFrom.y; j <= renderTo.y; ++j) {
                if (tileLayer[i][j])
                    tileLayer[i][j]->draw(window, sf::Vector2f(j * fTileSize, i * fTileSize));
            }
        }
        //++cnt;  
    }

    for (auto obj : objects) {
        sf::RectangleShape rect(sf::Vector2f(obj.width, obj.height));
        rect.setPosition(obj.getPosition());
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(1.3f);
        window->draw(rect);
    }
    
    window->draw(tileSelector);
    window->draw(MouseInfo);

}

