#include "GameEngine.h"
#include <iostream>

void testGameStates() {
    GameEngine game;
    string userCommand;

    while (true) {
        cout << "Enter command: ";
        cin >> userCommand;
        if (userCommand == "exit") break;
        game.command(userCommand);
    }
}

