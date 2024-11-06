#include "Map.h"
#include "Orders.h"
#include "Player.h"
#include <iostream>

void testOrders() {
    // Create players
    Player player1("Alice");
    Player player2("Bob");

    // Create territories
    Territory* territory1 = new Territory("Territory1");
    Territory* territory2 = new Territory("Territory2"); // Initially unowned
    Territory* territory3 = new Territory("Territory3");

    // Set ownership and add territories to players' lists using setTerritory
    player1.setTerritory(*player1.getTerritories(), "add", territory1); // Alice owns Territory1
    player2.setTerritory(*player2.getTerritories(), "add", territory3); // Bob owns Territory3

    // Establish adjacency
    territory1->addAdjacentTerritory(territory2); // Alice's territory1 is adjacent to unowned territory2
    territory2->addAdjacentTerritory(territory1);
    territory2->addAdjacentTerritory(territory3); // territory2 is adjacent to Bob's territory3
    territory3->addAdjacentTerritory(territory2);

  // Lambda to print a player's territories
    auto printInitialPlayerTerritories = [](Player& player) {
        cout << "Player " << player.getName() << "'s territories:" << endl;
        for (const auto& territory : *player.getTerritories()) {
            cout << "  - " << territory->getTerritory_name() << "\n\n" << endl;
        }
    };

    printInitialPlayerTerritories(player1);
    printInitialPlayerTerritories(player2);

    // ---- Deploy Order Test ----
    cout << "---- Deploy Order Test ----" << endl;
    Deploy deployOrder(&player1, territory1, 10); // Valid: Alice deploys to her own territory
    deployOrder.run();

    Deploy invalidDeployOrder(&player1, territory3, 5); // Invalid: Alice deploys to Bob's territory
    invalidDeployOrder.run();

    // ---- Advance Order Test ----
    cout << "\n---- Advance Order Test ----" << endl;
    Advance advanceOrder(&player1, territory1, territory2, 5); // Alice advances to conquer territory2
    advanceOrder.run();

    Advance invalidAdvanceOrder(&player1, territory3, territory2, 5); // Invalid: Alice does not own territory3
    invalidAdvanceOrder.run();

    // ---- Bomb Order Test ----
    cout << "\n---- Bomb Order Test ----" << endl;
    Bomb bombOrder(&player1, territory3); // Valid: Alice bombs Bob's adjacent territory3
    bombOrder.run();

    Bomb invalidBombOrder(&player1, territory1); // Invalid: Alice tries to bomb her own territory
    invalidBombOrder.run();

    // ---- Airlift Order Test ----
    cout << "\n---- Airlift Order Test ----" << endl;
    Airlift airliftOrder(&player1, territory1, territory2, 7); // Valid airlift to territory2 owned by Alice
    airliftOrder.run();

    Airlift invalidAirliftOrder(&player1, territory1, territory3, 7); // Invalid: Alice airlifts to Bob's territory
    invalidAirliftOrder.run();

    // ---- Blockade Order Test ----
    cout << "\n---- Blockade Order Test ----" << endl;
    Blockade blockadeOrder(&player1, territory1); // Valid blockade on Alice's territory1
    blockadeOrder.run();

    Blockade invalidBlockadeOrder(&player1, territory3); // Invalid: Bob owns territory3
    invalidBlockadeOrder.run();

    // ---- Negotiate Order Test ----
    cout << "\n---- Negotiate Order Test ----" << endl;
    Negotiate negotiateOrder(&player1, &player2); // Valid negotiation between Alice and Bob
    negotiateOrder.run();

    Negotiate invalidNegotiateOrder(&player1, &player1); // Invalid: Alice cannot negotiate with herself
    invalidNegotiateOrder.run();

    // Print each player's territories after orders
    cout << "\n---- Player Territories After Orders ----" << endl;

    // Lambda to print a player's territories
    auto printPlayerTerritories = [](Player& player) {
        cout << "Player " << player.getName() << "'s territories:" << endl;
        for (const auto& territory : *player.getTerritories()) {
            cout << "  - " << territory->getTerritory_name() << "\n\n" << endl;
        }
    };

    printPlayerTerritories(player1);
    printPlayerTerritories(player2);

    // Clean up
    delete territory1;
    delete territory2;
    delete territory3;
}


