// declaration file for Music class
#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

class Music: public Media {
 public:
  // constructor
  Music(char ntitle[], int nyear, char artist[], int nduration, char npublisher[]);
  // destructor
  ~Music();
  // accessors
  char getArtist();
  int getDuration();
  char getPublisher();
 private:
  char artist[99];
  int duration;
  char publisher[99];
};
