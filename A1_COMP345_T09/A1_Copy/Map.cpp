#include "Map.h"
#include <stdexcept>

// /////
// Map
// ////

// Constructor
Map::Map() {}

// Copy construcotr
Map::Map(const Map &map) {
  continents = map.continents;
  territories = map.territories;
}

// Desctrucotr
Map::~Map() {
  for (Continent *continent : continents) {
    delete continent; // Free the memory allocated for each Continent
  }
  for (Territory *territory : territories) {
    delete territory; // Free the memory allocated for each Continent
  }
}

// Ostream operator
ostream &operator<<(ostream &out, const Map &map) {
  // Display the contienns and teritories
  vector<Continent *> continentVector = map.continents;
  vector<Territory *> territoryVector = map.territories;
  for (Continent *i : continentVector) {
    cout << i->getContinentName() << endl;
    vector<Territory *> terr = i->getTerritories();
    for (Territory *j : terr) {
      cout << j->getTerritory_name() << endl;
    }
    cout << "" << endl;
  }
  return cout;
}

// Adders/setter and getter
void Map::addContinent(Continent *continent) {
  this->continents.push_back(continent);
}

void Map::addTerritory(Territory *territory) {
  this->territories.push_back(territory);
}

Continent *Map::getSpecificContinent(string continentName) {
  for (int i = 0; i < this->continents.size(); i++) {
    if (this->continents[i]->getContinentName() == continentName) {
      return continents[i];
    }
  }
  return nullptr;
}

Territory *Map::getSpecificTerritory(string territoryName) {
  for (int i = 0; i < this->territories.size(); i++) {
    if (this->territories[i]->getTerritory_name() == territoryName) {
      return territories[i];
    }
  }
  return nullptr;
}

vector<Territory *> Map::getTerritories() { return this->territories; }
vector<Continent *> Map::getContinents() { return this->continents; }

//////////////
// Continent
// /////////

// Constructor
Continent::Continent(string continentName, int score) {
  this->continentName = continentName;
  this->score = score;
}

// Copy
Continent::Continent(const Continent &continent) {
  continentName = continent.continentName;
  score = continent.score;
}

// Destructor
Continent::~Continent() {

  for (Territory *territory : territories) {
    delete territory; // Free the memory allocated for each territory
  }
}

// Stream operator
ostream &operator<<(ostream &out, const Continent &continent) {
  // Display the contienns and teritories
  vector<Territory *> terr = continent.territories;
  for (Territory *i : terr) {
    cout << i->getTerritory_name() << endl;
    cout << "" << endl;
  }
  return cout;
}

// Getter and setters and adders
string Continent::getContinentName() { return this->continentName; }

void Continent::addTerritoryToContinent(Territory *territory) {
  this->territories.push_back(territory);
}

vector<Territory *> Continent::getTerritories() { return this->territories; }

int Continent::getScore() { return this->score; }

void Continent::setContinentName(string newContinent) {
  this->continentName = newContinent;
}

void Continent::setScore(int score) { this->score = score; }

#include "Map.h"
#include <stdexcept>

// Map class implementations remain the same...

/////////////
// Territory
/////////////

// Constructor
Territory::Territory(string territoryName) {
  this->territory_name = territoryName;
}

// Copy constructor
Territory::Territory(const Territory &territory) {
  territory_name = territory.territory_name;
  adjacentTerritories = territory.adjacentTerritories;
  associated_continent = territory.associated_continent;
  owner = territory.owner;
  armies = territory.armies;
}

// Destructor
Territory::~Territory() {
  for (Territory *adj : adjacentTerritories) {
    delete adj;
  }
  delete associated_continent;
}

// Get the name of the territory
string Territory::getTerritory_name() { 
  return this->territory_name; 
}


// Add an adjacent territory
void Territory::addAdjacentTerritory(Territory *territory) {
  this->adjacentTerritories.push_back(territory);
}

// Get all adjacent territories
vector<Territory *> Territory::getAdjTerritories() {
  return this->adjacentTerritories;
}

// Set the associated continent for the territory
void Territory::setAssociatedContinent(Continent *continent) {
  this->associated_continent = continent;
}

// Get the associated continent for the territory
Continent *Territory::getAssociatedContinent() { 
  return associated_continent; 
}

// New methods added for Part 4

// Get the owner of the territory
Player* Territory::getOwner() { 
  return owner; 
}

// Set the owner of the territory
void Territory::setOwner(Player* newOwner) { 
  owner = newOwner; 
}

// Check if another territory is adjacent
bool Territory::isAdjacent(Territory *territory) {
    std::cout << "Checking adjacency for " << territory->getTerritory_name() << " in " << this->getTerritory_name() << "'s adjacencies." << std::endl;
    for (auto *adj : adjacentTerritories) {
        std::cout << "  Adjacent: " << adj->getTerritory_name() << std::endl;
        if (adj == territory) {
            return true;
        }
    }
    return false;
}


// Add armies to the territory
void Territory::addArmies(int num) { 
  armies += num; 
}

// Remove armies from the territory
void Territory::removeArmies(int num) { 
  armies -= num; 
  if (armies < 0) armies = 0;
}

// Get the current number of armies
int Territory::getArmies() const { 
  return armies; 
}

// Set the number of armies in the territory
void Territory::setArmies(int num) { 
  armies = num; 
}

