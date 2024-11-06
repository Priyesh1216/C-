#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "Orders.h"
#include "Map.h"  

using namespace std;

class Player {
public:
    // Constructor
    Player(string name);

    // Copy constructor
    Player(const Player& other); 

    // Assignment operator
    Player& operator=(const Player& other); 

    // Destructor 
    ~Player();  

    // Returns a list of territories to defend
    vector<Territory*>* toDefend(Territory* territory_Name = nullptr);

    // Returns a list of territories to attack
    vector<Territory*>* toAttack(Territory* territory_Name = nullptr);

    // Method to issue orders
    void issueOrder(string order_Type);

    // Add the order to the list
    void addOrder(Order* order);

    // Access the player's list of orders
    OrdersList& getOrdersListObject();

    // Add an ally (for negotiation)
    void addAlly(Player* ally);

    // Returns any owned territory (used for negotiation checks)
    Territory* getAnyTerritory() const;

    // Getters and setters
    vector<Territory*>* getTerritories(); 
    void setTerritory(vector<Territory*>& territories, const string& directive, Territory* territory);
    string getName() const;

    // Outputting the player details
    friend ostream& operator<<(ostream& os, const Player& player);

private:
    string* name;  
    vector<Territory*>* playerTerritories;  
    vector<Territory*>* defendTerritories;  
    vector<Territory*>* attackTerritories;  
    OrdersList* orders;  
    unordered_set<Player*> allies;  // Set of allied players for negotiation
};
