// declaration file for Media class
#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <cstring>

using namespace std;

class Media {
 public:
  // accessors
  virtual char* getTitle();
  virtual int getYear();
  virtual void setTitle(char ntitle[]);
  virtual void setYear(int nyear);
 private:
  char title[99];
  int year;
};

#endif
