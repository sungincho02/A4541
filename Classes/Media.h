#include <iostream>
#include <string.h>

using namespace std;

class Media {
 public:
  string* getTitle();
  int getYear();
 private:
  string* title;
  int year;
};
