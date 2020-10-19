#include <iostream>
#include <string.h>
#include "Media.h"

using namespace std;

string* Media::getTitle() {
  return title;
}

int Media::getYear() {
  return year;
}

void Media::setTitle(string* ntitle) {
  title = ntitle;
}

void Media::setYear(int nyear) {
  year = nyear;
}
