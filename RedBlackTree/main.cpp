#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include "Node.h"

using namespace std;

int search(Node* current, int level, int key);
void insert(Node* &root, Node* current, Node* nnode);
void print(Node* root, Node* current, bool line[]);
void remove(Node* &root, Node* current, int key);
void delRepair(Node* &root, Node* current);
Node* successor(Node* current);
void insRepair(Node* &root, Node* current);
Node* getParent(Node* root, Node* child);
Node* getUncle(Node* root, Node* key);
Node* getSibling(Node* root, Node* key);
void leftRotation(Node* root, Node* parent);
void rightRotation(Node* root, Node* parent);

const bool RED = true;
const bool BLACK = false;

int main() {
  char input[99];
  int method;
  int number;
  int size;
  Node* root = NULL;
  Node* nnode;
  bool quit = false;
  bool line[100] = {false};
  
  cout << "\nCommands:" << endl;
  cout << "ADD" << endl;
  cout << "BATCH" << endl;
  cout << "PRINT" << endl;
  cout << "DELETE" << endl;
  cout << "QUIT" << endl;
  
  // 
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
      if (root == NULL) {
	root = nnode;
      }
      else {
	insert(root, root, nnode);
      }
    }
    else if (strcmp(input, "BATCH") == 0) {
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
  
      //
      if (root == NULL) {
	root = new Node(list[0]);
	
	for (int i = 1; i < size; i++) {
	  nnode = new Node(list[i]);
	  insert(root, root, nnode);
	}
      }
      else {
	for (int i = 0; i < size; i++) {
	  nnode = new Node(list[i]);
	  insert(root, root, nnode);
	}
      }

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

      remove(root, root, number);
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

int search(Node* current, int level, int key) {
  if (key < current->getValue()) {
    if (current->getLeft() == NULL) {
      return 0;
    }
    else {
      return search(current->getLeft(), level + 1, key);
    }
  }
  else if (key > current->getValue()) {
    if (current->getRight() == NULL) {
      return 0;
    }
    else {
      return search(current->getRight(), level + 1, key);
    }
  }
  else {
    return level;
  }
}

void insert(Node* &root, Node* current, Node* nnode) {
  if (search(root, 1, nnode->getValue()) != 0) {
    cout << "Dupulicate skipped" << endl;
    return;
  }
  
  nnode->setColor(RED);
  if (nnode->getValue() < current->getValue()) {
    if (current->getLeft() == NULL) {
      current->setLeft(nnode);
      insRepair(root, nnode);
    }
    else {
      insert(root, current->getLeft(), nnode);
    }
  }
  else {
    if (current->getRight() == NULL) {
      current->setRight(nnode);
      insRepair(root, nnode);
    }
    else {
      insert(root, current->getRight(), nnode);
    }
  }
}

void print(Node* root, Node* current, bool line[]) {
  if (root == NULL) {
    cout << "Tree is empty" << endl;
    return;
  }
  if (current == root) {
    if (current->getColor() == RED) {
      cout << "[R]";
    }
    else {
      cout << "[B]";
    }
    cout << current->getValue() << endl;
  }
  else {
    for (int i = 0; i < search(root, 1, current->getValue()) - 2; i++) {
      if (line[i] == true) {
        cout << " |     ";
      }
      else {
        cout << "       ";
      }
    }
    cout << " |-----";
    if (current->getColor() == RED) {
      cout << "[R]";
    }
    else {
      cout << "[B]";
    }
    cout << current->getValue() << endl;
  }

  if (current->getLeft() != NULL) {
    for (int i = 0; i < search(root, 1, current->getValue()) - 1; i++) {
      if (line[i] == true) {
        cout << " |     ";
      }
      else {
        cout << "       ";
      }
    }
    cout << " |" << endl;
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
        cout << " |     ";
      }
      else {
        cout << "       ";
      }
    }
    cout << " |" << endl;
    bool clone[100];
    for (int i = 0; i < 100; i++) {
      clone[i] = line[i];
    }
    print(root, current->getRight(), clone);
  }
}

