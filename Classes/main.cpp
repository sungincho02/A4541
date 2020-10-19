#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <typeinfo>
#include <algorithm>
#include "Videogame.h"
#include "Music.h"
#include "Movie.h"

using namespace std;

vector<Media*> list;
string dtitle;
int dyear;

void addVG();
void addMusic();
void addMovie();
void search();
void print(Media* media);
void del();
bool titleMatch(Media* media);
bool yearMatch(Media* media);

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
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, title);
  
  cout << "Year:" << endl;
  cin >> year;

  cout << "Publisher:" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, title);
  
  cout << "Year:" << endl;
  cin >> year;

  cout << "Artist:" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, artist);

  cout << "Duration:" << endl;
  cin >> duration;
  
  cout << "Publisher:" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, title);
  
  cout << "Year:" << endl;
  cin >> year;

  cout << "Director:" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, director);

  cout << "Duration:" << endl;
  cin >> duration;
  
  cout << "Rating;" << endl;
  cin >> rating;

  Media* nmedia = new Movie(new string(title), year, new string(director), duration, rating);
  list.push_back(nmedia);
  cout << "Movie added" << endl;
}

void search() {
  string input;
  bool nf = true;
  
  cout << "\nSearch with:\n1) Title\n2) Year" << endl;
  cin >> input;
  
  if (input == "1") {
    cout << "\nEnter the title:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    
    for (int i = 0; i < list.size(); i++) {
      if (*(list.at(i)->getTitle()) == input) {
	print(list.at(i));
	nf = false;
      }
    }
    if (nf) {
      cout << "There's no digital media with that title" << endl;
    }
  }
  else if (input == "2") {
    cout << "\nEnter the year:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    for (int i = 0; i < list.size(); i++) {
      if (to_string(list.at(i)->getYear()) == input) {
	print(list.at(i));
	nf = false;
      }
    }
    if (nf) {
      cout << "There's no digital media from that year" << endl;
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}

void print(Media* media) {
  if (typeid(*media) == typeid(Videogame)) {
    Videogame* ptr = (Videogame*)media;
    cout << "\nType: Video Game" << "\nTitle: " << *(ptr->getTitle()) << "\nYear: " << ptr->getYear() << "\nPublisher: " << *(ptr->getPublisher()) << "\nRating: " << ptr->getRating() << endl;
  }
  else if (typeid(*media) == typeid(Music)) {
    Music* ptr = (Music*)media;
    cout << "\nType: Music" << "\nTitle: " << *(ptr->getTitle()) << "\nYear: " << ptr->getYear() << "\nArtist: " << *(ptr->getArtist()) << "\nDuration: " << ptr->getDuration() << "m" << "\nPublisher: " << *(ptr->getPublisher()) << endl;
  }
  else if (typeid(*media) == typeid(Movie)) {
    Movie* ptr = (Movie*)media;
    cout << "\nType: Movie" << "\nTitle: " << *(ptr->getTitle()) << "\nYear: " << ptr->getYear() << "\nDirector: " << *(ptr->getDirector()) << "\nDuration: " << ptr->getDuration() << "m" << "\nRating: " << ptr->getRating() << endl;
  }
}

void del() {
  string input;
  bool nf = true;
  
  cout << "\nSearch with:\n1) Title\n2) Year" << endl;
  cin >> input;
  
  if (input == "1") {
    cout << "\nEnter the title:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    dtitle = input;
    
    for (int i = 0; i < list.size(); i++) {
      if (*(list.at(i)->getTitle()) == input) {
	print(list.at(i));
	nf = false;
      }
    }
    if (nf) {
      cout << "There's no digital media with that title" << endl;
    }
    else {
      cout << "\nDelete these items? [Y/N]" << endl;
      cin >> input;

      while (input != "Y" && input != "N") {
	cout << "Please answer with a \"Y\" or \"N\"" << endl;
	cin >> input;
      }
      if (input == "Y") {
	list.erase(remove_if(list.begin(), list.end(), titleMatch), list.end());
	cout << "Items deleted" << endl;
      }
      else {
	cout << "Deletion terminated" << endl;
      }
    }
  }
  else if (input == "2") {
    cout << "\nEnter the year:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    dyear = stoi(input);

    for (int i = 0; i < list.size(); i++) {
      if (to_string(list.at(i)->getYear()) == input) {
	print(list.at(i));
	nf = false;
      }
    }
    
    if (nf) {
      cout << "There's no digital media from that year" << endl;
    }
    else {
      cout << "\nDelete these items? [Y/N]" << endl;
      cin >> input;
      
      while (input != "Y" && input != "N") {
	cout << "Please answer with a \"Y\" or \"N\"" << endl;
	cin >> input;
      }
      if (input == "Y") {
	list.erase(remove_if(list.begin(), list.end(), yearMatch), list.end());
	cout << "Items deleted" << endl;
      }
      else {
	cout << "Deletion terminated" << endl;
      }
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}

bool titleMatch(Media* media) {
  return (*(media->getTitle()) == dtitle);
}

bool yearMatch(Media* media) {
  return (media->getYear() == dyear);
}
