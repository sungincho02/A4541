#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cstring>

using namespace std;

class Tree {
 public:
  // getters and setters
  char* getValue();
  Tree* getLeft();
  Tree* getRight();
  void setLeft(Tree* nleft);
  void setRight(Tree* nright);
  // constructor and destructor
  Tree(char nvalue[]);
  ~Tree();
 private:
  char value[50];
  Tree* left;
  Tree* right;
};

#endif
