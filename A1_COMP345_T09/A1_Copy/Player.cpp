#include "Player.h"
#include "Map.h"
#include <iostream>
//#include <algorithm>  

// Constructor
Player::Player(string name) {
    this->name = new string(name); 
    this->playerTerritories = new vector<Territory*>();  
    this->defendTerritories = new vector<Territory*>();  
    this->attackTerritories = new vector<Territory*>();  
    this->orders = new OrdersList();  
}

// Copy Constructor
Player::Player(const Player& other) {
    name = new string(*other.name);  
    playerTerritories = new vector<Territory*>(*other.playerTerritories); 
    defendTerritories = new vector<Territory*>(*other.defendTerritories);  
    attackTerritories = new vector<Territory*>(*other.attackTerritories);  
    orders = new OrdersList(*other.orders);  
    allies = other.allies;
}

// Assignment Operator
Player& Player::operator=(const Player& other) {
    if (this == &other) 
        return *this;  

    delete name;
    delete playerTerritories;
    delete defendTerritories;
    delete attackTerritories;
    delete orders;

    name = new string(*other.name);
    playerTerritories = new vector<Territory*>(*other.playerTerritories);
    defendTerritories = new vector<Territory*>(*other.defendTerritories);
    attackTerritories = new vector<Territory*>(*other.attackTerritories);
    orders = new OrdersList(*other.orders);  
    allies = other.allies;

    return *this;
}

// Destructor
Player::~Player() {
    delete name;  
    delete playerTerritories;  
    delete defendTerritories;  
    delete attackTerritories;  
    delete orders;  
}

// Method to retrieve player's territories
vector<Territory*>* Player::getTerritories() {
    return playerTerritories;  
}

// Method to add or remove territories
// Player.cpp
void Player::setTerritory(vector<Territory*>& territories, const string& directive, Territory* territory) {
    if (directive == "add") {
        // Set ownership and add territory to player's list
        territory->setOwner(this);
        territories.push_back(territory);
    } 
    else if (directive == "remove") {
        // Remove ownership and territory from player's list
        territories.erase(remove(territories.begin(), territories.end(), territory), territories.end());
        territory->setOwner(nullptr); // Reset the owner to nullptr
    } 
    else {
        cerr << "Invalid directive. Use 'add' or 'remove'." << endl;
    }
}


// Returns a list of territories to defend
vector<Territory*>* Player::toDefend(Territory* territory_Name) {
    if (territory_Name != nullptr) {
        defendTerritories->push_back(territory_Name);  
    }
    return defendTerritories;
}

// Returns a list of territories to attack
vector<Territory*>* Player::toAttack(Territory* territory_Name) {
    if (territory_Name != nullptr) {
        attackTerritories->push_back(territory_Name);  
    }
    return attackTerritories;
}


// Method to issue orders with placeholder parameters
void Player::issueOrder(string order_Type) {
    Order* newOrder = nullptr;
    
    // Placeholder values for required arguments
    Territory* targetTerritory = playerTerritories->empty() ? nullptr : playerTerritories->front(); // First owned territory
    int numArmies = 5; // Example value for armies

    // Create an appropriate order based on the order type
    if (order_Type == "Deploy" && targetTerritory) {
        newOrder = new Deploy(this, targetTerritory, numArmies);
    } 
    
    else if (order_Type == "Advance" && targetTerritory) {
        // Advance (Player* player, Territory* source, Territory* target, int armies)
        // "this" is used for Player* player
        // "this" points to the instance of the class on which the function is being called
        newOrder = new Advance(this, targetTerritory, targetTerritory, numArmies); // source and target as example
    } 
    
    else if (order_Type == "Bomb" && targetTerritory) {
        // Bomb(Player* player, Territory* target)
        newOrder = new Bomb(this, targetTerritory);
    } 
    
    else if (order_Type == "Blockade" && targetTerritory) {
        // Blockade(Player* player, Territory* target)
        newOrder = new Blockade(this, targetTerritory);
    } 
    
    else if (order_Type == "Airlift" && targetTerritory) {
        //Airlift(Player* player, Territory* source, Territory* target, int armies)
        newOrder = new Airlift(this, targetTerritory, targetTerritory, numArmies);
    } 
    
    else if (order_Type == "Negotiate") {
        // Negotiate(Player* player, Player* target)
        newOrder = new Negotiate(this, this); // Example: negotiating with self for placeholder
    }

    // Add order if successfully created
    if (newOrder != nullptr) {
        addOrder(newOrder);
    } 
    
    else {
        cerr << "Failed to create order of type: " << order_Type << std::endl;
    }
}

// Add an order to the player's orders list
void Player::addOrder(Order* order) {
    orders->add(order);  
}

// Returns a reference to the player's orders list
OrdersList& Player::getOrdersListObject() {
    return *orders;  
}

// Add an ally (for negotiation purposes)
void Player::addAlly(Player* ally) {
    allies.insert(ally);
    cout << "Ally added: " << ally->getName() << endl;
}

// Returns any owned territory (used for negotiation checks)
Territory* Player::getAnyTerritory() const {
    return playerTerritories->empty() ? nullptr : playerTerritories->front();
}

// Returns the player's name
string Player::getName() const {
    return *name;  
}

// Output of player information
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player Name: " << *player.name;
    return os;
}



