#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Videogame.h"
#include "Music.h"
#include "Movie.h"

using namespace std;

vector<Media*> list;

void addVG();
void addMusic();
void addMovie();
void search();
void del();

int main() {
  bool quit = false;
  string input;

  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(1);
  
  while (!quit) {
    cout << "\nEnter a command" << endl;
    cin >> input;

    if (input == "ADD") {
      cout << "\nChoose a digital media you want to add:\n1) Video Game\n2) Music\n3) Movie" << endl;
      cin >> input;

      if (input == "1") {
	addVG();
      }
      else if (input == "2") {
	addMusic();
      }
      else if (input == "3") {
	addMovie();
      }
      else {
	cout << "Invalid command" << endl;
      }
    }
    else if (input == "SEARCH") {
      search();
    }
    else if (input == "DELETE") {
      del();
    }
    else if (input == "QUIT") {
      quit = true;
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
  
  return 0;
}

void addVG() {
  string title;
  int year;
  string publisher;
  float rating;
  
  cout << "\nTitle:" << endl;
  getline(cin, title);
  
  cout << "Year:" << endl;
  cin >> year;

  cout << "Publisher:" << endl;
  getline(cin, publisher);

  cout << "Rating;" << endl;
  cin >> rating;

  Media* nmedia = new Videogame(new string(title), year, new string(publisher), rating);
  list.push_back(nmedia);
  cout << "Video game added" << endl;
}

void addMusic() {
  string title;
  int year;
  string artist;
  int duration;
  string publisher;
  
  cout << "\nTitle:" << endl;
  getline(cin, title);
  
  cout << "Year:" << endl;
  cin >> year;

  cout << "Artist:" << endl;
  getline(cin, artist);

  cout << "Duration:" << endl;
  cin >> duration;
  
  cout << "Publisher:" << endl;
  getline(cin, publisher);

  Media* nmedia = new Music(new string(title), year, new string(artist), duration, new string(publisher));
  list.push_back(nmedia);
  cout << "Music added" << endl;
}

void addMovie() {
  string title;
  int year;
  string director;
  int duration;
  float rating;
  
  cout << "\nTitle:" << endl;
  getline(cin, title);
  
  cout << "Year:" << endl;
  cin >> year;

  cout << "Director:" << endl;
  getline(cin, director);

  cout << "Duration:" << endl;
  cin >> duration;
  
  cout << "Rating;" << endl;
  cin >> rating;

  Media* nmedia = new Movie(new string(title), year, new string(director), dureation, rating);
  list.push_back(nmedia);
  cout << "Movie added" << endl;
}

void search() {

}

void del() {

}
