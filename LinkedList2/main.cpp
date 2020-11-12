#include <iostream>
#include <cstring>
#include <limits>
#include "Node.h"

using namespace std;

// function prototypes
Node* prev(Node* head, Node* next);
void add(Node* &head, Node* nnode, Node* current);
void print(Node* head, Node* current);
void del(Node* &head, int id, Node* current);
void avg(Node* head);

int main() {
  Node* head = NULL;
  char input[99];
  bool quit = false;
  char fn[99];
  char ln[99];
  int id;
  float gpa;

  // set gpa precision
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // print commands
  cout << "\nCommands:" << endl;
  cout << "ADD" << endl;
  cout << "PRINT" << endl;
  cout << "DELETE" << endl;
  cout << "AVERAGE" << endl;
  cout << "QUIT" << endl;
  
  // prompt for command
  while (!quit) {
    cout << "\n> ";
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (strcmp(input, "ADD") == 0) {
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

      Node* nnode = new Node(new Student(fn, ln, id, gpa));

      // add the new student to the list
      add(head, nnode, head);
    }
    else if (strcmp(input, "PRINT") == 0) {
      print(head, head);
    }
    else if (strcmp(input, "DELETE") == 0) {
      // prompt for student id
      cout << "\nEnter the student ID: ";
      cin >> id;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // delete the specified student
      del(head, id, head);
    }
    else if (strcmp(input, "AVERAGE") == 0) {
      avg(head);
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

// find and return prev node
Node* prev(Node* head, Node* next) {
  Node* current = head;
  while (current->getNext() != NULL) {
    if (current->getNext() == next) {
      return current;
    }
    current = current->getNext();
  }
  return nullptr;
}

// insert a student to the list in correct position
void add(Node* &head, Node* nnode, Node* current) {
  // add the student if end of the list is reached or student with bigger ID number is found
  if (current == NULL) {
    if (current == head) {
      head = nnode;
    }
    else {
      prev(head, current)->setNext(nnode);
    }
    cout << "\nStudent added" << endl;
  }
  else if (nnode->getStudent()->getID() < current->getStudent()->getID()) {
    if (current == head) {
      head = nnode;
    }
    else {
      prev(head, current)->setNext(nnode);
    }
    nnode->setNext(current);
    cout << "\nStudent added" << endl;
  }
  // if not, check next in the list
  else {
    add(head, nnode, current->getNext());
  }
}

// print all students
void print(Node* head, Node* current) {
  // print student information
  if (current != NULL) {
    Student* student = current->getStudent();
    
    cout << "\nName: " << student->getFirst() << " " << student->getLast() << endl;
    cout << "ID: " << student->getID() << endl;
    cout << "GPA: " << student->getGPA() << endl;

    // next student
    print(head, current->getNext());
  }
  // notify if list is empty
  else if (current == head) {
    cout << "\nList is empty" << endl;
  }
}

// delete the student with the given student ID
void del(Node* &head, int id, Node* current) {
  // notify if the student does not exist in the list
  if (current == NULL) {
    if (current == head) {
      cout << "\nList is empty" << endl;
    }
    else {
      cout << "\nThe student does not exist" << endl;
    }
  }
  // remove student if ID matches
  else if (current->getStudent()->getID() == id) {
    if (current == head) {
      head = current->getNext();
    }
    else {
      prev(head, current)->setNext(current->getNext());
    }
    delete current;
    cout << "\nStudent deleted" << endl;
  }
  // if not, check next student
  else {
    del(head, id, current->getNext());
  }
}

// print average GPA of the students
void avg(Node* head) {
  if (head == NULL) {
    cout << "\nList is empty" << endl;
    return;
  }
  
  float total = 0;
  int count = 0;
  float avg;
  Node* current = head;
  
  while (current != NULL) {
    total += current->getStudent()->getGPA();
    count++;
    current = current->getNext();
  }

  avg = total / count;

  cout << "\nAverage GPA: " << avg << endl;
}
