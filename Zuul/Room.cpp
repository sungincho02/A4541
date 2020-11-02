// implementation file for class Room
#include <iostream>
#include <cstring>
#include <map>
#include <iterator>
#include "Room.h"

using namespace std;

Room::Room(int nindex, char ndescription[]) {
  index = nindex;
  strcpy(description, ndescription);
}

Room::~Room() {};

int Room::getIndex() {
  return index;
}

void Room::setExit(char direction, Room* neighbor) {
  exits.insert(pair<char, Room*>(direction, neighbor));
}

char* Room::getDescription() {
  return description; 
}

void Room::printExit() {
  cout << "Choose a direction to move:" << endl;
  for(auto itr = exits.begin(); itr != exits.end(); ++itr) {
    cout << itr->first << endl; 
  }
}

Room* Room::getNeighbor(char direction) {
  return exits[direction];
}