// Double the number of armies in the territory
void Territory::doubleArmies() { 
  armies *= 2; 
}

// Retrieve any territory (for ally purposes)
Territory* Territory::getAnyTerritory() {
  return adjacentTerritories.empty() ? nullptr : adjacentTerritories[0];
}


//////////////
// mapLoader
//////////////
//
void mapLoader::load(string fileName, Map *map) {

  // Create reading stream
  ifstream fileReader(fileName);
  string line;

  // Reads through the file
  while (getline(fileReader, line)) {

    line = mapLoader::trim(line);

    // Inserts continent
    if (line == "Continents") {
      string continentName;

      while (trim(line) != "Territories") {

        getline(fileReader, line);
        int pos = line.find('=');
        if (pos == -1) {
          break;
        }
        continentName = line.substr(0, pos);
        string scoreInString = line.substr(pos + 1);
        int score = stoi(scoreInString);
        Continent *continent = new Continent(continentName, score);
        map->addContinent(continent);
      }

    } else if (line == "Map") {

      // Skips the map info part of the file
      while (trim(line) != "Continents") {

        getline(fileReader, line);
        int pos = line.find('=');
        if (pos == -1) {
          break;
        }
      }

    } else { // Assume we are adding territoriesc

      // skips blank line
      if (line.find(',') == -1) {
        continue;
      }

      // Find territory
      string info = line;
      string territory = info.substr(0, info.find(","));
      info = (info.substr(info.find(",") + 1));
      // Create a territory object and check
      Territory *createTerritory;
      if (map->getSpecificTerritory(territory) != nullptr) {
        createTerritory = map->getSpecificTerritory(territory);
      } else {
        createTerritory = new Territory(territory);
        map->addTerritory(createTerritory);
      }

      // Skip coordinates
      info = (info.substr(info.find(",") + 1));
      info = (info.substr(info.find(",") + 1));

      // Get associated Continent

      string associatedCountry = info.substr(0, info.find(","));
      info = (info.substr(info.find(",") + 1));
      // Get the continent object from the map and add the territory to the
      // continent
      Continent *mapContinent;
      if (map->getSpecificContinent(associatedCountry) != nullptr) {
        mapContinent = map->getSpecificContinent(associatedCountry);
        mapContinent->addTerritoryToContinent(createTerritory);
      } else {
        cout << "continent does not exist" << " for the territory " << territory
             << endl;
      }

      // Check if territory is already part of a continent
      if (createTerritory->getAssociatedContinent() != nullptr) {
        cout << territory << " is already in a continent" << endl;
        throw runtime_error("Continent belings to two teritorry");
        exit(1);
        break;
      } else {
        createTerritory->setAssociatedContinent(mapContinent);
      }

      // Get adjacent territory
      while (true) {
        // Gets the adjacent territory from the string
        string adjTerritory = info.substr(0, info.find(","));

        // Creates the territory object
        Territory *adj;
        if (map->getSpecificTerritory(adjTerritory) != nullptr) {
          adj = map->getSpecificTerritory(adjTerritory);
          createTerritory->addAdjacentTerritory(adj);
        } else {
          adj = new Territory(adjTerritory);
          map->addTerritory(adj);
          createTerritory->addAdjacentTerritory(adj);
        }

        // Checks for the end of the line
        info = (info.substr(info.find(",") + 1));
        if (info.find(',') == -1) {
          break;
        }
      }
    }
  }

  // DFS to visit node
  unordered_set<Continent *> visitedContinents;
  unordered_set<Territory *> visitedTerritory;

  vector<Continent *> continents = map->getContinents();
  vector<Territory *> territories = map->getTerritories();

  for (int i = 0; i < continents.size(); i++) {
    vector<Territory *> continentTerritories = continents[i]->getTerritories();
    visitedContinents.insert(continents[i]);
    for (int j = 0; j < continentTerritories.size(); j++) {
      vector<Territory *> adj = continentTerritories[j]->getAdjTerritories();
      visitedTerritory.insert(continentTerritories[j]);
      for (int h = 0; h < adj.size(); h++) {
        visitedContinents.insert(adj[h]->getAssociatedContinent());
        visitedTerritory.insert(adj[h]);
      }
    }
  }

  // Checks if map has connected sub graph
  if (visitedContinents.size() == continents.size()) {
    cout << "continents are connected subgraph" << endl;
  } else if (visitedContinents.size() != continents.size()) {
    cout << "continents are not connected subgraph" << visitedContinents.size()
         << endl
         << continents.size() << endl;
    throw runtime_error("Invalid map");
  }

  // Chekcs if map is connected grapha
  if (visitedTerritory.size() == territories.size()) {
    cout << "map is connected graph" << endl;
  } else if (visitedTerritory.size() != territories.size()) {
    cout << "map is not connected graph" << visitedTerritory.size() << endl
         << territories.size() << endl;
    throw runtime_error("Invalid map");
  }

  cout << "All territories have a one continent" << endl;
}
// Constructor and destructor
mapLoader::mapLoader() {}
mapLoader::~mapLoader() { delete this; }

// trim string
string mapLoader::trim(string line) {
  if (line.find("[") != -1) {
    int removeChar1 = line.find("[");
    int removeChar2 = line.find("]");
    line = line.substr(removeChar1 + 1, removeChar2 - 1);
    cout << line << endl;
  }
  return line;
}
