#include <iostream>
#include <string.h>
#include "Videogame.h"

using namespace std;

Videogame::Videogame(string* ntitle, int nyear, string* npublisher, float nrating) {
  setTitle(ntitle);
  setYear(nyear);
  publisher = npublisher;
  rating = nrating;
}

Videogame::~Videogame() {}

string* Videogame::getPublisher() {
  return publisher;
}

float Videogame::getRating() {
  return rating;
}
