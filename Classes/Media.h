#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <string.h>

using namespace std;

class Media {
 public:
  string* getTitle();
  int getYear();
  void setTitle(string* ntitle);
  void setYear(int nyear);
 private:
  string* title;
  int year;
};

#endif
