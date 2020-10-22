// implementation file for Media class
#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

const char* Media::getTitle() {
  return title;
}

int Media::getYear() {
  return year;
}

void Media::setTitle(char ntitle[]) {
  title = ntitle;
}

void Media::setYear(int nyear) {
  year = nyear;
}
