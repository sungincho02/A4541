#include <iostream>
#include "Node.h"
#include "Student.h"

using namespace std;

Node * Node::getNext(){
  return pointer;
}
Student * Node::getStudent(){
  return value;
}
void Node::setNext(Node * nodeptr){
  pointer = nodeptr;
}
Node::Node(Student * studentptr){
  value = new Student();
  value = studentptr;
  pointer = NULL;
}

Node::~Node(){
  delete value;
  delete pointer;
}