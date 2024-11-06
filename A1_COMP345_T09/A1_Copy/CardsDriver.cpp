#include "Cards.h"
#include "Player.h"
#include "Orders.h"
#include <iostream>

void testCards() {
    // Create a new deck
    Deck deck;

    // Create a new player
    Player player("TestPlayer");

    // Create a new hand
    Hand hand;

    // Draw cards from the deck and add them to the player's hand
    for (int i = 0; i < 5; ++i) {
        Card* drawnCard = deck.draw();
        if (drawnCard) {
            hand.addCard(drawnCard);
            cout << "Card drawn and added to hand: " << drawnCard->getTypeAsString()<< endl;
        }
    }

    // Play all cards in the hand
    cout << "\nPlaying all cards in the hand...\n" << endl;
    hand.playAll(&player, &deck);
}