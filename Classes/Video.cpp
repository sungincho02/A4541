#include <iostream>
#include <string.h>
#include "Video.h"

using namespace std;

Video::Video(string* ntitle, int nyear, string* npublisher, float nrating) {
  setTitle(ntitle);
  setYear(nyear);
  publisher = npublisher;
  rating = nrating;
}

string* Video::getPublisher() {
  return publisher;
}

float Video::getRating() {
  return rating;
}
