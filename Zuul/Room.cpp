// implementation file for class Room
#include <iostream>
#include <cstring>
#include <map>
#include <iterator>
#include "Room.h"

using namespace std;

Room::Room(char ndescription[]) {
  strcpy(description, ndescription);
}

Room::~Room() {};

void Room::setExit(char direction, Room* neighbor) {
  exits.insert(pair<char, Room*>(direction, neighbor));
}

char* Room::getDescription() {
  return description; 
}

char* Room::getExit(char exitStr[99]) {
  strcpy(exitStr, "Exits:");
  for(auto itr = exits.begin(); itr != exits.end(); ++itr) {
    strcat(exitStr, "\n" + itr->first);
  }
  return exitStr;
}

Room* Room::getNeighbor(char direction) {
  return exits[direction];
}