void remove(Node* &root, Node* current, int key) {
  Node* parent;
  if (getParent(root, current) == nullptr) {
    parent = NULL;
  }
  else {
    parent = getParent(root, current);
  }
  if (key < current->getValue()) {
    if (current->getLeft() == NULL) {
      cout << "\nThe number is not in the tree" << endl;
      return;
    }
    else {
      remove(root, current->getLeft(), key);
    }
  }
  else if (key > current->getValue()) {
    if (current->getRight() == NULL) {
      cout << "\nThe number is not in the tree" << endl;
      return;
    }
    else {
      remove(root, current->getRight(), key);
    }
  }
  else {
    if (current->getLeft() == NULL && current->getRight() == NULL) {
      if (current != root) {
	if (current->getColor() == RED) {
	  if (parent->getLeft() == current) {
	    parent->setLeft(NULL);
	  }
	  else {
	    parent->setRight(NULL);
	  }
	}
	else {
	  delRepair(root, current);
	}
      }
      else {
	root = NULL;
      }
      delete current;
    }
    else if (current->getLeft() != NULL && current->getRight() != NULL) {
      int nvalue = successor(current->getRight())->getValue();
      remove(root, root, nvalue);
      current->setValue(nvalue);
    }
    else if (current->getLeft() != NULL) {
      if (parent->getLeft() == current) {
	parent->setLeft(current->getLeft());
	parent->getLeft()->setColor(BLACK);
      }
      else {
	parent->setRight(current->getLeft());
	parent->getRight()->setColor(BLACK);
      }
      delete current;
    }
    else {
      if (parent->getLeft() == current) {
	parent->setLeft(current->getRight());
	parent->getLeft()->setColor(BLACK);
      }
      else {
	parent->setRight(current->getRight());
	parent->getRight()->setColor(BLACK);
      }
      delete current;
    }
  }
}

void delRepair(Node* &root, Node* current) {
  Node* parent = getParent(root, current);
  Node* sibling = getSibling(root, current);

  if (parent->getLeft() == current) {
    if (sibling->getColor() == BLACK) {
      if (sibling->getRight()->getColor() == RED) {
	parent->setLeft(NULL);
	leftRotation(root, sibling);
	sibling->getRight()->setColor(BLACK);
      }
      else if (sibling->getLeft()->getColor() == RED) {
	parent->setRight(sibling->getLeft());
	sibling->getLeft()->setRight(sibling);
	sibling->setLeft(NULL);
	leftRotation(root, getParent(root, sibling));
	sibling->setColor(BLACK);
      }
      else {
	sibling->setColor(RED);
	parent->setColor(BLACK);
	parent->setLeft(NULL);
      }
    }
    else {
      parent->setLeft(NULL);
      leftRotation(root, sibling);
      parent->setColor(RED);
      sibling->setColor(BLACK);
    }
  }
  else {
    if (sibling->getColor() == BLACK) {
      if (sibling->getLeft()->getColor() == RED) {
	parent->setRight(NULL);
	rightRotation(root, sibling);
	sibling->getLeft()->setColor(BLACK);
      }
      else if (sibling->getRight()->getColor() == RED) {
	parent->setLeft(sibling->getRight());
	sibling->getRight()->setLeft(sibling);
	sibling->setRight(NULL);
	rightRotation(root, getParent(root, sibling));
	sibling->setColor(BLACK);
      }
      else {
	sibling->setColor(RED);
	parent->setColor(BLACK);
	parent->setRight(NULL);
      }
    }
    else {
      parent->setRight(NULL);
      rightRotation(root, sibling);
      parent->setColor(RED);
      sibling->setColor(BLACK);
    }
  }
}

Node* successor(Node* current) {
  if (current->getLeft() == NULL) {
    return current;
  }
  else {
    return successor(current->getLeft());
  }
}

