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
    drawBoard();
    cout << " " << turn << endl;
    do {
      cin >> input;
      while ((int)input[0] < 97 || (int)input[0] > 99 ||
	     input[1] != ',' ||
	     (int)input[2] < 49 || (int)input[2] > 51 ||
	     input[3] != '\0') {
        cout << "Please enter a valid coordinate" << endl;
        cin >> input;
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
      cout << " X Win!" << endl;
      newMatch();
    }
    else if (checkWin() == 2) {
      o_win++;
      drawBoard();
      cout << " O Win!" << endl;
      newMatch();
    }
    else if (checkWin() == 3) {
      tie++;
      drawBoard();
      cout << " Tie!" << endl;
      newMatch();
    }
  }

  return 0;
}

void drawBoard() {
  cout << "\n  1 2 3" << endl;
  cout << "a " << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
  cout << "b " << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
  cout << "c " << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
}

int checkWin() {
  bool win = false;
  int count = 0;

  //check win
  for (int i = 0; i < 3; i++) {
    if (board [i][0] != N && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
      win = true;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (board [0][i] != N && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
      win = true;
    }
  }
  if (board [0][0] != N && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
    win = true;
  }
  if (board [0][2] != N && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
    win = true;
  }
  if (win) {
    if (turn == OT) {
      return 1;
    }
    else {
      return 2;
    }
  }
  
  //check for draw
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == N) {
	count++;
      }
    }
  }
  if (count == 9) {
    return 3;
  }
  
  return 0;
}

void newMatch() {
  cout << "\nX Win: " << x_win << "\nO Win: " << o_win << "\nTie: " << tie << endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = N;
    }
  }
  turn = XT;

  char in;
  cout << "\nPlay another match? [Y/N]" << endl;
  cin >> in;
  while (in != 'Y' && in != 'N') {
    cout << "Please answer with a \"Y\" or \"N\"" << endl;
    cin >> in;
  }
  if (in == 'N') {
    replay = false;
  }
}
