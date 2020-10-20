// RiverwayEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}