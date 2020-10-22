/*
 * Project: Classes
 * Author: Sungin Cho
 * Date: 10/19/20
 * Instructor: Jason Galbraith
 * Description: This is a program for managing a list of 3 types of digital media
 */
#include <iostream>
#include <cstring>
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
char dtitle[99];
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
  char input[99];

  // setting precision for ratings
  cout.setf(ios::fixed, ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(1);
  
  while (!quit) {
    // prompt for a user command and resolve
    cout << "\nEnter a command" << endl;
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (strcmp(input, "ADD") == 0) {
      // prompt for the type of digital media
      cout << "\nChoose a digital media you want to add:\n1) Video Game\n2) Music\n3) Movie" << endl;
      cin.get(input, 99);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      if (strcmp(input, "1") == 0) {
	addVG();
      }
      else if (strcmp(input, "2") == 0) {
	addMusic();
      }
      else if (strcmp(input, "3") == 0) {
	addMovie();
      }
      else {
	cout << "Invalid command" << endl;
      }
    }
    else if (strcmp(input, "SEARCH") == 0) {
      search();
    }
    else if (strcmp(input, "DELETE") == 0) {
      del();
    }
    else if (strcmp(input, "QUIT") == 0) {
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
  char title[99];
  int year;
  char publisher[99];
  float rating;
  
  // prompt for the video game details
  cout << "\nTitle:" << endl;
  cin.get(title, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Year:" << endl;
  cin >> year;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Publisher:" << endl;
  cin.get(publisher, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Rating;" << endl;
  cin >> rating;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // create new Videogame and add to the list
  Media* nmedia = new Videogame(title, year, publisher, rating);
  list.push_back(nmedia);
  cout << "Video game added" << endl;
}

// Add a new Music to the list
void addMusic() {
  char title[99];
  int year;
  char artist[99];
  int duration;
  char publisher[99];
  
  // prompt for the music details
  cout << "\nTitle:" << endl;
  cin.get(title, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Year:" << endl;
  cin >> year;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Artist:" << endl;
  cin.get(artist, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Duration:" << endl;
  cin >> duration;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Publisher:" << endl;
  cin.get(publisher, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // create new Music and add to the list
  Media* nmedia = new Music(title, year, artist, duration, publisher);
  list.push_back(nmedia);
  cout << "Music added" << endl;
}

// Add a new Movie to the list
void addMovie() {
  char title[99];
  int year;
  char director[99];
  int duration;
  float rating;
  
  // prompt for the movie details
  cout << "\nTitle:" << endl;
  cin.get(title, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Year:" << endl;
  cin >> year;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Director:" << endl;
  cin.get(director, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Duration:" << endl;
  cin >> duration;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Rating;" << endl;
  cin >> rating;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // create a new Movie and add to the list
  Media* nmedia = new Movie(title, year, director, duration, rating);
  list.push_back(nmedia);
  cout << "Movie added" << endl;
}

// search for digital media in the list with title or year
void search() {
  char input[99];
  bool nf = true;
  
  // prompt for search type
  cout << "\nSearch with:\n1) Title\n2) Year" << endl;
  cin.get(input, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  if (strcmp(input, "1") == 0) {
    // print all digital media with matching title
    cout << "\nEnter the title:" << endl;
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for (int i = 0; i < list.size(); i++) {
      if (strcmp(list.at(i)->getTitle(), input) == 0) {
	print(list.at(i));
	nf = false;
      }
    }
	  
    // notify user if none of them matched
    if (nf) {
      cout << "There's no digital media with that title" << endl;
    }
  }
  else if (strcmp(input, "2") == 0) {
    int syear;

    // print all digital media with matching year
    cout << "\nEnter the year:" << endl;
    cin >> syear;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < list.size(); i++) {
      if (list.at(i)->getYear() == syear) {
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
    cout << "\nType: Video Game" << "\nTitle: " << ptr->getTitle() << "\nYear: " << ptr->getYear() << "\nPublisher: " << ptr->getPublisher() << "\nRating: " << ptr->getRating() << endl;
  }
  else if (typeid(*media) == typeid(Music)) {
    Music* ptr = (Music*)media;
    cout << "\nType: Music" << "\nTitle: " << ptr->getTitle() << "\nYear: " << ptr->getYear() << "\nArtist: " << ptr->getArtist() << "\nDuration: " << ptr->getDuration() << "m" << "\nPublisher: " << ptr->getPublisher() << endl;
  }
  else if (typeid(*media) == typeid(Movie)) {
    Movie* ptr = (Movie*)media;
    cout << "\nType: Movie" << "\nTitle: " << ptr->getTitle() << "\nYear: " << ptr->getYear() << "\nDirector: " << ptr->getDirector() << "\nDuration: " << ptr->getDuration() << "m" << "\nRating: " << ptr->getRating() << endl;
  }
}

// search & delete digital media
void del() {
  char input[99];
  bool nf = true;
  
  // search for digital media to delete
  cout << "\nSearch with:\n1) Title\n2) Year" << endl;
  cin.get(input, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  if (strcmp(input, "1") == 0) {
    // search and print result
    cout << "\nEnter the title:" << endl;
    cin.get(input, 99);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    strcpy(dtitle, input);
    
    for (int i = 0; i < list.size(); i++) {
      if (strcmp(list.at(i)->getTitle(), input) == 0) {
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
      cin.get(input, 99);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      while (strcmp(input, "Y") != 0 && strcmp(input, "N") != 0) {
	cout << "Please answer with a \"Y\" or \"N\"" << endl;
	cin.get(input, 99);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
	    
      if (strcmp(input, "Y") == 0) {
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
  else if (strcmp(input, "2") == 0) {
    int syear;
	  
    // search and print result
    cout << "\nEnter the year:" << endl;
    cin >> syear;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    dyear = syear;

    for (int i = 0; i < list.size(); i++) {
      if (list.at(i)->getYear() == syear) {
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
      cin.get(input, 99);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      while (strcmp(input, "Y") != 0 && strcmp(input, "N") != 0) {
	cout << "Please answer with a \"Y\" or \"N\"" << endl;
	cin.get(input, 99);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
	    
      if (strcmp(input, "Y") == 0) {
        // delete all digital media with matching title 
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
  return (media->getTitle() == dtitle);
}

// check for year match
bool yearMatch(Media* media) {
  return (media->getYear() == dyear);
}
