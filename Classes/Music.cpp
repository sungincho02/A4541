// implementation file for Music class
#include <iostream>
#include <cstring>
#include "Music.h"

using namespace std;

Music::Music(char ntitle[], int nyear, char nartist[], int nduration, char npublisher[]) {
  setTitle(ntitle);
  setYear(nyear);
  strcpy(artist, nartist);
  duration = nduration;
  strcpy(publisher, npublisher);
}

Music::~Music() {}

char* Music::getArtist() {
  return artist;
}

int Music::getDuration() {
  return duration;
}

char* Music::getPublisher() {
  return publisher;
}
