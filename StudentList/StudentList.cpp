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

vector<Student> list;

void add();
void print();
void del();

int main() {
  bool quit = false;
  string input;
  
  while (!quit) {
    cout << "\nEnter a command" << endl;
    cin >> input;

    if (input == "ADD") {
      add();
    }
    else if (input == "PRINT") {
      print();
    }
    else if (input == "DELETE") {
      del();
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

void add() {
  Student nstdnt;
  cout << "\nFirst name:" << endl;
  cin,getline(nstdnt.fn, 20);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Last name:" << endl;
  cin.getline(nstdnt.ln, 20);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Student ID:" << endl;
  cin >> nstdnt.id;
  while (nstdnt.id < 0) {
    cout << "Invalid student ID" << endl;
    cin >> nstdnt.id;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "GPA:" << endl;
  cin >> nstdnt.gpa;
  while (nstdnt.gpa > 5 || nstdnt.gpa < 0) {
    cout << "Invalid GPA" << endl;
    cin >> nstdnt.gpa;
  }

  list.push_back(nstdnt);
}

void print() {

}

void del() {

}
