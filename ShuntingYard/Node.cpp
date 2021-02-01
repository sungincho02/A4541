#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(char nvalue) {
  value = nvalue;
  next = NULL;
}

Node::~Node() {
  next = NULL;
}

char Node::getValue() {
  return value;
}

Node* Node::getNext() {
  return next;
}

void Node::setNext(Node* nnode) {
  next = nnode;
}
