#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  char getValue();
  Node* getNext();
  void setNext(Node* nnode);
  Node(char nvalue);
  ~Node();
 private:
  char value;
  Node* next;
};

#endif
