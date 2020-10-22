// implementation file for Movie class
#include <iostream>
#include <cstring>
#include "Movie.h"

using namespace std;

Movie::Movie(char ntitle[], int nyear, char ndirector[], int nduration, float nrating) {
  setTitle(ntitle);
  setYear(nyear);
  director = ndirector;
  duration = nduration;
  rating = nrating;
}

Movie::~Movie() {};

char* Movie::getDirector() {
  return director;
}

int Movie::getDuration() {
  return duration;
}

float Movie::getRating() {
  return rating;
}
