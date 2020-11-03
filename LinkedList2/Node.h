#pragma once
#include <iostream>
#include "Student.h"

using namespace std;

class Node{
  public:
  Student * value; // pointer to the student at this node
  Node * pointer; // pointer to the next node
  Node * getNext(); // returns pointer 
  Student * getStudent(); // returns value
  void setNext(Node * nodeptr); // sets the next pointer
  Node(Student * studentptr); // constructor, assigns student to node
  ~Node(); // destructor
};