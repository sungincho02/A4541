#include <iostream>
#include <vector>
#include <string>

using namespace std;

void drawBoard(vector<vector<char>> board, string turn);
int checkWin();

int main() {
  const string XT = "X Turn",
    OT = "O Turn";
  const char N = ' ',
    X = 'X',
    O = 'O';
  string turn = XT;
  int x_win = 0,
    o_win = 0,
    draw = 0;
  vector<vector<char>> board{{N, N, N},
                             {N, N, N},
                             {N, N, N}};

  drawBoard(board, turn);
  


  return 0;
}

void drawBoard(vector<vector<char>> board, string turn) {
  cout << "  1 2 3" << endl;
  cout << "a " << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
  cout << "b " << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
  cout << "c " << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
  cout << " " << turn << endl;
}

int checkWin(vector<vector<char>> board) {
  return 0;
}
