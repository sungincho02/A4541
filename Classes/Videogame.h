// declaration file for Videogame class
#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

class Videogame: public Media {
 public:
  // constructor
  Videogame(char ntitle, int nyear, char npublisher, float nrating);
  // destructor
  ~Videogame();
  // accessors
  char getPublisher();
  float getRating();
 private:
  char publisher[99];
  float rating;
};
