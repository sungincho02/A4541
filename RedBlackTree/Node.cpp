#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(int nvalue) {
  value = nvalue;
  color = false;
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

bool Node::getColor() {
  return color;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

void Node::setColor(bool ncolor) {
  color = ncolor;
}

void Node::setLeft(Node* nleft) {
  left = nleft;
}

void Node::setRight(Node* nright) {
  right = nright;
}
