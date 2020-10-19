#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Movie: public Media {
 public:
  Movie(string* ntitle, int nyear, string* ndirector, int nduration, float nrating);
  ~Movie();
  string* getDirector();
  int getDuration();
  float getRating();
 private:
  string* director;
  int duration;
  float rating;
};
