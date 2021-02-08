#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include "Node.h"

using namespace std;

// function prototypes
int search(Node* current, int level, int key);
void insert(Node* &root, Node* current, Node* nnode);
void print(Node* root, Node* current, bool line[]);
void remove(Node* &root, Node* current, int key);
bool delRepair(Node* &root, Node* current);
Node* successor(Node* current);
void insRepair(Node* &root, Node* current);
Node* getParent(Node* root, Node* child);
Node* getUncle(Node* root, Node* key);
Node* getSibling(Node* root, Node* key);
void leftRotation(Node* &root, Node* parent);
void rightRotation(Node* &root, Node* parent);

// const variables
const bool RED = true;
const bool BLACK = false;
const bool LEFT = true;
const bool RIGHT = false;

int main() {
  // initialize variables
  char input[99];
  int method;
  int number;
  int size;
  Node* root = NULL;
  Node* nnode;
  bool quit = false;
  bool line[100] = {false};
  
  // print out commands
  cout << "\nCommands:" << endl;
  cout << "ADD" << endl;
  cout << "BATCH" << endl;
  cout << "PRINT" << endl;
  cout << "DELETE" << endl;
  cout << "SEARCH" << endl;
  cout << "QUIT" << endl;
  
  // prompt commands
  while (!quit) {
    cout << "\n> ";
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (strcmp(input, "ADD") == 0) {	// add a value to the tree
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
    else if (strcmp(input, "BATCH") == 0) {	// add multiple values to the tree either manually or from a file
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
    else if (strcmp(input, "PRINT") == 0) {	// print out the tree
      cout << "\n";
      print(root, root, line);
    }
    else if (strcmp(input, "DELETE") == 0) {	// remove a value from the tree
      cout << "\nEnter the number you want to remove: " << endl;
      cout << "> ";
      cin >> number;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      remove(root, root, number);
    }
    else if (strcmp(input, "SEARCH") == 0) {	// search a value from the tree
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

// search for a value in the tree. If it exists, return its level. If not, return 0.
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

// insert a value to the tree
void insert(Node* &root, Node* current, Node* nnode) {
  // skip if it's a duplicate
  if (search(root, 1, nnode->getValue()) != 0) {
    cout << "Dupulicate skipped" << endl;
    return;
  }
  
  // go through nodes until empty spot is found then add and repair
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

// print out the tree
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

// remove a value from the tree
void remove(Node* &root, Node* current, int key) {
  Node* parent;
  if (getParent(root, current) == nullptr) {
    parent = NULL;
  }
  else {
    parent = getParent(root, current);
  }
	
  // find the value
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
  else {	// once the value is found,
    if (current->getLeft() == NULL && current->getRight() == NULL) {	// when it has no children
      if (current != root) {
	if (current->getColor() == RED) {	// when it's red, just remove
	  if (parent->getLeft() == current) {
	    parent->setLeft(NULL);
	  }
	  else {
	    parent->setRight(NULL);
	  }
	}
	else {	// when it's black, repair and remove
	  if (delRepair(root, current) == LEFT) {
	    getParent(root, current)->setLeft(NULL);
	  }
	  else {
	    getParent(root, current)->setRight(NULL);
	  }
	}
      }
      else {	// if it's root, reset root
	root = NULL;
      }
      delete current;
    }
    else if (current->getLeft() != NULL && current->getRight() != NULL) {	// when it has two children, remove its inorder successor instead and swap value
      int nvalue = successor(current->getRight())->getValue();
      remove(root, root, nvalue);
      current->setValue(nvalue);
    }
    // when it has a single child, place its child in its place
    else if (current->getLeft() != NULL) {
      if (current != root) {
	if (parent->getLeft() == current) {
	  parent->setLeft(current->getLeft());
	  parent->getLeft()->setColor(BLACK);
	}
	else {
	  parent->setRight(current->getLeft());
	  parent->getRight()->setColor(BLACK);
	}
      }
      else {
	root = current->getLeft();
      }
      delete current;
    }
    else {
      if (current != root) {
	if (parent->getLeft() == current) {
	  parent->setLeft(current->getRight());
	  parent->getLeft()->setColor(BLACK);
	}
	else {
	  parent->setRight(current->getRight());
	  parent->getRight()->setColor(BLACK);
	}
      }
      else {
	root = current->getRight();
      }
      delete current;
    }
  }
}

// deletion repair algorithm
bool delRepair(Node* &root, Node* current) {
  Node* parent = getParent(root, current);
  Node* sibling = getSibling(root, current);
  
  if (parent->getLeft() == current) {	// when the value is a left child,
    if (sibling->getColor() == BLACK) {	// when sibling is black, 
      if (sibling->getRight() != NULL) {
	if (sibling->getRight()->getColor() == RED) {	// when sibling has a red right child
	  leftRotation(root, sibling);
	  sibling->getRight()->setColor(BLACK);
	}
	else if (sibling->getLeft() != NULL) {	// when sibling has a red left child and does not have a red right child
	  if (sibling->getLeft()->getColor() == RED) {
	    parent->setRight(sibling->getLeft());
	    sibling->getLeft()->setRight(sibling);
	    sibling->setLeft(NULL);
	    leftRotation(root, getParent(root, sibling));
	    sibling->setColor(BLACK);
	  }
	  else {	// when sibling has no red child
	    sibling->setColor(RED);
	    if (parent != root) {
	      if (parent->getColor() == RED) {
		parent->setColor(BLACK);
	      }
	      else {
		delRepair(root, parent);
	      }
	    }
	  }
	}
	else {	// (no red child)
	  sibling->setColor(RED);
	  if (parent != root) {
	    if (parent->getColor() == RED) {
	      parent->setColor(BLACK);
	    }
	    else {
	      delRepair(root, parent);
	    }
	  }
	}
      }
      else if (sibling->getLeft() != NULL) {
	if (sibling->getLeft()->getColor() == RED) {	// (red left child only)
	  parent->setRight(sibling->getLeft());
	  sibling->getLeft()->setRight(sibling);
	  sibling->setLeft(NULL);
	  leftRotation(root, getParent(root, sibling));
	  sibling->setColor(BLACK);
	}
	else {	// (no red child)
	  sibling->setColor(RED);
	  if (parent != root) {
	    if (parent->getColor() == RED) {
	      parent->setColor(BLACK);
	    }
	    else {
	      delRepair(root, parent);
	    }
	  }
	}
      }
      else {	// (no red child)
	sibling->setColor(RED);
	if (parent != root) {
	  if (parent->getColor() == RED) {
	    parent->setColor(BLACK);
	  }
	  else {
	    delRepair(root, parent);
	  }
	}
      }
    }
    else {	// when sibling is red
      leftRotation(root, sibling);
      sibling->setColor(BLACK);
      parent->getRight()->setColor(RED);
    }
    return LEFT;
  }
  else {	// when the value is a right child, do simply the opposite(in terms of direction) of when it's a left child
    if (sibling->getColor() == BLACK) {
      if (sibling->getLeft() != NULL) {
	if (sibling->getLeft()->getColor() == RED) {
	  rightRotation(root, sibling);
	  sibling->getLeft()->setColor(BLACK);
	}
	else if (sibling->getRight() != NULL) {
	  if (sibling->getRight()->getColor() == RED) {
	    parent->setLeft(sibling->getRight());
	    sibling->getRight()->setLeft(sibling);
	    sibling->setRight(NULL);
	    rightRotation(root, getParent(root, sibling));
	    sibling->setColor(BLACK);
	  }
	  else {
	    sibling->setColor(RED);
	    if (parent != root) {
	      if (parent->getColor() == RED) {
		parent->setColor(BLACK);
	      }
	      else {
		delRepair(root, parent);
	      }
	    }
	  }
	}
	else {
	  sibling->setColor(RED);
	  if (parent != root) {
	    if (parent->getColor() == RED) {
	      parent->setColor(BLACK);
	    }
	    else {
	      delRepair(root, parent);
	    }
	  }
	}
      }
      else if (sibling->getRight() != NULL) {
	if (sibling->getRight()->getColor() == RED) {
	  parent->setLeft(sibling->getRight());
	  sibling->getRight()->setLeft(sibling);
	  sibling->setRight(NULL);
	  rightRotation(root, getParent(root, sibling));
	  sibling->setColor(BLACK);
	}
	else {
	  sibling->setColor(RED);
	  if (parent != root) {
	    if (parent->getColor() == RED) {
	      parent->setColor(BLACK);
	    }
	    else {
	      delRepair(root, parent);
	    }
	  }
	}
      }
      else {
	sibling->setColor(RED);
	if (parent != root) {
	  if (parent->getColor() == RED) {
	    parent->setColor(BLACK);
	  }
	  else {
	    delRepair(root, parent);
	  }
	}
      }
    }
    else {
      rightRotation(root, sibling);
      sibling->setColor(BLACK);
      parent->getLeft()->setColor(RED);
    }
    return RIGHT;
  }
}

// return an inorder successor
Node* successor(Node* current) {
  if (current->getLeft() == NULL) {
    return current;
  }
  else {
    return successor(current->getLeft());
  }
}

// return parent node
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

// return sibling node
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

// return uncle node
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

// return grandfather node
Node* getGrand(Node* root, Node* key) {
  return getParent(root, getParent(root, key));
}

// insertion repair algorithm
void insRepair(Node* &root, Node* current) {
  Node* parent = getParent(root, current);
  Node* grand = getGrand(root, current);
  Node* uncle = getUncle(root, current);
  
  if (parent == nullptr) {	// set root to black
    current->setColor(BLACK);
  }
  else {
    if (grand != nullptr) {
      if (parent->getColor() == RED) {
	if (uncle == NULL || uncle->getColor() == BLACK) {	// when uncle is black
	  if (grand->getLeft() == parent) {	// when parent is left child
	    if (parent->getLeft() == current) {	// when current is left child as well
	      rightRotation(root, parent);
	      parent->setColor(BLACK);
	      grand->setColor(RED);
	      if (grand == root) {
		root = parent;
	      }
	    }
	    else {	// when current is right child
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
	  else {	// when parent is right child
	    if (parent->getRight() == current) {	// when current is right child as well
	      leftRotation(root, parent);
	      parent->setColor(BLACK);
	      grand->setColor(RED);
	      if (grand == root) {
		root = parent;
	      }
	    }
	    else {	// when current is left child
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
	else {	// when uncle is red
	  parent->setColor(BLACK);
	  uncle->setColor(BLACK);
	  grand->setColor(RED);
	  // repeat for grandfather
	  insRepair(root, grand);
	}
      }
    }
  }
}

// right rotation
void rightRotation(Node* &root, Node* parent) {
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
    root = parent;
  }
}

// left rotation
void leftRotation(Node* &root, Node* parent) {
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
    root = parent;
  }
}
