#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  Node(int nvalue);
  ~Node();
  int getValue();
  bool getColor();
  Node* getLeft();
  Node* getRight();
  void setColor(bool ncolor);
  void setLeft(Node* nleft);
  void setRight(Node* nright);
 private:
  int value;
  bool color;
  Node* left;
  Node* right;
};

#endif
