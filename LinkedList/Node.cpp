// implementation file for Node class
#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(Student* nstudent) {
  student = nstudent;
  next = NULL;
}

Node::~Node() {
  delete student;
  next = NULL;
}

Student* Node::getStudent() {
  return student;
}

void Node::setNext(Node* node) {
  next = node;
}

Node* Node::getNext() {
  return next;
}
