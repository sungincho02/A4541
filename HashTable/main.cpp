#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

struct Student {
  char fn[20];
  char ln[20];
  int id;
  flaot gpa;
  Student* next;
  int chain;
};

// function prototypes
int hash(int size, Student* key);
void rehash(Student** p);
void link(Student* prev, Student* current);
void add(Student** p, Student* nstudent);
void print(Student** p);
void del(Student** p, int id);
void rand(Student** p, int &id);

int main() {
  boolean quit = false;
  Student** p;
  char fn[20];
  char ln[20];
  int id;
  float gpa;
  int nid = 100000;

  // create a table
  Student* table[100];
  p = table;

  // set precision
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // print commands
  cout << "\nCommands:" << endl;
  cout << "ADD" << endl;
  cout << "PRINT" << endl;
  cout << "DELETE" << endl;
  cout << "RANDOM" << endl;
  cout << "QUIT" << endl;
  
  // prompt for command
  while (!quit) {
    cout << "\n> ";
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (strcmp(input, "ADD") == 0) {
      // prompt for the student information
      cout << "\nFirst name: ";
      cin.get(fn, 20);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
      cout << "Last name: ";
      cin.get(ln, 20);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "ID: ";
      cin >> id;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "GPA: ";
      cin >> gpa;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      Student* nstudent = new Student(fn, ln, id, gpa);

      // add the new student to the table
      add(p, nstudent);
    }
    else if (strcmp(input, "PRINT") == 0) {
      print(p);
    }
    else if (strcmp(input, "DELETE") == 0) {
      // prompt for student id
      cout << "\nEnter the student ID: ";
      cin >> id;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // delete the specified student
      del(p, id);
    }
    else if (strcmp(input, "RANDOM") == 0) {
      rand(p, nid);
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

int hash(int size, Student* key) {
  return key->id % size;
}

void rehash(Student** p) {

}

void link(Student* prev, Student* current) {

}

void add(Student** p, Student* nstudent) {
  
}

void print(Student** p) {

}

void del(Student** p, int id) {
  
}

void rand(Student** p, int &id) {
  
}
