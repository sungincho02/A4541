#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  char input[80];
  char alnum[80];

  cout << "Enter a text" << endl;

  cin.get(input, 80);

  cout << input << endl;

  int count = 0;
  for (int i = 0; i < 80; i++) {
    if (input[i] != '\0') {
      if (isalnum(input[i])) {
        alnum[count] = input[i];
        count++;
      }
    }
    else {
      i = 80;
    }
  }
  alnum[count] = '\0';
  cout << count << endl;
  cout << alnum << endl;

  char reverse[count];
  for (int i = 0; i < count; i++) {
    reverse[i] = alnum[count - 1 - i];
  }
  reverse[count] = '\0';
  cout << reverse << endl;

  if (strcmp(alnum, reverse) == 0) {
    cout << "Palindrome" << endl;
  }
  else {
    cout << "Not a palindrome" << endl;
  }

  return 0;
}
