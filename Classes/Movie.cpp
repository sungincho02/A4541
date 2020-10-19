//implementation file for Movie class
#include <iostream>
#include <string.h>
#include "Movie.h"

using namespace std;

Movie::Movie(string* ntitle, int nyear, string* ndirector, int nduration, float nrating) {
  setTitle(ntitle);
  setYear(nyear);
  director = ndirector;
  duration = nduration;
  rating = nrating;
}

Movie::~Movie() {};

string* Movie::getDirector() {
  return director;
}

int Movie::getDuration() {
  return duration;
}

float Movie::getRating() {
  return rating;
}
