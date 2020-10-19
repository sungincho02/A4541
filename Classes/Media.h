// declaration file for Media class
#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <string.h>

using namespace std;

class Media {
 public:
  // accessors
  virtual string* getTitle();
  virtual int getYear();
  virtual void setTitle(string* ntitle);
  virtual void setYear(int nyear);
 private:
  string* title;
  int year;
};

#endif
