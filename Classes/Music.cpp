#include <iostream>
#include <string.j>
#include "Music.h"

using namespace std;

Music::Music(string* ntitle, int nyear, string* nartist, int nduration, string* npublisher) {
  setTitle(ntitle);
  setYear(nyear);
  artist = nartist;
  duration = nduration;
  publisher = npublisher;
}

string* Music::getArtist() {
  return artist;
}

int Music::getDuration() {
  return duration;
}

string* Music::getPublisher() {
  return publisher;
}
