/*
 * Project: StudentList
 * Author: Sungin Cho
 * Date: 10/11/20
 * Instructor: Jason Galbraith
 * Description: This is a program for managing list of students
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// struct that keeps name, id, and gpa
struct Student {
  char fn[20];
  char ln[20];
  int id;
  float gpa;
};

// function prototypes
void add(vector<Student*>* list);
void print(vector<Student*>* list);
void del(vector<Student*>* list);

int main() {
  // creating variables
  vector<Student*>* list = new vector<Student*>();
  bool quit = false;
  string input;

  // setting gpa precision
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  while (!quit) {
    cout << "\nEnter a command" << endl;
    cin >> input;

    // resolve the user command
    if (input == "ADD") {
      add(list);
    }
    else if (input == "PRINT") {
      print(list);
    }
    else if (input == "DELETE") {
      del(list);
    }
    else if (input == "QUIT") {
      quit = true;
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
  
  return 0;
}

// function that prompts for student information and adds to the list
void add(vector<Student*>* list) {
  Student* nstdnt = new Student();
  cout << "\nFirst name:" << endl;
  cin >> nstdnt -> fn;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Last name:" << endl;
  cin >> nstdnt -> ln;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Student ID:" << endl;
  cin >> nstdnt -> id;
  while (nstdnt ->id < 0) {
    cout << "Invalid student ID" << endl;
    cin >> nstdnt -> id;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "GPA:" << endl;
  cin >> nstdnt -> gpa;
  while (nstdnt -> gpa > 5 || nstdnt -> gpa < 0) {
    cout << "Invalid GPA" << endl;
    cin >> nstdnt -> gpa;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  list -> push_back(nstdnt);
  cout << "Student added" << endl;
}

// function that prints all the students in the list
void print(vector<Student*>* list) {
  cout << endl;
  for (int i = 0; i < list -> size(); i++) {
    cout << list -> at(i) -> fn << " " << list -> at(i) -> ln << ", " << list -> at(i) -> id << ", " << list -> at(i) -> gpa << endl;
  }
}

// function that prompts for student ID and removes the student
void del(vector<Student*>* list) {
  int id;
  bool valid = false;
  
  cout << "\nEnter the student ID" << endl;
  cin >> id;

  for (int i = 0; i < list -> size(); i++) {
    if (id == list -> at(i) -> id) {
      list -> erase(list -> begin() + i);
      valid = true;
    }
  }

  if (valid) {
    cout << "Student deleted" << endl;
  }
  else {
    cout << "That student does not exist" << endl;
  }
}
