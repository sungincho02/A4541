#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// function prototypes
int first(int parent);
int second(int parent);
int parent(int child);
int gen(int current);
void draw(int index, int heap[], bool line[]);
void insert(int list[], int index, int heap[]);
void upheap(int current, int heap[]);

int main() {
  // initialize variables
  char input[99];
  int method;
  int list[101] = {0};
  int heap[201] = {0};
  
  // take input
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
    
    for (int i = 0; i < 101; i++) {
      infile >> list[i];
    }
  }
  else if (method == 2) {
    cout << "\nEnter the numbers:" << endl;
    cout << "> ";

    for (int i = 0; i < 101; i++) {
      cin >> list[i];
    }
  }
  
  // input into heap
  insert(list, 1, heap);

  // print out the list
  cout << "\nList:" << endl;
  int index = 0;
  while (list[index] != 0) {
    cout << list[index] << " ";
    index++;
  }
  cout << endl;

  // print out the heap
  cout << "\nHeap:" << endl;
  int index2 = 1;
  while (heap[index2] != 0) {
    cout << heap[index2] << " ";
    index2++;
  }
  cout << endl;

  // draw the diagram
  cout << "\nDiagram:" << endl;
  bool line[5] = {false};
  draw(1, heap, line);
  
  return 0;
}

int first(int parent) {
  return (parent * 2);
}

int second(int parent) {
  return (parent * 2 + 1);
}

int parent(int child) {
  return (child / 2);
}

int gen(int current) {
  int count = 1;
  while (current != 1) {
    count++;
    current = current / 2;
  }
  return count;
}

void insert(int list[], int index, int heap[]) {
  heap[index] = list[index-1];
  upheap(index, heap);
  if (index < 99 && list[index] != 0) {
    insert(list, index+1, heap);
  }
}

void upheap(int current, int heap[]) {
  if (current != 1) {
    if (heap[current] > heap[parent(current)]) {
      int temp = heap[current];
      heap[current] = heap[parent(current)];
      heap[parent(current)] = temp;
      upheap(parent(current), heap);
    }
  }
}

void draw(int index, int heap[], bool line[]) {
  if (index == 1) {
    cout << heap[1] << endl;
  }
  else {
    for (int i = 0; i < gen(index) - 2; i++) {
      if (line[i] == true) {
	cout << "|   ";
      }
      else {
	cout << "    ";
      }
    }
    cout << "|---" << heap[index] << endl;
  }
  
  if (heap[first(index)] != 0) {
    for (int i = 0; i < gen(index) - 1; i++) {
      if (line[i] == true) {
	cout << "|   ";
      }
      else {
	cout << "    ";
      }
    }
    cout << "|" << endl;
    bool nline[5];
    for (int i = 0; i < 5; i++) {
      nline[i] = line[i];
    }
    if (heap[second(index)] != 0) {
      nline[gen(index) - 1] = true;
    }
    draw(first(index), heap, nline);
  }
  if (heap[second(index)] != 0) {
    for (int i = 0; i < gen(index) - 1; i++) {
      if (line[i] == true) {
	cout << "|   ";
      }
      else {
	cout << "    ";
      }
    }
    cout << "|" << endl;
    bool clone[5];
    for (int i = 0; i < 5; i++) {
      clone[i] = line[i];
    }
    draw(second(index), heap, clone);
  }
}
