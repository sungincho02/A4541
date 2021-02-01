#include <iostream>
#include <limits>
#include <cstring>
#include "Node.h"
#include "Tree.h"

using namespace std;

void push(Node* &head, Node* token);
char pop(Node* &head);
char peek(Node* head);
void enqueue(Node* &head, Node* &tail, Node* token);
char dequeue(Node* &head, Node* &tail);
void push(Tree* stack[], Tree* node);
void printInfix(Tree* root);
void printPostfix(Tree* root);
void printPrefix(Tree* root);

int main() {
  char input[50];
  char postfix[50];
  Node* ntoken;
  Node* stack = NULL;
  Node* qhead = NULL;
  Node* qtail = NULL;
  Tree* tstack[50];
  char* ttoken;
  Tree* tnode;
  Tree* root = NULL;
  Tree* left = NULL;
  Tree* right = NULL;

  // take user input
  cout << "Enter a mathematical expression without any spaces in between:" << endl;
  cout << "> ";

  cin.get(input, 50);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  // shutting yard algorithm
  for (int i = 0; i < strlen(input); i++) {  
    if (isdigit(input[i])) {
      ntoken = new Node(input[i]);
      enqueue(qhead, qtail, ntoken);
    }
    else if (input[i] == '(') {
      ntoken = new Node(input[i]);
      push(stack, ntoken);
    }
    else if (input[i] == ')') {
      while (peek(stack) != '(') {
	ntoken = new Node(' ');
	enqueue(qhead, qtail, ntoken);
	ntoken = new Node(pop(stack));
	enqueue(qhead, qtail, ntoken);
      }
      pop(stack);
    }
    else {
      ntoken = new Node(' ');
      enqueue(qhead, qtail, ntoken);
      if (input[i] == '+' || input[i] == '-') {
	while (peek(stack) == '*' || peek(stack) == '/' || peek(stack) == '^') {
	  ntoken = new Node(pop(stack));
	  enqueue(qhead, qtail, ntoken);
	  ntoken = new Node(' ');
	  enqueue(qhead, qtail, ntoken);
	}
	ntoken = new Node(input[i]);
	push(stack, ntoken);
      }
      else if (input[i] == '*' || input[i] == '/') {
	while (peek(stack) == '^') {
	  ntoken = new Node(pop(stack));
	  enqueue(qhead, qtail, ntoken);
	  ntoken = new Node(' ');
	  enqueue(qhead, qtail, ntoken);
	}
	ntoken = new Node(input[i]);
	push(stack, ntoken);
      }
      else {
	ntoken = new Node(input[i]);
	push(stack, ntoken);
      }
    }
  }
  while (stack != NULL) {
    ntoken = new Node(' ');
    enqueue(qhead, qtail, ntoken);
    ntoken = new Node(pop(stack));
    enqueue(qhead, qtail, ntoken);
  }
  ntoken = new Node(' ');
  enqueue(qhead, qtail, ntoken);

  // dequeque all tokens into postfix
  int index = 0;
  while (qhead != NULL) {
    postfix[index] = dequeue(qhead, qtail);
    index++;
  }
  postfix[index] = '\0';

  cout << "\nInfix: " << input << endl;
  cout << "Postfix: " << postfix << endl;
  
  // construct a binary expression tree
  int count;
  for (int i = 0; i < strlen(postfix); i++) {
    if (postfix[i] == ' ') {
      ttoken = new char[50];
      count = 0;
      while (qhead != NULL) {
	ttoken[count] = dequeue(qhead, qtail);
	count++;
      }
      ttoken[count] = '\0';

      tnode = new Tree(ttoken);
      push(tstack, tnode);

      // if most recently placed token is an operator, 
      if (!isdigit(tstack[0]->getValue()[0])) {
	root = tstack[0];
	right = tstack[1];
	left = tstack[2];
	root->setLeft(left);
	root->setRight(right);
	for (int i = 1; i < 48; i++) {
	  tstack[i] = tstack[i+2];
	}
      }
    }
    else {
      ntoken = new Node(postfix[i]);
      enqueue(qhead, qtail, ntoken);
    }
  }

  cout << "\nInfix(tree): ";
  printInfix(root);
  cout << "\nPostfix(tree): ";
  printPostfix(root);
  cout << "\nPrefix(tree): ";
  printPrefix(root);

  return 0;
}

void push(Node* &head, Node* token) {
  if (head != NULL) {
    token->setNext(head);
  }
  head = token;
}

char pop(Node* &head) {
  Node* temp = head;
  head = head->getNext();
  char value = temp->getValue();
  delete temp;
  temp = NULL;
  return value;
}

char peek(Node* head) {
  if (head == NULL) {
    return '\0';
  }
  return (head->getValue());
}

void enqueue(Node* &head, Node* &tail, Node* token) {
  if (tail != NULL) {
    tail->setNext(token);
  }
  else {
    head = token;
  }
  tail = token;
}

char dequeue(Node* &head, Node* &tail) {
  Node* temp = head;
  head = head->getNext();
  if (head == NULL) {
    tail = NULL;
  }
  char value = temp->getValue();
  delete temp;
  temp = NULL;
  return value;
}

void push(Tree* stack[], Tree* node) {
  for (int i = 49; i > 0; i--) {
    stack[i] = stack[i-1];
  }
  stack[0] = node; 
}

void printInfix(Tree* root) {
  if (root != NULL) {
    if (!isdigit(root->getValue()[0])) {
      cout << "(";
    }
    printInfix(root->getLeft());
    cout << root->getValue();
    printInfix(root->getRight());
    if (!isdigit(root->getValue()[0])) {
      cout << ")";
    }
  }
}

void printPostfix(Tree* root) {
  if (root != NULL) {
    printPostfix(root->getLeft());
    printPostfix(root->getRight());
    cout << root->getValue() << " ";
  }
}

void printPrefix(Tree* root) {
  if (root != NULL) {
    cout << root->getValue() << " ";
    printPrefix(root->getLeft());
    printPrefix(root->getRight());
  }
}
