#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

struct Student {  
  char fn[20];
  char ln[20];
  int id;
  float gpa;
  Student* next;
};

// function prototypes
int hashFunction(int size, Student* key);
void rehash(int &size, Student** &p);
void add(int &size, Student** &p, Student* nstudent);
void print(int size, Student** p);
void del(int size, Student** p, int id);
void rm(Student** p, Student* prev, Student* s, int index);

int main() {
  ifstream* infn;
  ifstream* inln;
  bool quit = false;
  char input[99];
  Student** p;
  char nfn[20];
  char nln[20];
  int nid;
  float ngpa;
  int number;
  int rfn;
  int rln;
  float rgpa;
  int rid = 100000;
  int size = 100;
  Student* ptr;

  srand(time(NULL));
  
  // create a table
  Student* table[size];
  p = table;

  for (int i = 0; i < size; i++) {
    p[i] = nullptr;
  }
  
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
      cin.get(nfn, 20);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
      cout << "Last name: ";
      cin.get(nln, 20);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "ID: ";
      cin >> nid;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "GPA: ";
      cin >> ngpa;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // add the new student to the table
      ptr = new Student();
      strcpy(ptr->fn, nfn);
      strcpy(ptr->ln, nln);
      ptr->id = nid;
      ptr->gpa = ngpa;
      ptr->next = NULL;
  
      add(size, p, ptr);
    }
    else if (strcmp(input, "PRINT") == 0) {
      print(size, p);
    }
    else if (strcmp(input, "DELETE") == 0) {
      // prompt for student id
      cout << "\nEnter the student ID: ";
      cin >> nid;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // delete the specified student
      del(size, p, nid);
    }
    else if (strcmp(input, "RANDOM") == 0) {
      cout << "\nEnter the number of students to add: ";
      cin >> number;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      
      for (int i = 0; i < number; i++) {
	infn = new ifstream();
	inln = new ifstream();
	
	infn->open("Firstname.txt");
	inln->open("Lastname.txt");
	
	rfn = rand() % 30 + 1;
	rln = rand() % 30 + 1;
	ngpa = rand() % 300 + 101;
	ngpa = ngpa / 100;
	for (int i = 0; i < rfn; i++) {
	  *infn >> nfn;
	}
	for (int i = 0; i < rln; i++) {
	  *inln >> nln;
	}

	ptr = new Student();
	strcpy(ptr->fn, nfn);
	strcpy(ptr->ln, nln);
	ptr->id = rid;
	ptr->gpa = ngpa;
	ptr->next = NULL;

	add(size, p, ptr);

	rid++;
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

// hash function
int hashFunction(int size, Student* key) {
  return key->id % size;
}

// create a table that is twice as big and rehash
void rehash(int &size, Student** &p) {
  Student** temp = p;
  int tsize = size;
  size = size * 2;
  p = new Student*[size];

  for (int i = 0; i < size; i++) {
    p[i] = nullptr;
  }

  cout << "\nRehashing..." << endl;
  
  for (int i = 0; i < tsize; i++) {
    if (temp[i] != nullptr) {
      add(size, p, temp[i]);
      Student* current = temp[i];
      Student* ntemp;
      while (current->next != NULL) {
	ntemp = current->next;
	current->next = NULL;
	current = ntemp;
	add(size, p, current);
      }
    }
  }
}

// add a student
void add(int &size, Student** &p, Student* nstudent) {
  int h = hashFunction(size, nstudent);

  if (p[h] == nullptr) {
    p[h] = nstudent;
  }
  else {
    Student* prev = p[h];
    int chain = 0;
    while (prev->next != NULL) {
      prev = prev->next;
      chain++;
    }
    if (chain == 3) {
      rehash(size, p);
      add(size, p, nstudent);
    }
    else {
      prev->next = nstudent;
    }
  }
  
}

void detail(Student* s) {
  cout << "\nName: " << s->fn << " " << s->ln << endl;
  cout << "ID: " << s->id << endl;
  cout << "GPA: " << s->gpa << endl;
}

void print(int size, Student** p) {
  bool empty = true;
  for (int i = 0; i < size; i++) {
    if (p[i] != nullptr) {
      empty = false;

      cout << "\nIndex: " << i;
      
      detail(p[i]);
      Student* current = p[i]; 
      while (current->next != NULL) {
	current = current->next;
	detail(current);
      }
    }
  }
  if (empty) {
    cout << "\nList is empty" << endl;
  }
}

void del(int size, Student** p, int id) {
  bool empty = true;
  for (int i = 0; i < size; i++) {
    if (p[i] != nullptr) {
      empty = false;
      if (p[i]->id == id) {
	rm(p, nullptr, p[i], i);
	return;
      }
      Student* current = p[i]; 
      while (current->next != NULL) {
	if (current->next->id == id) {
	  rm(p, current, current->next, i);
	  return;
	}
	current = current->next;
      }
    }
  }
  if (empty) {
    cout << "\nList is empty" << endl;
  }
  else {
    cout << "\nCan't find the student" << endl;
  }
}

void rm(Student** p, Student* prev, Student* s, int index) {
  if (prev != nullptr) {
    prev->next = s->next;
    delete s;
  }
  else {
    if (s->next != NULL) {
      p[index] = s->next;
    }
    else {
      p[index] = nullptr;
    }
    delete s;
  }
}
