// declaration file for Movie class
#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Movie: public Media {
 public:
  // constructor
  Movie(string* ntitle, int nyear, string* ndirector, int nduration, float nrating);
  // destructor
  ~Movie();
  // accessors
  string* getDirector();
  int getDuration();
  float getRating();
 private:
  string* director;
  int duration;
  float rating;
};
