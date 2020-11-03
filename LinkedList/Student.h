// header file for Student class
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

using namespace std;

class Student {
 public:
  // constructor
  Student(char nfn[99], char nln[99], int nid, float ngpa);
  // destructor
  ~Student();
  // accessors
  char* getFirst();
  char* getLast();
  int getID();
  float getGPA();
 private:
  char fn[99];
  char ln[99];
  int id;
  float gpa;
};

#endif
