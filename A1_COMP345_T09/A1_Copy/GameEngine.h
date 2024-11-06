#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Player.h"

using namespace std;

// Class definition for GameEngine, which manages the game's state transitions and commands
class GameEngine {
public:
    // Constructor to initialize the game engine
    GameEngine();

    // Function to process user commands and manage state transitions
    void command(string userCommand);

    // Function to print the current state of the game
    void printState();

    // Function to test various game states (could be used for debugging)
    void testGameStates();

    void executeOrdersPhase();

private:
    // Enum to represent different states of the game
    enum State { 
        START, MAP_LOADED, MAP_VALIDATED, PLAYERS_ADDED, 
        ASSIGN_REINFORCEMENT, ISSUE_ORDERS, END_ISSUE_ORDER, 
        EXECUTE_ORDERS, END_EXEC_ORDERS, WIN, END 
    };

    // Variable to hold the current state of the game
    State currentState;

    // Function to transition from one state to another
    void transitionTo(State nextState);

    // Function to handle invalid commands
    void invalidCommand();

    // Function to validate if the user command is allowed in the current state
    bool validateCommand(string userCommand);
};

#endif
