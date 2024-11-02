#include <iostream>

#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;

int main()
{
    Game::getInstance().run();
    cout << "hello world!";
    return 0;
}