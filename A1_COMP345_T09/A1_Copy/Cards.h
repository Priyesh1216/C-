#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Player.h"
#include "Orders.h"

using namespace std;

// Enum for card types stores user defined data for the different card types
enum CardType {
    BOMB,
    REINFORCEMENT,
    BLOCKADE,
    AIRLIFT,
    DIPLOMACY
};


/*
* * * * *  Card * * * * *
*/

// Forward declaration of classes
class Deck;
class Player;
class Hand;

class Card {

public:
    //Default Constructor
    Card(CardType type);

    // Copy Constructor
    Card(const Card& other);  

    // Destructor
    ~Card();

    // Returns the enum Card type and prints it out as a string
    string getType() const;

    // Returns the string representation of the Card type
    string getTypeAsString() const; 

    // Plays the card and adds an order to the player's order list
    void play(Player* player, Deck* deck);  

private:
    CardType cardType;
};


/*
* * * * *  Deck * * * * *
*/

class Deck {

public:
    // Default Constructor
    Deck();

    // Copy Constructor
    Deck(const Deck& other);  

    // Destructor
    ~Deck();

    // Draws a random card from the deck
    Card* draw();  

    // Return the card back to the deck
    void returnCardToDeck(Card* card);  
    
    // To get the deck of cards
    vector<Card*>& getDeckCards();

private:
    // Stores the cards in a vector list
    vector<Card*> cards;
};


/*
* * * * *  Hand * * * * *
*/

class Hand {

public:
    // Default Constructor
    Hand();

    // Copy Constructor
    Hand(const Hand& other);  

    // Destructor
    ~Hand();

    // Adds card to hand
    void addCard(Card* card);

    // Play all cards in the hand
    void playAll(Player* player, Deck* deck);  

    // To get the list of all cards in hand
    vector<Card*>& getHandCards();

private:
    // Stores the hand's cards in a vector list
    vector<Card*> cardsInHand;
};
