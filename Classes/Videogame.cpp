// implementation file for Videogame class
#include <iostream>
#include <cstring>
#include "Videogame.h"

using namespace std;

Videogame::Videogame(char ntitle[], int nyear, char npublisher[], float nrating) {
  setTitle(ntitle);
  setYear(nyear);
  publisher = npublisher;
  rating = nrating;
}

Videogame::~Videogame() {}

char* Videogame::getPublisher() {
  return publisher;
}

float Videogame::getRating() {
  return rating;
}
