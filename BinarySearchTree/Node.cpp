#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(int nvalue) {
  value = nvalue;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  left = NULL;
  right = NULL;
}

int Node::getValue() {
  return value;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

void Node::setValue(int nvalue) {
  value = nvalue;
}

void Node::setLeft(Node* nleft) {
  left = nleft;
}

void Node::setRight(Node* nright) {
  right = nright;
}
