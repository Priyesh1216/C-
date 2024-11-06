#include "MainDriver.h"
#include <iostream>

int main() {

    cout << "\n\n\n---------------------------Testing Map functionality...---------------------------" << endl;
    testLoadMaps();

    cout << "\n\n\n---------------------------Testing Player functionality...---------------------------" << endl;
    testPlayers();

    cout << "\n\n\n---------------------------Testing Orders functionality...---------------------------" << endl;
    testOrders();

    cout << "\n\n\n---------------------------Testing Cards functionality...---------------------------" << endl;
    testCards();

    cout << "\n\n\n---------------------------Testing Game Engine functionality...---------------------------" << endl;
    testGameStates();

    return 0;
}
