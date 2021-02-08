#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include "Vertex.h"

using namespace std;

struct Path {
  int cost;
  vector<char> trail;
};


// function prototypes
int find(vector<Vertex*> list, char label);
void print(vector<Vertex*> list);
Path* dijkstra(vector<Vertex*> list, int source, int destination);
void travel(vector<Vertex*> list, vector<Path*> paths, vector<bool> &traveled, int current);

int main() {
  bool quit = false;
  char input[20];
  vector<Vertex*> list;
  Vertex* v;
  char label;
  char second;
  int weight;
  int key;
  Path* solution;

  cout << "\nCommands:" << endl;
  cout << "ADD V - add a vertex" << endl;
  cout << "RM V - remove a vertex" << endl;
  cout << "ADD E - add an edge" << endl;
  cout << "RM E - remove an edge" << endl;
  cout << "PRINT - print the adjacency table" << endl; 
  cout << "PATH - find shortest path" << endl;
  cout << "QUIT" << endl;
  
  while (!quit) {
    cout << "\n> ";
    cin.get(input, 20);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (strcmp(input, "ADD V") == 0) {
      cout << "\nEnter a label(single character): ";
      cin >> label;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      key = find(list, label);

      if (key == -1) {
	v = new Vertex(label, new vector<int>);
	// update adjacency lists
	for (int i = 0; i < list.size(); i++) {
	  list[i]->getTable()->push_back(0);
	}
	// add new node
	list.push_back(v);
	v->add(list.size());
      }
      else {
	cout << "\nThat vertex already exists" << endl;
      }
    }
    else if (strcmp(input, "RM V") == 0) {
      cout << "\nEnter the label: ";
      cin >> label;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      
      key = find(list, label);

      if (key == -1) {
	cout << "\nThat vertex does not exist" << endl;
      }
      else {
	// remove node
	list.erase(list.begin()+key);
	// remove connection with the removed node from adjacency lists
	for (int i = 0; i < list.size(); i++) {
	  list[i]->remove(key);
	}
      }
    }
    else if (strcmp(input, "ADD E") == 0) {
      cout << "\nEnter the label of the first node: ";
      cin >> label;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter the label of the second node: ";
      cin >> second;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter the weight of the edge(up to 99999): ";
      cin >> weight;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // add weight to connection between the two nodes
      list[find(list, label)]->getTable()->at(find(list, second)) = weight;
      list[find(list, second)]->getTable()->at(find(list, label)) = weight;
    }
    else if (strcmp(input, "RM E") == 0) {
      cout << "\nEnter the label of the first node: ";
      cin >> label;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter the label of the second node: ";
      cin >> second;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // remove weight from connection between the two nodes
      list[find(list, label)]->getTable()->at(find(list, second)) = 0;
      list[find(list, second)]->getTable()->at(find(list, label)) = 0;
    }
    else if (strcmp(input, "PRINT") == 0) {
      // print the adjacency table
      print(list);
    }
    else if (strcmp(input, "PATH") == 0) {
      cout << "\nEnter the label of the source: ";
      cin >> label;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter the label of the destination: ";
      cin >> second;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // find the shortest path
      solution = dijkstra(list, find(list, label), find(list, second));

      // print out the shortest path and the cost if it exists
      if (solution->cost != 100000) {
	cout << "\nShortest path: ";
	for (int i = 0; i < solution->trail.size(); i++) {
	  cout << solution->trail.at(i);
	  if (i+1 < solution->trail.size()) {
	    cout << " -> ";
	  }
	}
	cout << "\nCost: " << solution->cost << endl;
      }
      else {
	cout << "\nThere is no path between them" << endl;
      }
    }
    else if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    else {
      cout << "\nInvalid command" << endl;
    }
  }
  
  return 0;
}

// find the index of the node with the given label
int find(vector<Vertex*> list, char label) {
  for (int i = 0; i < list.size(); i++) {
    if (list[i]->getLabel() == label) {
      return i;
    }
  }
  return -1;
}

// print the adjacency table
void print(vector<Vertex*> list) {
  for (int i = 0; i < list.size(); i++) {
    cout << "\n" << i << ") " << list[i]->getLabel();
    for (int j = 0; j < list.size(); j++) {
      if (list[i]->getTable()->at(j) != 0) {
	cout << " -> [" << list[j]->getLabel() << " | " << list[i]->getTable()->at(j) << "]";
      }
    }
  }
  cout << endl;
}

// construct shortest path list from source and return the path to destination
Path* dijkstra(vector<Vertex*> list, int source, int destination) {
  vector<Path*> paths;

  // initialize the shortest paths
  for (int i = 0; i < list.size(); i++) {
    paths.push_back(new Path());
    if (i == source) {
      paths[i]->cost = 0;
    }
    else {
      paths[i]->cost = 100000;
    }
  }

  // keeps track of the nodes traveled
  vector<bool> traveled;

  for (int i = 0; i < list.size(); i++) {
    traveled.push_back(false);
  }

  // start traveling
  travel(list, paths, traveled, source);

  // return the path to destination
  return paths[destination];
}

// travel to find shortest path to each node
void travel(vector<Vertex*> list, vector<Path*> paths, vector<bool> &traveled, int current) {
  // mark current node as traveled and update path
  traveled[current] = true;
  paths[current]->trail.push_back(list[current]->getLabel());
  
  int temp;

  // update shortest path for any neighbour nodes
  for (int i = 0; i < list.size(); i++) {
    if (list[current]->getTable()->at(i) != 0) {
      if (!traveled[i]) {
	temp = paths[current]->cost + list[current]->getTable()->at(i);
	if (temp < paths[i]->cost) {
	  paths[i]->cost = temp;
	  paths[i]->trail = paths[current]->trail;
	}
      }
    }
  }

  // find the next node to travel
  int shortest = 0;
  int next = -1;
  for (int i = 0; i < list.size(); i++) {
    if (!traveled[i]) {
      if (shortest == 0 || paths[i]->cost < shortest) {
	shortest = paths[i]->cost;
	next = i;
      }
    }
  }

  // travel to next node unless none left
  if (next != -1) {
    travel(list, paths, traveled, next);
  }
}
