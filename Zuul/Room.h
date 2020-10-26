// header file for class Room
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

class Room {
 public:
  // constructor
  Room(char ndescription[]);
  // destructor
  ~Room();
  // accessors
  void setExit(char direction, Room* neighbor)
  char* getDescription();
  char* getExit();
  Room* getNeighbor(char direction);
 private:
  char description[99];
  map<char, Room*> exits; 
};
