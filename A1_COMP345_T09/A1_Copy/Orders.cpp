#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <cstdlib> // For random attack calculation

// Base Order constructor
Order::Order() {}

// Default constructor for OrdersList
OrdersList::OrdersList() = default;

// Copy constructor (copy of OrdersList)
// Create a new object as a copy of the existing object
// Iterate over the orders list from the other OrdersList and pushes the same pointers to the new orders list
// So the new OrdersList shares the same Order objects as the original one (both point to the same object in memory - on the heap)
OrdersList::OrdersList(const OrdersList &other) {
    for (Order *order : other.orders) {
        orders.push_back(order);  
    }
}

// Destructor - Delete all orders in the list
OrdersList::~OrdersList() {
    for (Order *order : orders) {
        delete order;
    }
}

// Assignment Operator -- could be used if a player wants to replace their orders
// copy the contents of one object into another object that has already been created
OrdersList &OrdersList::operator=(const OrdersList &other) {
    // Check if the other OrdersList is the same as the current OrdersList
    if (this == &other) {
        return *this;
    }

    // Delete up existing orders to avoid memory leaks
    for (Order *order : orders) {
        delete order;
    }
    orders.clear();

    // Copy the other orders list (shallow copy)
    for (Order *order : other.orders) {
        orders.push_back(order);  
    }

    return *this;
}

// Add an order to the end of the list
// Adds a pointer to an Order object to the OrdersList
void OrdersList::add(Order *order) {
    orders.push_back(order);
}

// Remove an order by index
void OrdersList::remove(int index) {
    // Parameter checking
    if (index >= 0 && index < orders.size()) {
        // Delete the memory for the Order object
        delete orders[index];  
      
        // .begin () needed because .erase () takes an iterator hence a integer value would be invalid
        // Use pointer arithmetic to move the iterator forward by index positions
        orders.erase(orders.begin() + index);  
    }
}

// Move an order from one position to another
void OrdersList::move(int fromIndex, int toIndex) {
    // Parameter checking
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        // Store the order in temp variable
        Order *temp = orders[fromIndex];
        orders.erase(orders.begin() + fromIndex);
        // .insert (iterator index, element to insert)
        orders.insert(orders.begin() + toIndex, temp);
    }
}

// Run all orders if they are valid and clear the list for the next
void OrdersList::run() {
    for (Order *order : orders) {
        if (order->isValid()) {
            order->run();
        }
    }
    orders.clear();
}

// Return the list of orders
vector<Order *> OrdersList::getList() const {
    return orders;
}

// Define the operator<< for OrdersList
// Prints the entire OrdersList iterating through each order
ostream& operator<<(ostream& os, const OrdersList& orderList) {
    for (Order *order : orderList.orders) {
        // Print the order using the overloaded operator<< for Order (below)
        os << *order << endl;
    }
    return os;
}

// Prints a single order and its type
ostream& operator<<(ostream& os, const Order& order) {
    os << "Order Type: " << order.getOrderType();
    return os;
}

// ________________Order Constructors___________________

// Deploy Constructor
Deploy::Deploy(Player* player, Territory* target, int armies) {
    this->player = player;
    this->targetTerritory = target;
    this->numArmies = armies;
}

// Advance Constructor
Advance::Advance(Player* player, Territory* source, Territory* target, int armies) {
    this->player = player;
    this->sourceTerritory = source;
    this->targetTerritory = target;
    this->numArmies = armies;
}

// Bomb Constructor
Bomb::Bomb(Player* player, Territory* target) {
    this->player = player;
    this->targetTerritory = target;
}

// Blockade Constructor
Blockade::Blockade(Player* player, Territory* target) {
    this->player = player;
    this->targetTerritory = target;
}

// Airlift Constructor
Airlift::Airlift(Player* player, Territory* source, Territory* target, int armies) {
    this->player = player;
    this->sourceTerritory = source;
    this->targetTerritory = target;
    this->numArmies = armies;
}

// Negotiate Constructor
Negotiate::Negotiate(Player* player, Player* target) {
    this->player = player;
    this->targetPlayer = target;
}

// ________________Order Subclasses with Execution Logic___________________

// Deploy Order
bool Deploy::isValid() { 
    // Assuming the player owns the target territory
    return targetTerritory->getOwner() == player; 
}

string Deploy::getOrderType() const { 
    return "Deploy"; 
}

void Deploy::run() {
    if (isValid()) {
        targetTerritory->addArmies(numArmies);
        cout << "Deploy order executed: " << numArmies << " units deployed to " 
             << targetTerritory->getTerritory_name() << endl;
    } else {
        cout << "Deploy order invalid: Target territory does not belong to player.\n";
    }
}

// Advance Order
bool Advance::isValid() { 
    return sourceTerritory->getOwner() == player && 
           (sourceTerritory->isAdjacent(targetTerritory) || targetTerritory->getOwner() != player); 
}

