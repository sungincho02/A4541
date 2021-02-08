#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>

using namespace std;

class Vertex {
 public:
  Vertex(char nlabel, vector<int>* ntable);
  ~Vertex();
  char getLabel();
  vector<int>* getTable();
  void add(int size);
  void remove(int index);
 private:
  char label;
  vector<int>* table;
};

#endif
