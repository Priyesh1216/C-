#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declarations to avoid circular dependencies
class Player;
class Territory;

// Base Order class
class Order {
public:
    // Default constructor
    Order();

    // Virtual destructor for derived classes
    virtual ~Order() = default;

    // Virtual methods that must be overridden by derived classes
    // = 0 makes it so that it is pure virtual -- MUST be overridden by derived classes
    virtual bool isValid() = 0;
    virtual string getOrderType() const = 0;
    virtual void run() = 0;

    // friend keyword allows the << operator to access the private/protected members of the Order Class
    friend ostream& operator<<(ostream& os, const Order& order);
};

// The OrdersList class manages a list of orders through a list of Order pointers
class OrdersList {
private:
    // Pointers to order objects
    vector<Order *> orders;

public:
    // Constructor
    OrdersList();

    // Copy constructor 
    // Pass by reference avoids copying the object - const to ensure that the object is not modified during the copying process
    OrdersList(const OrdersList &other);

    // Destructor
    ~OrdersList();

    // Assignment operator - copy when one OrderList is assigned to another
    // copy the contents of one object into another object that has already been created
    OrdersList &operator=(const OrdersList &other);

    // Add an order (pointer to Order object) to the list 
    void add(Order *order);

    // Move an order from one position to another
    void move(int fromIndex, int toIndex);

    // Remove an order by index
    void remove(int index);

    // Run all orders and clear the list
    void run();

    // Return the list of orders (vector of pointers to Order objects)
    // const because we don't want to modify the list
    vector<Order *> getList() const;

    // Declare the operator << for printing an OrdersList
    friend ostream& operator<<(ostream& os, const OrdersList& orderList);
};

// Order subclasses with necessary attributes

class Deploy : public Order {
private:
    Player* player;
    Territory* targetTerritory;
    int numArmies;
public:
    Deploy(Player* player, Territory* target, int armies);
    bool isValid() override;
    string getOrderType() const override;
    void run() override;
};

class Advance : public Order {
private:
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numArmies;
public:
    Advance(Player* player, Territory* source, Territory* target, int armies);
    bool isValid() override;
    string getOrderType() const override;
    void run() override;
};

class Bomb : public Order {
private:
    Player* player;
    Territory* targetTerritory;
public:
    Bomb(Player* player, Territory* target);
    bool isValid() override;
    string getOrderType() const override;
    void run() override;
};

class Blockade : public Order {
private:
    Player* player;
    Territory* targetTerritory;
public:
    Blockade(Player* player, Territory* target);
    bool isValid() override;
    string getOrderType() const override;
    void run() override;
};

class Airlift : public Order {
private:
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numArmies;
public:
    Airlift(Player* player, Territory* source, Territory* target, int armies);
    bool isValid() override;
    string getOrderType() const override;
    void run() override;
};

class Negotiate : public Order {
private:
    Player* player;
    Player* targetPlayer;
public:
    Negotiate(Player* player, Player* target);
    bool isValid() override;
    string getOrderType() const override;
    void run() override;
};

// Function to test the OrdersList
void testOrdersLists();

