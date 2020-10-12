#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Student {
  char fn[20];
  char ln[20];
  int id;
  float gpa;
};

void add(vector<Student*>* list);
void print(vector<Student*>* list);
void del(vector<Student*>* list);

int main() {
  vector<Student*>* list = new vector<Student*>();
  bool quit = false;
  string input;

  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  while (!quit) {
    cout << "\nEnter a command" << endl;
    cin >> input;

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

void print(vector<Student*>* list) {
  cout << endl;
  for (int i = 0; i < list -> size(); i++) {
    cout << list -> at(i) -> fn << " " << list -> at(i) -> ln << ", " << list -> at(i) -> id << ", " << list -> at(i) -> gpa << endl;
  }
}

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
