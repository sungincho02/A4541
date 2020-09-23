#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  char input[80];
  char alnum[80];

  //read in input
  cout << "Enter a text" << endl;
  cin.get(input, 80);

  //take only alphanumeric and change to lowercase
  int count = 0;
  for (int i = 0; i < 80; i++) {
    if (input[i] != '\0') {
      if (isalnum(input[i])) {
        alnum[count] = tolower(input[i]);
        count++;
      }
    }
    else {
      i = 80;
    }
  }
  alnum[count] = '\0';

  //copy the char array into another in reverse order
  char reverse[count];
  for (int i = 0; i < count; i++) {
    reverse[i] = alnum[count - 1 - i];
  }
  reverse[count] = '\0';

  //compare if the two char array are identical and output the result accordingly
  if (strcmp(alnum, reverse) == 0) {
    cout << "Palindrome" << endl;
  }
  else {
    cout << "Not a palindrome" << endl;
  }

  return 0;
}
