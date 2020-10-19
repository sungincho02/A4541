// declaration file for Videogame class
#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Videogame: public Media {
 public:
  // constructor
  Videogame(string* ntitle, int nyear, string* npublisher, float nrating);
  // destructor
  ~Videogame();
  // accessors
  string* getPublisher();
  float getRating();
 private:
  string* publisher;
  float rating;
};
