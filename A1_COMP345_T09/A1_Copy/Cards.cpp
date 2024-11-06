#include "Cards.h"
#include "Player.h"
#include "Orders.h"
#include <iostream>
#include <algorithm>
#include <random>

/*
* * * * *  Card * * * * *
*/

// Default constructor
Card::Card(CardType type) : cardType(type) {}

// Copy constructor
Card::Card(const Card& other) : cardType(other.cardType) {}

// Deestructor
Card::~Card() = default;

// Returns the Card type and prints it out as a string
string Card::getType() const {
    return getTypeAsString();
}

// Returns the string representation of the Card type
string Card::getTypeAsString() const {
    switch (cardType) {
        case BOMB: return "BOMB";
        case REINFORCEMENT: return "REINFORCEMENT";
        case BLOCKADE: return "BLOCKADE";
        case AIRLIFT: return "AIRLIFT";
        case DIPLOMACY: return "DIPLOMACY";
        default: return "UNKNOWN"; // In case of an invalid type
    }
}

// Plays the card and adds a corresponding order to the player's order list
void Card::play(Player* player, Deck* deck) {
    Order* newOrder = nullptr;

    Territory* targetTerritory = player->getTerritories()->empty() ? nullptr : player->getTerritories()->front();
    int numArmies = 5;

    switch (cardType) {
        case BOMB:
            if (targetTerritory) {
                newOrder = new Bomb(player, targetTerritory);
            }
            break;
        case REINFORCEMENT:
            if (targetTerritory) {
                newOrder = new Deploy(player, targetTerritory, numArmies);
            }
            break;
        case BLOCKADE:
            if (targetTerritory) {
                newOrder = new Blockade(player, targetTerritory);
            }
            break;
        case AIRLIFT:
            if (targetTerritory) {
                newOrder = new Airlift(player, targetTerritory, targetTerritory, numArmies);
            }
            break;
        case DIPLOMACY:
            newOrder = new Negotiate(player, player);
            break;
    }

    // Adds order to player's list
    if (newOrder) {
        player->addOrder(newOrder);  
        cout << "Played card: " << getTypeAsString() << " and created order." << endl;
    } 
    
    // Error
    else {
        cerr << "Failed to create order for card: " << getTypeAsString() << endl;
    }

     // Returns the current card to the deck
    deck->returnCardToDeck(this);
    cout << "Card returned to Deck." << endl;
}

/*
* * * * *  Deck * * * * *
*/

Deck::Deck() {
    
}

// Copy Constructor
Deck::Deck(const Deck& other) {
    for (Card* card : other.cards) {
        cards.push_back(new Card(*card));  // Deep copy of each card
    }
    cout << "Deck copied." << endl;
}

// Destructor
Deck::~Deck() {
    // Clean up dynamically allocated cards
    for (Card* card : cards) {
        delete card;
    }
}

// Draws a random card from the deck
Card* Deck::draw() {
    // First checks if deck doesn'y contain any cards
    if (cards.empty()) {
        cout << "The deck is empty!" << endl;
        return nullptr;
    }

    // Gives access to a random number generator
    random_device rd;
    // Takes rd as starting point to generate a sequence of numbers 
    mt19937 gen(rd());

    // Shuffles the entire deck
    shuffle(cards.begin(), cards.end(), gen);  

    // Draws the last card (after shuffling)
    Card* drawnCard = cards.back();

    // Removes the drawn card from the deck
    cards.pop_back();  

    return drawnCard;
}

// Return card back to the deck
void Deck::returnCardToDeck(Card* card) {
    cards.push_back(card);
}

// Get the deck of cards
vector<Card*>& Deck::getDeckCards() {
    return cards;
}

/*
* * * * *  Hand * * * * *
*/

Hand::Hand() = default;

// Copy Constructor
Hand::Hand(const Hand& other) {
    for (Card* card : other.cardsInHand) {
        cardsInHand.push_back(new Card(*card));  // Deep copy of each card
    }
    cout << "Hand copied." << endl;
}

// Destructor
Hand::~Hand() {
    // Clean up cards in hand
    for (Card* card : cardsInHand) {
        delete card;
    }
}

// Add cards to hand
void Hand::addCard(Card* card) {
    cardsInHand.push_back(card);
}

// Play all cards in hand
void Hand::playAll(Player* player, Deck* deck) {
    for (Card* card : cardsInHand) {
        card->play(player, deck);
    }

    // Clear the hand
    cardsInHand.clear();
}

// Get the list of all cards in hand
vector<Card*>& Hand::getHandCards() {
    return cardsInHand;
}












