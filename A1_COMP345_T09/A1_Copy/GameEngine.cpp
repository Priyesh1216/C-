#include "GameEngine.h" // Include the header file for GameEngine

// Constructor to initialize the game engine and set the initial state
GameEngine::GameEngine() {
    currentState = START;
    cout << "Game initialized. Current state: START\n";
}

// Process user commands and transition between game states
void GameEngine::command(string userCommand) {
    // Check if the command is valid for the current state
    if (!validateCommand(userCommand)) {
        invalidCommand();
        return;
    }

    // Handle transitions between states based on current state and user command
    if (currentState == START && userCommand == "loadmap") {
        transitionTo(MAP_LOADED);
    } else if (currentState == MAP_LOADED ) {
        if(userCommand == "validatemap") {
            transitionTo(MAP_VALIDATED);
        } else if (userCommand == "loadmap") {
            cout << "Map reloaded. Still in MAP_LOADED state.\n";
            return;
        }
        else{
            invalidCommand();
        }
    } else if (currentState == MAP_VALIDATED && userCommand == "addplayer") {
        transitionTo(PLAYERS_ADDED);
    } else if (currentState == PLAYERS_ADDED ) {
        if(userCommand == "assigncountries") {
            transitionTo(ASSIGN_REINFORCEMENT);
        } else if(userCommand == "addplayer") {
            cout << "Player added. Still in PLAYERS_ADDED state.\n";
            return;
        }
        else{
            invalidCommand();
        }
    } else if (currentState == ASSIGN_REINFORCEMENT && userCommand == "issueorder") {
        transitionTo(ISSUE_ORDERS);
    } else if (currentState == ISSUE_ORDERS) {
        if(userCommand == "execorder") {
            transitionTo(EXECUTE_ORDERS);
        } else if("issueorder") {
            cout << "Order issued. Still in ISSUE_ORDERS state.\n";
            return;
        }
        else{
            invalidCommand();
        }
    } else if (currentState == EXECUTE_ORDERS) {
        if(userCommand == "win") {
            transitionTo(WIN);
        } else if(userCommand == "execorder") {
            cout << "Order Executed. Still in EXECUTE_ORDERS state.\n";
            return;
        } else {
            invalidCommand();
        }
    } else if (currentState == WIN) {
        if(userCommand == "end") {
            transitionTo(END);
        } else if(userCommand == "play") {
            transitionTo(START);
        }
        else{
            invalidCommand();
        }
    } else {
        invalidCommand(); // If no valid state transition, show an error
    }
}

// Transition to the next game state and print the new state
void GameEngine::transitionTo(State nextState) {
    currentState = nextState;
    printState();
}

// Output an error message for invalid commands
void GameEngine::invalidCommand() {
    cout << "Invalid command for the current state. Please try again.\n";
}

// Validate if the user command is recognized
bool GameEngine::validateCommand(string userCommand) {
    vector<string> validCommands = {"loadmap", "validatemap", "addplayer", "assigncountries", "issueorder", "execorder", "win"};
    return find(validCommands.begin(), validCommands.end(), userCommand) != validCommands.end();
}

// Print the current state of the game
void GameEngine::printState() {
    switch (currentState) {
        case START: cout << "Current state: START\n"; break;
        case MAP_LOADED: cout << "Current state: MAP_LOADED\n"; break;
        case MAP_VALIDATED: cout << "Current state: MAP_VALIDATED\n"; break;
        case PLAYERS_ADDED: cout << "Current state: PLAYERS_ADDED\n"; break;
        case ASSIGN_REINFORCEMENT: cout << "Current state: ASSIGN_REINFORCEMENT\n"; break;
        case ISSUE_ORDERS: cout << "Current state: ISSUE_ORDERS\n"; break;
        case EXECUTE_ORDERS: cout << "Current state: EXECUTE_ORDERS\n"; break;
        case WIN: cout << "Current state: WIN\n"; break;
        default: cout << "Unknown state\n"; break;
    }
}
