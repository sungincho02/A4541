// declaration file for Movie class
#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

class Movie: public Media {
 public:
  // constructor
  Movie(char ntitle[], int nyear, char ndirector, int nduration, float nrating);
  // destructor
  ~Movie();
  // accessors
  char* getDirector();
  int getDuration();
  float getRating();
 private:
  char director[99];
  int duration;
  float rating;
};
