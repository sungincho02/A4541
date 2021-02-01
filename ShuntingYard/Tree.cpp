#include <iostream>
#include <cstring>
#include "Tree.h"

using namespace std;

Tree::Tree(char nvalue[]) {
  strcpy(value, nvalue);
  left = NULL;
  right = NULL;
}

Tree::~Tree() {
  left = NULL;
  right = NULL;
}

char* Tree::getValue() {
  return value;
}

Tree* Tree::getLeft() {
  return left;
}

Tree* Tree::getRight() {
  return right;
}

void Tree::setLeft(Tree* nleft) {
  left = nleft;
}

void Tree::setRight(Tree* nright) {
  right = nright;
}
