#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include "Node.h"

using namespace std;

// function prototypes
int search(Node* current, int gen, int key);
void insert(Node* current, Node* nnode);
void print(Node* root, Node* current, bool line[]);
void remove(Node* &root, Node* prev, Node* current, int key);
Node* inorder(Node* current);

int main() {
  // initialization
  char input[99];
  int method;
  int number;
  int size;
  Node* root = NULL;
  Node* nnode;
  bool quit = false;

  // take user input
  cout << "\nEnter the amount of numbers: " << endl;
  cout << "> ";
  cin >> size;
  
  int list[size];
  
  cout << "\nChoose input method[1/2]:" << endl;
  cout << "1. File" << endl;
  cout << "2. Manual" << endl;
  cout << "> ";
  cin >> method;

  if (method == 1) {
    ifstream infile;
    
    cout << "\nEnter the file name: " << endl;
    cout << "> ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    
    cin.get(input, 99);
    infile.open(input);

    for (int i = 0; i < size; i++) {
      infile >> list[i];
    }
  }
  else if (method == 2) {
    cout << "\nEnter the numbers:" << endl;
    cout << "> ";
    
    for (int i = 0; i < size; i++) {
      cin >> list[i];
    }
  }
  
  // set root
  root = new Node(list[0]);

  // add list into tree
  for (int i = 1; i < size; i++) {
    nnode = new Node(list[i]);
    insert(root, nnode);
  }

  bool line[100] = {false};

  // print out possible commands
  cout << "\nCommands:" << endl;
  cout << "ADD" << endl;
  cout << "PRINT" << endl;
  cout << "DELETE" << endl;
  cout << "QUIT" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // resolve user commands
  while (!quit) {
    cout << "\n> ";
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (strcmp(input, "ADD") == 0) {
      cout << "\nEnter the number you want to add: " << endl;
      cout << "> ";
      cin >> number;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      nnode = new Node(number);
      insert(root, nnode);
    }
    else if (strcmp(input, "PRINT") == 0) {
      cout << "\n";
      print(root, root, line);
    }
    else if (strcmp(input, "DELETE") == 0) {
      cout << "\nEnter the number you want to remove: " << endl;
      cout << "> ";
      cin >> number;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      remove(root, NULL, root, number);
    }
    else if (strcmp(input, "SEARCH") == 0) {
      cout << "\nEnter the number you want to search: " << endl;
      cout << "> ";
      cin >> number;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      if (search(root, 1, number) == 0) {
	cout << "\nThe number is not in the tree" << endl;
      }
      else {
	cout << "\nThe number is in the tree" << endl;
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


// search for a node and return its level or 0 if it doesn't exist
int search(Node* current, int gen, int key) {
  if (key < current->getValue()) {
    if (current->getLeft() == NULL) {
      return 0;
    }
    else {
      return search(current->getLeft(), gen + 1, key);
    }
  }
  else if (key > current->getValue()) {
    if (current->getRight() == NULL) {
      return 0;
    }
    else {
      return search(current->getRight(), gen + 1, key);
    }
  }
  else {
    return gen;
  }
}

// insert a node into the tree
void insert(Node* current, Node* nnode) {
  if (nnode->getValue() < current->getValue()) {
    if (current->getLeft() == NULL) {
      current->setLeft(nnode);
    }
    else {
      insert(current->getLeft(), nnode);
    }
  }
  else {
    if (current->getRight() == NULL) {
      current->setRight(nnode);
    }
    else {
      insert(current->getRight(), nnode);
    }
  }
}

// print out the diagram of the tree
void print(Node* root, Node* current, bool line[]) {
  if (current == root) {
    cout << current->getValue() << endl;
  }
  else {
    for (int i = 0; i < search(root, 1, current->getValue()) - 2; i++) {
      if (line[i] == true) {
        cout << "|   ";
      }
      else {
        cout << "    ";
      }
    }
    cout << "|---" << current->getValue() << endl;
  }

  if (current->getLeft() != NULL) {
    for (int i = 0; i < search(root, 1, current->getValue()) - 1; i++) {
      if (line[i] == true) {
        cout << "|   ";
      }
      else {
        cout << "    ";
      }
    }
    cout << "|" << endl;
    bool nline[100];
    for (int i = 0; i < 100; i++) {
      nline[i] = line[i];
    }
    if (current->getRight() != NULL) {
      nline[search(root, 1, current->getValue()) - 1] = true;
    }
    print(root, current->getLeft(), nline);
  }
  if (current->getRight() != NULL) {
    for (int i = 0; i < search(root, 1, current->getValue()) - 1; i++) {
      if (line[i] == true) {
        cout << "|   ";
      }
      else {
        cout << "    ";
      }
    }
    cout << "|" << endl;
    bool clone[100];
    for (int i = 0; i < 100; i++) {
      clone[i] = line[i];
    }
    print(root, current->getRight(), clone);
  }
}

// remove a node from the tree
void remove(Node* &root, Node* prev, Node* current, int key) {
  if (key < current->getValue()) {
    if (current->getLeft() == NULL) {
      cout << "\nThe number is not in the tree" << endl;
      return;
    }
    else {
      remove(root, current, current->getLeft(), key);
    }
  }
  else if (key > current->getValue()) {
    if (current->getRight() == NULL) {
      cout << "\nThe number is not in the tree" << endl;
      return;
    }
    else {
      remove(root, current, current->getRight(), key);
    }
  }
  else {
    if (current->getLeft() == NULL && current->getRight() == NULL) {
      if (current != root) {
	if (prev->getLeft() == current) {
	  prev->setLeft(NULL);
	}
	else {
	  prev->setRight(NULL);
	}
      }
      else {
	root = NULL;
      }
      delete current;
    }
    else if (current->getLeft() != NULL && current->getRight() != NULL) {
      // if the node to be deleted has two children, remove its inorder successor instead and replace the value
      int nvalue = inorder(current->getRight())->getValue();
      remove(root, NULL, root, nvalue);
      current->setValue(nvalue);
    }
    else if (current->getLeft() != NULL) {
      if (current != root) {
	if (prev->getLeft() == current) {
	  prev->setLeft(current->getLeft());
	}
	else {
	  prev->setRight(current->getLeft());
	}
      }
      else {
	root = current->getLeft();
      }
      delete current;
    }
    else {
      if (current != root) {
	if (prev->getLeft() == current) {
	  prev->setLeft(current->getRight());
	}
	else {
	  prev->setRight(current->getRight());
	}
      }
      else {
	root = current->getRight();
      }
      delete current;
    }
  }
}

// find the indrder successor for the node to be deleted
Node* inorder(Node* current) {
  if (current->getLeft() == NULL) {
    return current;
  }
  else {
    return inorder(current->getLeft());
  }
}
