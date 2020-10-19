#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Music: public Media {
 public:
  Music(string* ntitle, int nyear, string* artist, int nduration, string* npublisher);
  string* getArtist();
  int getDuration();
  string* getPublisher();
 private:
  string* artist;
  int duaration;
  string* publisher;
};
