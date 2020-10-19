#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Videogame: public Media {
 public:
  Videogame(string* ntitle, int nyear, string* npublisher, float nrating);
  string* getPublisher();
  float getRating();
 private:
  string* publisher;
  float rating;
};
