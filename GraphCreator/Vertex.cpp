#include <iostream>
#include <vector>
#include "Vertex.h"

using namespace std;

Vertex::Vertex(char nlabel, vector<int>* ntable) {
  label = nlabel;
  table = ntable;
}

Vertex::~Vertex() {
  delete table;
  table = NULL;
}

char Vertex::getLabel() {
  return label;
}

vector<int>* Vertex::getTable() {
  return table;
}

void Vertex::add(int size) {
  for (int i = 0; i < size; i++) {
    table->push_back(0);
  }
}

void Vertex::remove(int index) {
  table->erase(table->begin()+index);
}
