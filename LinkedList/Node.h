/*
 * Author: Sungin Cho
 * Date: 11/1/20
 * Description: This is Node class that contains Student pointer and next node pointer for linked lists.
 */
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Student.h"

using namespace std;

class Node {
 public:
  // constructor
  Node(Student* nstudent);
  // destructor
  ~Node();
  // get student pointer
  Student* getStudent();
  // set next node pointer
  void setNext(Node* node);
  // get next node pointer
  Node* getNext();
 private:
  Student* student;
  Node* next;
};

#endif
