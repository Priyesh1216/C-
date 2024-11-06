#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

class Player;
class Continent;
class Territory;
class mapLoader;

class Map {
public:
  // Store the continents and territory
  vector<Continent *> continents;
  vector<Territory *> territories;

  // default constructor
  Map();

  // copy constructor
  Map(const Map &map);

  // destructor
  ~Map();

  // getters
  vector<Territory *> getTerritories();
  vector<Continent *> getContinents();
  Continent *getSpecificContinent(string continentName);
  Territory *getSpecificTerritory(string territoryName);

  // setters/add
  void addContinent(Continent *continent);
  void addTerritory(Territory *territory);
};

class Territory {
private:
  string territory_name;
  Continent *associated_continent = nullptr;
  Player *owner = nullptr;
  int armies = 0;

public:
  vector<Territory *> adjacentTerritories;

  // Constructor and copy constructor
  Territory(string territory_name);
  Territory(const Territory &territory);

  // Destructor
  ~Territory();

  // Methods related to territory properties
  string getTerritory_name();
  void addAdjacentTerritory(Territory *territory);
  vector<Territory *> getAdjTerritories();
  void setAssociatedContinent(Continent *continent);
  Continent *getAssociatedContinent();

  
  // New methods for Part 4
  Player* getOwner();
  void setOwner(Player* newOwner);
  bool isAdjacent(Territory *territory);
  void addArmies(int num);
  void removeArmies(int num);
  int getArmies() const;
  void setArmies(int num);
  void doubleArmies();

  // Function to support negotiation logic
  Territory* getAnyTerritory();
};

class Continent {
private:
  string continentName;
  int score;

public:
  vector<Territory *> territories;

  // Constructor
  Continent(string continentName, int score);

  // Copy constructor
  Continent(const Continent &otherContinent);

  // Destructor
  ~Continent();

  // Add a territory to the continent
  void addTerritoryToContinent(Territory *territory);

  // Getters
  string getContinentName();
  int getScore();
  vector<Territory *> getTerritories();

  // Setters
  void setContinentName(string);
  void setScore(int score);
};

class mapLoader {
public:
  mapLoader();
  mapLoader(const mapLoader &maploader);
  ~mapLoader();

  static string trim(string s);
  static void load(string fileName, Map *map);
};
