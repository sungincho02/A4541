// header file of Node class for Red-Black Tree
#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  // constructor and destructor
  Node(int nvalue);
  ~Node();
  // getters and setters
  int getValue();
  bool getColor();
  Node* getLeft();
  Node* getRight();
  void setValue(int nvalue);
  void setColor(bool ncolor);
  void setLeft(Node* nleft);
  void setRight(Node* nright);
 private:
  int value; // integer value
  bool color; // color of node
  Node* left; // left child
  Node* right; // right child
};

#endif
