#pragma once

#include "Orders.h"
#include "Map.h"
#include <vector>
#include <string>

class Player {
private:
    // Name of the player
    std::string name;  
                            
    std::vector<Territory*> playerTerritories; 
    std::vector<Territory*> defendTerritories; // Territories to defend
    
    // Territories to attack
    std::vector<Territory*> attackTerritories; 
    
    // Orders issued by the player
    OrdersList orders;                       

public:
    // Constructor
    Player(const std::string& playerName);

    // Add or remove territories from the player's collection
    void setTerritory(std::vector<Territory*>& territories, const std::string& directive, Territory* territory);

    // Methods to manage territories to defend or attack
    std::vector<Territory*> toDefend(Territory* territory);
    std::vector<Territory*> toAttack(Territory* territory);

    // Method to issue orders
    void issueOrder(const std::string& orderType);

    // Access the player's list of orders
    OrdersList& getOrdersListObject();

    // Get the player's territories
    std::vector<Territory*>* getTerritories();

    // Get the player's name
    std::string getName() const;
};