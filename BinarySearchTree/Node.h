#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  Node(int nvalue);
  ~Node();
  int getValue();
  Node* getLeft();
  Node* getRight();
  void setLeft(Node* nleft);
  void setRight(Node* nright);
 private:
  int value;
  Node* left;
  Node* right;
};

#endif