string Advance::getOrderType() const { 
    return "Advance"; 
}

void Advance::run() {
    if (!isValid()) {
        cout << "Advance order invalid: Either source territory is not owned by player or target is non-adjacent.\n";
        return;
    }

    if (targetTerritory->getOwner() == player) {
        targetTerritory->addArmies(numArmies);
        sourceTerritory->removeArmies(numArmies);
        cout << "Advanced " << numArmies << " units to " << targetTerritory->getTerritory_name() << endl;
    } 
    
    else {
        int attackUnits = numArmies;
        int defenseUnits = targetTerritory->getArmies();
        sourceTerritory->removeArmies(attackUnits);
        
        while (attackUnits > 0 && defenseUnits > 0) {
            if ((rand() % 100) < 60) defenseUnits--;  // Attack succeeds 60% of the time
            if ((rand() % 100) < 70) attackUnits--;   // Defense succeeds 70% of the time
        }
        
        if (defenseUnits <= 0) {
            // Conquered: Remove territory from the previous owner's list
            Player* previousOwner = targetTerritory->getOwner();
            if (previousOwner != nullptr) {
                previousOwner->setTerritory(*previousOwner->getTerritories(), "remove", targetTerritory);
            }

            // Set the new owner and add the territory to the conqueror's list
            targetTerritory->setOwner(player);
            player->setTerritory(*player->getTerritories(), "add", targetTerritory);

            // Update the remaining attacking units in the conquered territory
            targetTerritory->setArmies(attackUnits);
            cout << "Territory " << targetTerritory->getTerritory_name() 
                 << " conquered! Remaining armies: " << attackUnits << endl;
        } else {
            // Attack failed, update remaining defense units
            targetTerritory->setArmies(defenseUnits);
            cout << "Attack failed. Remaining defense: " << defenseUnits << endl;
        }
    }
}

// Bomb Order
bool Bomb::isValid() {
    if (targetTerritory->getOwner() == player) {
        cout << "Bomb order invalid: Cannot bomb own territory." << endl;
        return false;
    }

    bool isAdjacentFound = false;
    cout << "Checking adjacency for Bomb order. Player's territories:" << endl;
    for (Territory* territory : *player->getTerritories()) {
        cout << "  Owned territory: " << territory->getTerritory_name() << endl;
        if (territory->isAdjacent(targetTerritory)) {
            isAdjacentFound = true;
            break;
        }
    }

    if (!isAdjacentFound) {
        cout << "Bomb order invalid: No adjacent territory found for target." << endl;
    }
    return isAdjacentFound;
}




string Bomb::getOrderType() const { 
    return "Bomb"; 
}

void Bomb::run() {
    if (isValid()) {
        targetTerritory->setArmies(targetTerritory->getArmies() / 2);
        cout << "Bomb order executed: Armies in " << targetTerritory->getTerritory_name() << " halved.\n";
    } 
    
    else {
        cout << "Target territory either belongs to player or is not adjacent.\n";
    }
}

// Blockade Order
bool Blockade::isValid() { 
    return targetTerritory->getOwner() == player; 
}

string Blockade::getOrderType() const { 
    return "Blockade"; 
}

void Blockade::run() {
    if (isValid()) {
        targetTerritory->doubleArmies();
        targetTerritory->setOwner(nullptr); // Assumes nullptr is the Neutral player
        cout << "Blockade order executed: " << targetTerritory->getTerritory_name() 
             << " now neutral with doubled armies.\n";
    } else {
        cout << "Blockade order invalid: Target territory does not belong to player.\n";
    }
}

// Airlift Order
bool Airlift::isValid() { 
    return sourceTerritory->getOwner() == player && targetTerritory->getOwner() == player; 
}

string Airlift::getOrderType() const { 
    return "Airlift"; 
}

void Airlift::run() {
    if (isValid()) {
        targetTerritory->addArmies(numArmies);
        sourceTerritory->removeArmies(numArmies);
        cout << "Airlift order executed: " << numArmies << " units moved to " 
             << targetTerritory->getTerritory_name() << endl;
    } else {
        cout << "Airlift order invalid: Either source or target does not belong to player.\n";
    }
}

// Negotiate Order
bool Negotiate::isValid() { 
    return targetPlayer != player; 
}

string Negotiate::getOrderType() const { 
    return "Negotiate"; 
}

void Negotiate::run() {
    if (isValid()) {
        player->addAlly(targetPlayer);  // Adds to ally list for the turn
        targetPlayer->addAlly(player);
        cout << "Negotiate order executed: " << player->getName() << " and " 
             << targetPlayer->getName() << " cannot attack each other this turn.\n";
    } else {
        cout << "Negotiate order invalid: Cannot negotiate with self.\n\n";
    }
}
