#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  char input[80];
  char alnum[80];

  cout << "Enter a text" << endl;

  cin.get(input, 80);
  cin.get();

  int count = 0;
  for (int i = 0; i < 80; i++) {
    if (isalnum(input[i])) {
      alnum[count] = input[i];
      count++;
    }
  }
  alnum[count] = '\0';

  char reverse[count];
  for (int i = 0; i < count; i++) {
    reverse[i] = alnum[count - 1 - i];
  }
  reverse[count] = '\0';

  if (strcmp(alnum, reverse) == 0) {
    cout << "Palindrome" << endl;
  }
  else {
    cout << "Not a palindrome" << endl;
  }

  return 0;
}
