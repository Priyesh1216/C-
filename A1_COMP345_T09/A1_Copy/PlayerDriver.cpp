#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>

void testPlayers() {
    // Create a player
    cout << "Creating player Alice..." << endl;
    Player player("Alice");

    // Test adding territories to the player
    cout << "\nAdding territories to player..." << endl;
    Territory* t1 = new Territory("Territory1");
    Territory* t2 = new Territory("Territory2");
    Territory* t3 = new Territory("Territory3");

    player.setTerritory(*player.getTerritories(), "add", t1);
    player.setTerritory(*player.getTerritories(), "add", t2);
    player.setTerritory(*player.getTerritories(), "add", t3);

    cout << "Player " << player.getName() << " now owns the following territories:" << endl;
    for (Territory* t : *player.getTerritories()) {
        cout << " - " << t->getTerritory_name() << endl;
    }

    // Test defending and attacking territories
    cout << "\nPlayer marking territories to defend and attack..." << endl;
    player.toDefend(t1);
    player.toAttack(t2);
    
    cout << "Territories to defend:" << endl;
    for (Territory* t : *player.toDefend()) {
        cout << " - " << t->getTerritory_name() << endl;
    }

    cout << "Territories to attack:" << endl;
    for (Territory* t : *player.toAttack()) {
        cout << " - " << t->getTerritory_name() << endl;
    }

    // Test issuing orders
    cout << "\nPlayer issuing orders..." << endl;
    player.issueOrder("Deploy");
    player.issueOrder("Advance");

    OrdersList& ordersList = player.getOrdersListObject();
    cout << "Orders issued by " << player.getName() << ":" << endl;

    // Loop through the player's orders and print them using the stream insertion operator
    const vector<Order*>& ordersVector = ordersList.getList(); // Get the vector reference
    for (Order* order : ordersVector) {  // Iterate over the vector directly
        if (order != nullptr) {
            cout << *order << endl;  // Use the stream insertion operator to print the order
        }
    }

    // Test stream operator for Player
    cout << "\nPlayer information:" << endl;
    cout << player << endl;

    // Clean up dynamically allocated memory
    delete t1;
    delete t2;
    delete t3;
}

/*
int main() {
    testPlayers();
    return 0;
}

*/


