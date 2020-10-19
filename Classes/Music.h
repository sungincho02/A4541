// declaration file for Music class
#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

class Music: public Media {
 public:
  // constructor
  Music(string* ntitle, int nyear, string* artist, int nduration, string* npublisher);
  // destructor
  ~Music();
  // accessors
  string* getArtist();
  int getDuration();
  string* getPublisher();
 private:
  string* artist;
  int duration;
  string* publisher;
};