Node* getParent(Node* root, Node* child) {
  if (child == nullptr) {
    return nullptr;
  }
  if (child == root) {
    return nullptr;
  }
  else {
    Node* current = root;
    while (current->getLeft() != NULL || current->getRight() != NULL) {
      if (current->getLeft() == child || current->getRight() == child) {
	return current;
      }
      else {
	if (child->getValue() > current->getValue()) {
	  current = current->getRight();
	}
	else {
	  current = current->getLeft();
	}
      }
      if (current == NULL) {
	return nullptr;
      }
    }
    return nullptr;
  }
}

Node* getSibling(Node* root, Node* key) {
  if (key == nullptr) {
    return nullptr;
  }
  if (getParent(root, key) == nullptr) {
    return nullptr;
  }
  else {
    if (getParent(root, key)->getLeft() == key) {
      return getParent(root, key)->getRight();
    }
    else {
      return getParent(root, key)->getLeft();
    }
  }
}

Node* getUncle(Node* root, Node* key) {
  if (key == nullptr) {
    return nullptr;
  }
  if (getParent(root, key) == nullptr) {
    return nullptr;
  }
  else {
    return getSibling(root, getParent(root, key));
  }
}

Node* getGrand(Node* root, Node* key) {
  return getParent(root, getParent(root, key));
}

void insRepair(Node* &root, Node* current) {
  Node* parent = getParent(root, current);
  Node* grand = getGrand(root, current);
  Node* uncle = getUncle(root, current);
  
  if (parent == nullptr) {
    current->setColor(BLACK);
  }
  else {
    if (grand != nullptr) {
      if (parent->getColor() == RED) {
	if (uncle == NULL || uncle->getColor() == BLACK) {
	  if (grand->getLeft() == parent) {
	    if (parent->getLeft() == current) {
	      rightRotation(root, parent);
	      parent->setColor(BLACK);
	      grand->setColor(RED);
	      if (grand == root) {
		root = parent;
	      }
	    }
	    else {
	      parent->setRight(current->getLeft());
	      current->setLeft(parent);
	      current->setLeft(parent);
	      grand->setLeft(current);
	      rightRotation(root, current);
	      current->setColor(BLACK);
	      grand->setColor(RED);
	      if (grand == root) {
		root = current;
	      }
	    }
	  }
	  else {
	    if (parent->getRight() == current) {
	      leftRotation(root, parent);
	      parent->setColor(BLACK);
	      grand->setColor(RED);
	      if (grand == root) {
		root = parent;
	      }
	    }
	    else {
	      parent->setLeft(current->getRight());
	      current->setRight(parent);
	      grand->setRight(current);
	      leftRotation(root, current);
	      current->setColor(BLACK);
	      grand->setColor(RED);
	      if (grand == root) {
		root = current;
	      }
	    }
	  }
	}
	else {
	  parent->setColor(BLACK);
	  uncle->setColor(BLACK);
	  grand->setColor(RED);
	  insRepair(root, grand);
	}
      }
    }
  }
}

void rightRotation(Node* root, Node* parent) {
  Node* grand = getParent(root, parent);
  if (grand != root) {
    Node* great = getParent(root, grand);
    grand->setLeft(parent->getRight());
    parent->setRight(grand);
    if (great->getLeft() == grand) {
      great->setLeft(parent);
    }
    else {
      great->setRight(parent);
    }
  }
  else {
    grand->setLeft(parent->getRight());
    parent->setRight(grand);
  }
}

void leftRotation(Node* root, Node* parent) {
  Node* grand = getParent(root, parent);
  if (grand != root) {
    Node* great = getParent(root, grand);
    grand->setRight(parent->getLeft());
    parent->setLeft(grand);
    if (great->getLeft() == grand) {
      great->setLeft(parent);
    }
    else {
      great->setRight(parent);
    }
  }
  else {
    grand->setRight(parent->getLeft());
    parent->setLeft(grand);
  }
}
