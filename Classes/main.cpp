/*
 * Project: Classes
 * Author: Sungin Cho
 * Date: 10/19/20
 * Instructor: Jason Galbraith
 * Description: This is a program for managing a list of 3 types of digital medias
 */
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

// global variables
vector<Media*> list;
string dtitle;
int dyear;

//function prototypes
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

  // setting precision for ratings
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(1);
  
  while (!quit) {
    // prompt for a user command and resolve
    cout << "\nEnter a command" << endl;
    cin >> input;

    if (input == "ADD") {
      // prompt for the type of digital media
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

// Add a new Videogame to the list
void addVG() {
  string title;
  int year;
  string publisher;
  float rating;
  
  // prompt for the video game details
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

  // create new Videogame and add to the list
  Media* nmedia = new Videogame(new string(title), year, new string(publisher), rating);
  list.push_back(nmedia);
  cout << "Video game added" << endl;
}

// Add a new Music to the list
void addMusic() {
  string title;
  int year;
  string artist;
  int duration;
  string publisher;
  
  // prompt for the music details
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

  // create new Music and add to the list
  Media* nmedia = new Music(new string(title), year, new string(artist), duration, new string(publisher));
  list.push_back(nmedia);
  cout << "Music added" << endl;
}

// Add a new Movie to the list
void addMovie() {
  string title;
  int year;
  string director;
  int duration;
  float rating;
  
  // prompt for the movie details
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

  // create a new Movie and add to the list
  Media* nmedia = new Movie(new string(title), year, new string(director), duration, rating);
  list.push_back(nmedia);
  cout << "Movie added" << endl;
}

// search for digital media in the list with title or year
void search() {
  string input;
  bool nf = true;
  
  // prompt for search type
  cout << "\nSearch with:\n1) Title\n2) Year" << endl;
  cin >> input;
  
  if (input == "1") {
    // print all digital media with matching title
    cout << "\nEnter the title:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    
    for (int i = 0; i < list.size(); i++) {
      if (*(list.at(i)->getTitle()) == input) {
	print(list.at(i));
	nf = false;
      }
    }
	  
    // notify user if none of them matched
    if (nf) {
      cout << "There's no digital media with that title" << endl;
    }
  }
  else if (input == "2") {
    // print all digital media with matching year
    cout << "\nEnter the year:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    for (int i = 0; i < list.size(); i++) {
      if (to_string(list.at(i)->getYear()) == input) {
	print(list.at(i));
	nf = false;
      }
    }
	  
    // notify user if none of them matched
    if (nf) {
      cout << "There's no digital media from that year" << endl;
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}

// print out details of given digital media
void print(Media* media) {
  // check for the type and print its details
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

// search & delete digital media
void del() {
  string input;
  bool nf = true;
  
  // search for digital media to delete
  cout << "\nSearch with:\n1) Title\n2) Year" << endl;
  cin >> input;
  
  if (input == "1") {
    // search and print result
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
      // ask for confirmation
      cout << "\nDelete these items? [Y/N]" << endl;
      cin >> input;

      while (input != "Y" && input != "N") {
	cout << "Please answer with a \"Y\" or \"N\"" << endl;
	cin >> input;
      }
	    
      if (input == "Y") {
        // delete all digital media with matching title 
	list.erase(remove_if(list.begin(), list.end(), titleMatch), list.end());
	cout << "Items deleted" << endl;
      }
      else {
	// terminate deletion
	cout << "Deletion terminated" << endl;
      }
    }
  }
  else if (input == "2") {
    // search and print result
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
      // ask for confirmation
      cout << "\nDelete these items? [Y/N]" << endl;
      cin >> input;
      
      while (input != "Y" && input != "N") {
	cout << "Please answer with a \"Y\" or \"N\"" << endl;
	cin >> input;
      }
      if (input == "Y") {
	// delete all digital media with matching year
	list.erase(remove_if(list.begin(), list.end(), yearMatch), list.end());
	cout << "Items deleted" << endl;
      }
      else {
	// terminate deletion
	cout << "Deletion terminated" << endl;
      }
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}

// check for title match
bool titleMatch(Media* media) {
  return (*(media->getTitle()) == dtitle);
}

// check for year match
bool yearMatch(Media* media) {
  return (media->getYear() == dyear);
}
