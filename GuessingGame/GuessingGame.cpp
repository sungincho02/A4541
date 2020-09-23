#include <iostream>

using namespace std;

int main()
{
  //initialize variables
  bool replay = true;
  int number = 0;
  int guess = 0;
  int guessCount = 0;
  bool finish = false;
  char input = 0;
  //repeat until player chooses to stop
  while (replay == true) {
    //generate a random number between 0 and 100
    srand (time(NULL));
    number = rand() % 101;
    //reset variables
    guessCount = 0;
    finish = false;
    //ask for a guess
    cout << "Guess a number between 0 and 100" << endl;
    while (finish == false) {
      cin >> guess;
      //only accept a number between 0 and 100
      while (guess > 100 || guess < 0) {
        cout << "The number is between 0 and 100" << endl;
        cin >> guess;
      }
      //add 1 to number of guess
      guessCount++;
      //output the guess result
      if (guess == number) {
        //display number of guess and finish current round if guessed right
        cout << "You guessed the number!" << endl;
        cout << "Number of guess: " << guessCount << endl;
        finish = true;
      }
      else if (guess > number) {
        cout << "Your guess is higher than the number" << endl;
      }
      else if (guess < number) {
        cout << "Your guess is lower than the number" << endl;
      }
    }
    //ask if the user wants to play again
    cout << "Replay the game? [Y/N]" << endl;
    cin >> input;
    //only accept "Y" or "N"
    while (input != 'Y' && input != 'N') {
      cout << "Please answer with a \"Y\" or \"N\"" << endl;
      cin >> input;
    }
    //exit loop if answered "N"
    if (input == 'N') {
      replay = false;
    }
  }
}

