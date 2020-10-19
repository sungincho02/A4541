#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Video: public Media {
 public:
  Video(string* ntitle, int nyear, string* npublisher, flaot nrating);
  string* getPublisher();
  float getRating();
 private:
  string* publisher;
  float rating;
};
