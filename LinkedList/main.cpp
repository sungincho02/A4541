#include <iostream>
#include <cstring>
#include <limits>
#include "Node.h"

using namespace std;

void add();
Node* prev(Node* next);
void sort();
void print(Node* current);
Node* search(int id, Node* current);
void del();
void avg();

Node* lead = NULL;

int main() {
  char input[99];
  bool quit = false;

  // set gpa precision
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // prompt for command
  while (!quit) {
    cout << "\n> ";
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (strcmp(input, "ADD") == 0) {
      add();
    }
    else if (strcmp(input, "PRINT") == 0) {
      print(lead);
    }
    else if (strcmp(input, "DELETE") == 0) {
      del();
    }
    else if (strcmp(input, "AVERAGE") == 0) {
      avg();
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

// add a student to the list
void add() {
  char fn[99];
  char ln[99];
  int id;
  float gpa;

  // set gpa precision
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  // prompt for the student information
  cout << "\nFirst name: ";
  cin.get(fn, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Last name: ";
  cin.get(ln, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "ID: ";
  cin >> id;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "GPA: ";
  cin >> gpa;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // create a node for the student and add it to the linked list
  Node* newnode = lead;
  if (newnode == NULL) {
    lead = new Node(new Student(fn, ln, id, gpa));
  }
  else {
    while (newnode->getNext() != NULL) {
      newnode = newnode->getNext();
    }
    newnode->setNext(new Node(new Student(fn, ln, id, gpa)));
  }

  sort();

  cout << "\nStudent added" << endl;
}

Node* prev(Node* next) {
  Node* current = lead;
  while (current->getNext() != NULL) {
    if (current->getNext() == next) {
      return current;
    }
    current = current->getNext();
  }
  return nullptr;
}

void sort() {
  int swap = 0;
  Node* current = lead;
  Node* temp;
  
  while (current->getNext() != NULL) {
    if (current->getStudent()->getID() > current->getNext()->getStudent()->getID()) {
      if (prev(current) != nullptr) {
	prev(current)->setNext(current->getNext());
      }
      temp = current->getNext()->getNext();
      current->getNext()->setNext(current);
      if (current == lead) {
	lead = current->getNext();
      }
      current->setNext(temp);
      swap++; 
    }
    else {
      current = current->getNext();
    }  
  }
  
  if (swap != 0) {
    sort();
  }
}

void print(Node* current) {
  if (current != NULL) {
    Student* student = current->getStudent();
    
    cout << "\nName: " << student->getFirst() << " " << student->getLast() << endl;
    cout << "ID: " << student->getID() << endl;
    cout << "GPA: " << student->getGPA() << endl;

    print(current->getNext());
  }
  else if (current == lead) {
    cout << "\nList is empty" << endl;
  }
}

Node* search(int id, Node* current) {
  if (current->getID() == id) {
    return current;
  }
  else if (current->getNext != NULL) {
    return search(current->getNext);
  }
  return nullptr;
}

void del() {
  int id;

  cout << "\nEnter the student ID: ";
  cin >> id;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
      
  Node* dnode = search(id, lead);

  if (prev(dnode) != nullptr) {
    prev(dnode)->setNext(dnode->getNext());
  }
  else if (dnode->getNext() != NULL) {
    lead = dnode->getNext();
  }
  else {
    lead = NULL;
  }

  delete dnode;
}

void avg() {
  if (lead == NULL) {
    cout << "\nList is empty" << endl;
    return;
  }
  
  float total = 0;
  int count = 0;
  float avg;
  Node* current = lead;
  
  while (current != NULL) {
    total += current->getGPA();
    count++
    current = current->getNext();
  }

  avg = total / count;

  cout << "Average GPA: " << avg << endl;
}
