// header file for class Room
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <cstring>
#include <map>

using namespace std;

class Room {
 public:
  // constructor
  Room(int nindex, char ndescription[]);
  // destructor
  ~Room();
  // accessors
  int getIndex();
  void setExit(char direction, Room* neighbor);
  char* getDescription();
  void printExit();
  Room* getNeighbor(char direction);
 private:
  int index;
  char description[99];
  map<char, Room*> exits; 
};

#endif
