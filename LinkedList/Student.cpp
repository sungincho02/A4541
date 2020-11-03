// implementation file for Student class
#include <iostream>
#include <cstring>
#include "Student.h"

using namespace std;

Student::Student(char nfn[99], char nln[99], int nid, float ngpa) {
  strcpy(fn, nfn);
  strcpy(ln, nln);
  id = nid;
  gpa = ngpa;
}

Student::~Student() {};

char* Student::getFirst() {
  return fn;
}

char* Student::getLast() {
  return ln;
}

int Student::getID() {
  return id;
}

float Student::getGPA() {
  return gpa;
}
