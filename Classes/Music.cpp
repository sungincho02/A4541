// implementation file for Music class
#include <iostream>
#include <string.h>
#include "Music.h"

using namespace std;

Music::Music(string* ntitle, int nyear, string* nartist, int nduration, string* npublisher) {
  setTitle(ntitle);
  setYear(nyear);
  artist = nartist;
  duration = nduration;
  publisher = npublisher;
}

Music::~Music() {}

string* Music::getArtist() {
  return artist;
}

int Music::getDuration() {
  return duration;
}

string* Music::getPublisher() {
  return publisher;
}
