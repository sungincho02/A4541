/*
 * Project: TicTacToe
 * Author: Sungin Cho
 * Date: 9/30/20 
 * Instructor: Jason Galbraith
 * Description: This is a tictactoe program for two players
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <limits>

using namespace std;

const string XT = "X Turn",
  OT = "O Turn";
const char N = ' ',
  X = 'X',
  O = 'O';

string turn = XT;
int x_win = 0,
  o_win = 0,
  tie = 0;
vector<vector<char>> board{{N, N, N},
                           {N, N, N},
                           {N, N, N}};
char input[3];
int a, n;
bool replay = true;
bool occupied = true;

void drawBoard();
int checkWin();
void newMatch();

int main() {

  cout << "Enter a coordinate to make a move" << endl;
  cout << "ex) a,2" << endl;
  while (replay) {
    cout << endl;
    drawBoard();
    cout << " " << turn << endl;
    do {
      cin >> input;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      while (!isalpha(input[0])|| input[1] != ',' || !isdigit(input[2]) || input[2] == '0') {
        cout << "Please enter a valid coordinate" << endl;
        cin >> input;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      a = (int)tolower(input[0]) - 97;
      n = (int)input[2] - 49;
      if (board[a][n] == N) {
	occupied = false;
      }
      else {
	cout << "That spot is already taken" << endl;
	occupied = true;
      }
    } while (occupied);
    if (turn == XT) {
      board[a][n] = X;
      turn = OT;
    }
    else {
      board[a][n] = O;
      turn = XT;
    }
    if (checkWin() == 1) {
      x_win++;
      drawBoard();
      cout << "X Win!" << endl;
      newMatch();
    }
    else if (checkWin() == 2) {
      o_win++;
      drawBoard();
      cout << "O Win!" << endl;
      newMatch();
    }
    else if (checkWin() == 3) {
      tie++;
      drawBoard();
      cout << "Tie!" << endl;
      newMatch();
    }
  }

  return 0;
}

void drawBoard() {
  cout << "  1 2 3" << endl;
  cout << "a " << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
  cout << "b " << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
  cout << "c " << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
}

int checkWin() {
  return 0;
}

void newMatch() {
  cout << "X Win: " << x_win << " O Win: " << o_win << " Tie: " << tie << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = N;
    }
  }
  turn = XT;

  char in;
  cout << "Play another match? [Y/N]" << endl;
  cin >> in;

  while (in != ('Y', 'N')) {
    cout << "Please answer with a \"Y\" or \"N\"" << endl;
    cin >> in;
  }

  if (in == 'N') {
    replay = false;
  }
}
