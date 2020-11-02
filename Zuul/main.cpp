#include <iostream>
#include <cstring>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <algorithm>
#include "Room.h"

using namespace std;

struct Item {
  int index;
  char name[99];
};

void prompt();
void setup();
void checkEvent();
void currentRoom();
void help();
void move();
void printInv();
void useItem();

const char E = 'E';
const char W = 'W';
const char S = 'S';
const char N = 'N';

vector<Room*> list;
Room* cRoom;
vector<Item*> inventory;
char command;
bool event[16];
bool finish = false;
Room *mouse = new Room(0, (char*)"a mouse statue."),
  *cow = new Room(1, (char*)"a cow statue."),
  *tiger = new Room(2, (char*)"a tiger statue."),
  *rabbit = new Room(3, (char*)"a rabbit statue."),
  *dragon = new Room(4, (char*)"a dragon statue. As you look closer into it, you notice that it's missing a single scale."),
  *snake = new Room(5, (char*)"a snake statue."),
  *horse = new Room(6, (char*)"a horse statue."),
  *sheep = new Room(7, (char*)"a sheep statue."),
  *monkey = new Room(8, (char*)"a monkey statue."),
  *chicken = new Room(9, (char*)"a chicken statue."),
  *dog = new Room(10, (char*)"a dog statue."),
  *pig = new Room(11, (char*)"a pig statue. This is where you woke up."),
  *torch1 = new Room(12, (char*)"a giant torch. Roman numeral \"I\" is written on it."),
  *torch2 = new Room(13, (char*)"a giant torch. Roman numeral \"II\" is written on it."),
  *torch3 = new Room(14, (char*)"a giant torch. Roman numeral \"III\" is written on it."),
  *torch4 = new Room(15, (char*)"a giant torch. Roman numeral \"IV\" is written on it.");

int main() {
  setup();
  cout << "You wake up in a room with a bizzare pig statue. As you look around, you realize that you are in somekind of a dungeon." << endl;
  cout << "\nSuddenly an unfamiliar echoing voice inside your head says\n\"Light up the four torches hidden in the dungeon and the dragon shall take you home.\"" << endl;
  cout << "Strange as it might sound, you decided to follow what the voice was saying to escape from this dungeon." << endl;
  cout << "\nType 'help' if you need help." << endl;
  
  while (!finish) {
    prompt();

    if (command == 'h') {
      help();
    }
    else if (command == 'm') {
      move();
    }
    else if (command == 'i') {
      printInv();
    }
    else if (command == 'u') {
      useItem();
    }
    else if (command == 'r') {
      currentRoom();
    }
    else {
      cout << "Invalid command." << endl;
    }
  }
  
  return 0;
}

void prompt() {
  char input[99];
  cout << "\n> ";
  cin.get(input, 99);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (strcmp(input, "help") == 0) {
    command = 'h';
  }
  else if (strcmp(input, "move") == 0) {
    command = 'm';
  }
  else if (strcmp(input, "inventory") == 0) {
    command = 'i';
  }
  else if (strcmp(input, "item") == 0) {
    command = 'u';
  }
  else if (strcmp(input, "room") == 0) {
    command = 'r';
  }
  else if (strcmp(input, "E") == 0 || strcmp(input, "W") == 0 || strcmp(input, "S") == 0 || strcmp(input, "N") == 0) {
    command = input[0];
  }
  else if (isdigit(input[0]) && input[0] != 0 && input[1] == '\0') {
    command = input[0];
  }
  else {
    command == '0';
  }
  cout << endl;
}

void setup() {
  fill_n(event, 14, false);
  
  mouse->setExit(E, tiger);
  mouse->setExit(W, cow);
  mouse->setExit(S, chicken);
  mouse->setExit(N, torch2);
  list.push_back(mouse);
  
  cow->setExit(E, mouse);
  cow->setExit(W, torch1);
  cow->setExit(S, torch4);
  cow->setExit(N, rabbit);
  list.push_back(cow);

  tiger->setExit(E, torch1);
  tiger->setExit(W, mouse);
  tiger->setExit(S, pig);
  tiger->setExit(N, snake);
  list.push_back(tiger);
  
  rabbit->setExit(E, torch2);
  rabbit->setExit(W, dragon);
  rabbit->setExit(S, cow);
  rabbit->setExit(N, sheep);
  list.push_back(rabbit);
  
  dragon->setExit(E, rabbit);
  dragon->setExit(W, snake);
  dragon->setExit(S, torch1);
  dragon->setExit(N, monkey);
  list.push_back(dragon);
  
  snake->setExit(E, dragon);
  snake->setExit(W, torch2);
  snake->setExit(S, tiger);
  snake->setExit(N, torch3);
  list.push_back(snake);
  
  horse->setExit(E, torch3);
  horse->setExit(W, sheep);
  horse->setExit(S, torch2);
  horse->setExit(N, chicken);
  list.push_back(horse);

  sheep->setExit(E, horse);
  sheep->setExit(W, monkey);
  sheep->setExit(S, rabbit);
  sheep->setExit(N, torch4);
  list.push_back(sheep);
  
  monkey->setExit(E, sheep);
  monkey->setExit(W, torch3);
  monkey->setExit(S, dragon);
  monkey->setExit(N, dog);
  list.push_back(monkey);
  
  chicken->setExit(E, pig);
  chicken->setExit(W, torch4);
  chicken->setExit(S, horse);
  chicken->setExit(N, mouse);
  list.push_back(chicken);
  
  dog->setExit(E, torch4);
  dog->setExit(W, pig);
  dog->setExit(S, monkey);
  dog->setExit(N, torch1);
  list.push_back(dog);
  
  pig->setExit(E, dog);
  pig->setExit(W, chicken);
  pig->setExit(S, torch3);
  pig->setExit(N, tiger);
  list.push_back(pig);
  
  torch1->setExit(E, cow);
  torch1->setExit(W, tiger);
  torch1->setExit(S, dog);
  torch1->setExit(N, dragon);
  list.push_back(torch1);
  
  torch2->setExit(E, snake);
  torch2->setExit(W, rabbit);
  torch2->setExit(S, mouse);
  torch2->setExit(N, horse);
  list.push_back(torch2);
  
  torch3->setExit(E, monkey);
  torch3->setExit(W, horse);
  torch3->setExit(S, snake);
  torch3->setExit(N, pig);
  list.push_back(torch3);
  
  torch4->setExit(E, chicken);
  torch4->setExit(W, dog);
  torch4->setExit(S, sheep);
  torch4->setExit(N, cow);
  list.push_back(torch4);

  cRoom = pig;
}

