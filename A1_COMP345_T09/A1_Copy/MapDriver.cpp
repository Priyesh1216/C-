#include "Map.h" // Include Map class

// Function to test loading maps
void testLoadMaps() {
  set<string> files = {"USA.map", "USA_False.map"}; // Set of map files to load

  for (string s : files) {
    try {
      cout << endl << s << endl;

      // Load map from file
      Map *newMap = new Map();
      mapLoader *mapload = new mapLoader();
      mapload->load(s, newMap);

      cout << "Valid Map" << endl << endl;
    } catch (exception e) {
      // Handle invalid map loading
      cout << "Invalid Map" << endl << endl;
    }
  }
}

/*
int main() {
  testLoadMaps(); // Test map loading
  return 0;
}

*/