void checkEvent() {
  int i = cRoom->getIndex();
  if (i < 11 && i != 4 && i != 5) {
    if (!event[i]) {
      if (i == 0) {
	cout << "You found a key lying on the floor; A sheep is engraved on its handle. This might come in use later." << endl;
	cout << "<Sheep Key> is added to your inventory." << endl;
	//add to inv
	event[0] = true; 
      }
      else if (i == 1) {
	cout << "You found a piece of map lying on the floor. The left side of it is torn off but this is still probably useful." << endl;
	cout << "<Map 2> is added to your inventory." << endl;
	//add to inv
	event[1] = true;
      }
      else if (i == 2) {
	cout << "As you look closer into it, you found a glowing scale in its mouth. Only animal you can think of with a scale this big is dragon." << endl;
	cout << "<Dragon Scale?> is added to your inventory." << endl;
	//add to inv
	event[2] = true;
      }
      else if (i == 3) {
	cout << "Next to it, you see a rabbit's foot. There's a tag on it that says\n\"This can take you to wherever you want but only if you are lucky enough.\"" << endl;
	cout << "<Rabbit's foot> is added to your inventory." << endl;
	//add to inv
	event[3] = true;
      }
      else if (i == 6) {
	cout << "You found a piece of map lying on the floor. The right side of it is torn off but this is still probably useful." << endl;
	cout << "<Map 1> is added to your inventory." << endl;
	//add to inv
	event[1] = true;
      }
      else if (i == 7) {
	cout << "You see a locked chest next to it. It looks like the only way to open it is to find the key." << endl;
      }
      else if (i == 8) {
	cout << "It's holding a key in its hand. The key has a chicken engraving on its handle. This might come in use later." << endl;
	cout << "<Chicken Key> is added to your inventory." << endl;
	//add to inv
	event[7] = true;
      }
      else if (i == 9) {
	cout << "You see a locked chest next to it. It looks like the only way to open it is to find the key." << endl;
      }
      else if (i == 10) {
	cout << "There's a bell attached to its collar. There's also a note next to it that says\n\"Ring the bell and you will always find yourself alongside the dog.\"" << endl;
	cout << "<Bell> is added to your inventory." << endl;
	//add to inv
	event[10] = true;
      }
    }
    else {
      cout << "You don't see anything else that is particularly interesting..." << endl;
    }
  }
  else if (i == 4) {
    if (event[4]) {
      cout << "The giant gateway above it is open but nothing is happening. Finding the missing scale of the dragon statue might do the job." << endl;
    }
    else {
      cout << "There's also a giant gateway above it but it's sealed shut. Lighting up all four torches might open it up." << endl;
    }
  }
  else if (i == 5) {
    cout << "You see a scripture next to it that says\n\nYou shall find the path to your destination when you turn your back against it.\"\nThis could be an hint to navigating this dungeon..." << endl; 
  }
  else if (i > 11) {
    if (event[i]) {
      cout << "This torch is already lighted up." << endl;
    }
    else {
      cout << "In order to climb up the torch and light it up, you'll probably need a rope and a tool to start a fire. You should be able to find them somewhere in this dungeon." << endl;
    }
  }
}

void currentRoom() {
  cout << "You are now in a room with " << cRoom->getDescription() << endl;
  checkEvent();
}

void help() {
  cout << "Commands:" << endl;
  cout << "move - This command will ask you for the direction you want to move and move you to the chosen direction" << endl;
  cout << "inventory - This command will print out the items in your possesion" << endl;
  cout << "item - This command will ask you for the item you want to use and use the chosen item (all items are reusable)" << endl;
  cout << "room - This command will describe the room you are currently in" << endl;
  cout << "\nHint: ";
  if (event[12] == true && event[13] == true && event[14] == true && event[15] == true) {
    cout << "All four torches are lighted up! Let's head to the dragon and return home!" << endl;
  }
  else {
    cout << "Find the four torches and a way to light them up." << endl;
  }
}

void move() {
  cRoom->printExit();
  prompt();
  if (command == N || command == E || command == W || command == S) {
    cRoom = cRoom->getNeighbor(command);
    currentRoom();
  }
  else {
    cout << "Invalid command." << endl;
  }
}

void printInv() {
  
}

void useItem() {

}
