/*
 * Project: Zuul
 * Author: Sungin Cho
 * Date: 11/1/20
 * Instructor: Jason Galbraith
 * Description: This is a program of a simple text-based adventure game
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>
#include <ctime>
#include "Room.h"

using namespace std;

//struct for items
struct Item {
  int index;
  char name[99];
};

// function prototypes
void prompt();
void setup();
void checkEvent();
void currentRoom();
void help();
void move();
void printInv(vector<Item*> items);
void drop();
void grab();
void useItem();

// constant variables
const char E = 'E';
const char W = 'W';
const char S = 'S';
const char N = 'N';

// global variables including the rooms
vector<Room*> list;
Room* cRoom;
vector<Item*> inventory;
vector<vector<Item*>> roomInv = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };
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
  // introduction message
  cout << "You wake up in a room with a bizarre pig statue. As you look around, you realize that you are in somekind of a dungeon." << endl;
  cout << "\nSuddenly an unfamiliar echoing voice inside your head says\n\"Light up the four torches hidden in the dungeon and the dragon shall take you home.\"" << endl;
  cout << "Strange as it might sound, you decided to follow what the voice was saying to escape from this dungeon." << endl;
  cout << "\nType 'help' if you need help." << endl;
  
  // resolve commands until game is finished
  while (!finish) {
    prompt();

    if (command == 'h') {
      help();
    }
    else if (command == 'm') {
      move();
    }
    else if (command == 'i') {
      cout << "Inventory:" << endl;
      printInv(inventory);
    }
    else if (command == 'd') {
      drop();
    }
    else if (command == 'g') {
      grab();
    }
    else if (command == 'u') {
      useItem();
    }
    else if (command == 'r') {
      currentRoom();
    }
    else if (command == 'q') {
      finish = true;
    }
    else {
      cout << "Invalid command." << endl;
    }
  }
  
  return 0;
}

// take an input and identify which command it is
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
  else if (strcmp(input, "grab") == 0) {
    command = 'g';
  }
  else if (strcmp(input, "drop") == 0) {
    command = 'd';
  }
  else if (strcmp(input, "item") == 0) {
    command = 'u';
  }
  else if (strcmp(input, "room") == 0) {
    command = 'r';
  }
  else if (strcmp(input, "quit") == 0) {
    command = 'q';
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

// game initial setup
void setup() {
  // randomize
  srand(time(nullptr));
  
  // no events encountered
  fill_n(event, 14, false);
  
  // set exits for every room
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

  // start in pig room
  cRoom = pig;
}

// check for any room event
void checkEvent() {
  int i = cRoom->getIndex();
	
  // resolve a room event if it hasn't been done so before
  if (i < 11 && i != 4 && i != 5) {
    if (!event[i]) {
      if (i == 0) {
	cout << "You found a key lying on the floor; A sheep is engraved on its handle. This might come in use later." << endl;
	cout << "<Sheep Key> is added to your inventory." << endl;
	Item* sheepKey = new Item();
	sheepKey->index = 0;
	strcpy(sheepKey->name, "Sheep Key");
	inventory.push_back(sheepKey);
	event[0] = true; 
      }
      else if (i == 1) {
	cout << "You found a piece of map lying on the floor. The left side of it is torn off but this is still probably useful." << endl;
	cout << "<Map 2> is added to your inventory." << endl;
	Item* map2 = new Item();
	map2->index = 1;
	strcpy(map2->name, "Map 2");
	inventory.push_back(map2);
	event[1] = true;
      }
      else if (i == 2) {
	cout << "As you look closer into it, you found a glowing scale in its mouth. Only animal you can think of with a scale this big is dragon." << endl;
	cout << "<Dragon Scale?> is added to your inventory." << endl;
	Item* dragonScale = new Item();
	dragonScale->index = 2;
	strcpy(dragonScale->name, "Dragon Scale?");
	inventory.push_back(dragonScale);
	event[2] = true;
      }
      else if (i == 3) {
	cout << "Next to it, you see a rabbit's foot. There's a tag on it that says\n\"This can take you to wherever you want but only if you are lucky enough.\"" << endl;
	cout << "<Rabbit's foot> is added to your inventory." << endl;
	Item* rabbitFoot = new Item();
	rabbitFoot->index = 3;
	strcpy(rabbitFoot->name, "Rabbit's Foot");
	inventory.push_back(rabbitFoot);
	event[3] = true;
      }
      else if (i == 6) {
	cout << "You found a piece of map lying on the floor. The right side of it is torn off but this is still probably useful." << endl;
	cout << "<Map 1> is added to your inventory." << endl;
	Item* map1 = new Item();
	map1->index = 4;
	strcpy(map1->name, "Map 1");
	inventory.push_back(map1);
	event[6] = true;
      }
      else if (i == 7) {
	cout << "You see a locked chest next to it. It looks like the only way to open it is to find the key." << endl;
      }
      else if (i == 8) {
	cout << "It's holding a key in its hand. The key has a chicken engraving on its handle. This might come in use later." << endl;
	cout << "<Chicken Key> is added to your inventory." << endl;
	Item* chickenKey = new Item();
	chickenKey->index = 6;
	strcpy(chickenKey->name, "Chicken Key");
	inventory.push_back(chickenKey);
	event[8] = true;
      }
      else if (i == 9) {
	cout << "You see a locked chest next to it. It looks like the only way to open it is to find the key." << endl;
      }
      else if (i == 10) {
	cout << "There's a bell attached to its collar. There's also a note next to it that says\n\"Ring the bell and you will always find yourself alongside the dog.\"" << endl;
	cout << "<Bell> is added to your inventory." << endl;
	Item* bell = new Item();
	bell->index = 8;
	strcpy(bell->name, "Bell");
	inventory.push_back(bell);
	event[10] = true;
      }
    }
    else {
      cout << "You don't see anything else that is particularly interesting..." << endl;
    }
  }
  else if (i == 4) {
    if (event[12] == true && event[13] == true && event[14] == true && event[15] == true) {
      cout << "The giant gateway above it is open but nothing is happening. Returning the missing scale of the dragon statue might do the job." << endl;
    }
    else {
      cout << "There's also a giant gateway above it but it's sealed shut. Lighting up all four torches might open it up." << endl;
    }
  }
  else if (i == 5) {
    cout << "You see a scripture next to it that says\n\"You shall find the path to your destination when you turn your back against it.\"\nThis could be an hint to navigating this dungeon..." << endl; 
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

// print current room information
void currentRoom() {
  cout << "You are now in a room with " << cRoom->getDescription() << endl;
  cout << "Items in the room:" << endl;
  printInv(roomInv[cRoom->getIndex()]);
  cout << endl;
  checkEvent();
}

// print out command words and hint
void help() {
  cout << "Commands:" << endl;
  cout << "move - This command will ask you for the direction you want to move and move you to the chosen direction" << endl;
  cout << "inventory - This command will print out the items in your possesion" << endl;
  cout << "drop - This command will ask you for the item you want to drop and drop the chosen item" << endl;
  cout << "grab - This command will ask you for the item you wnat to grab and grab the chosen item" << endl;
  cout << "item - This command will ask you for the item you want to use and use the chosen item (all items are reusable)" << endl;
  cout << "room - This command will describe the room you are currently in" << endl;
  cout << "quit - This command will end the game" << endl;
  cout << "\nHint: ";
  if (event[12] == true && event[13] == true && event[14] == true && event[15] == true) {
    cout << "All four torches are lighted up! Let's head to the dragon and return home!" << endl;
  }
  else {
    cout << "Find the four torches and a way to light them up." << endl;
  }
}

// move to a different room
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

// print items in the given inventory
void printInv(vector<Item*> items) {
  for (int i = 1; i <= items.size(); i++) {
    cout << i << ") " << items[i - 1]->name << endl;
  }
  if (items.size() == 0) {
    cout << "(No items)" << endl;
  }
}

// transfer an item from inventory to room
void drop() {
  cout << "Enter the item number of the item you want to drop:" << endl;
  printInv(inventory);
  prompt();
  if (isdigit(command)) {
    int n = (int)command - 48;
    int r = cRoom->getIndex();
    if (n <= inventory.size()) {
      roomInv[r].push_back(inventory[n - 1]);
      inventory.erase(inventory.begin() + (n - 1));
      cout << "Item dropped" << endl;
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}

// transfer an item from room to inventory
void grab() {
  cout << "Enter the item number of the item you want to grab:" << endl;
  int r = cRoom->getIndex();
  printInv(roomInv[r]);
  prompt();
  if (isdigit(command)) {
    int n = (int)command - 48;
    if (n <= roomInv[r].size()) {
      inventory.push_back(roomInv[r][n - 1]);
      roomInv[r].erase(roomInv[r].begin() + (n - 1));
      cout << "Item grabbed" << endl;
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}

// use an item in the inventory
void useItem() {
  cout << "Enter the item number of the item you want to use:" << endl;
  printInv(inventory);
  prompt();
  if (isdigit(command)) {
    int n = (int)command - 48;
    int r = cRoom->getIndex();
    if (n <= inventory.size()) {
      int i = inventory[n - 1]->index;

      if (i == 0) {
	if (r == 7 && event[7] == false) {
	  cout << "You unlocked the chest with the key and found a rope inside the chest!" << endl;
	  cout << "<Rope> is added to your inventory." << endl;
	  Item* rope = new Item();
	  rope->index = 5;
	  strcpy(rope->name, "Rope");
	  inventory.push_back(rope);
	  event[7] = true;
	}
	else if (r == 9 && event[9] == false) {
	  cout << "You tried to unlock the chest with the key but it doesn't seem to fit..." << endl;
	}
	else {
	  cout << "You can't use that here." << endl;
	}
      }
      else if (i == 1) {
	cout << "The map looks like this:" << endl;
	cout << " ________ ________ " << endl;
	cout << " )       |        |" << endl;
	cout << "(   I    | Tiger  |" << endl;
	cout << " )       |        |" << endl;
	cout << "(________|________|" << endl;
	cout << " )       |        |" << endl;
	cout << "( Dragon | Snake  |" << endl;
	cout << " )       |        |" << endl;
	cout << "(________|________|" << endl;
	cout << " )       |        |" << endl;
	cout << "( Monkey |  III   |" << endl;
	cout << " )       |        |" << endl;
	cout << "(________|________|" << endl;
	cout << " )       |        |" << endl;
	cout << "(  Dog   |  Pig   |" << endl;
	cout << " )       |        |" << endl;
	cout << "(________|________|" << endl;
      }
      else if (i == 2) {
	if (r == 4) {
	  if (event[12] == true && event[13] == true && event[14] == true && event[15] == true) {
	    finish = true;
	    cout << "As soon as you fit the dragon scale onto the dragon statue, the statue starts to rumble.\nYou quickly hop onto it and the statue eventually turns into a real dragon.\nThe dragon takes off, flying through the gateway, and takes you home while you're holding onto it as hard as you can to not fall off.\nAfter a few minute, you finally arrive back home and so this bizarre adventure comes to an end..." << endl;  
	  }
	  else {
	    cout << "The gateway isn't open yet. Maybe you should try fitting it after the gateway opens." << endl;
	  }
	}
	else {
	  cout << "You can't use that here." << endl;
	}
      }
      else if (i == 3) {
	int random = rand() % 16;
	for (int a = 0; a < 16; a++) {
	  if (list[a]->getIndex() == random) {
	    cRoom = list[a];
	  }
	}
	cout << "While holding the rabbit's foot, you closed your eyes and opened them after few seconds...\n" << endl;
	currentRoom();
      }
      else if (i == 4) {
	cout << "The map looks like this:" << endl;
	cout << " ________ ________ " << endl;
	cout << "|        |        )" << endl;
	cout << "| Mouse  |  Cow  ( " << endl;
	cout << "|        |        )" << endl;
	cout << "|________|_______( " << endl;
	cout << "|        |        )" << endl;
	cout << "|   II   | Rabbit( " << endl;
	cout << "|        |        )" << endl;
	cout << "|________|_______( " << endl;
	cout << "|        |        )" << endl;
	cout << "| Horse  | Sheep ( " << endl;
	cout << "|        |        )" << endl;
	cout << "|________|_______( " << endl;
	cout << "|        |        )" << endl;
	cout << "|Chicken |   IV  ( " << endl;
	cout << "|        |        )" << endl;
	cout << "|________|_______( " << endl;
      }
      else if (i == 5 || i == 7) {
	if (r > 11) {
	  bool hasRope = false;
	  bool hasMatch = false;
	  for (int a = 0; a < inventory.size(); a++) {
	    if (strcmp(inventory[a]->name, "Rope") == 0) {
	      hasRope = true;
	    }
	    else if (strcmp(inventory[a]->name, "Matchbox") == 0) {
	      hasMatch = true;
	    }
	  }
	  if (hasRope == true && hasMatch == true) {
	    cout << "You climbed up the torch with the rope and lighted it up using a match." << endl;
	    event[r] = true;
	  }
	  else if (hasMatch == false) {
	    cout << "You climbed up the torch with the rope but you don't have anything to light it up..." << endl;
	  }
	  else if (hasRope == false) {
	    cout << "You tried to light up the torch using a match but the torch is too high for you to reach..." << endl;
	  }
	}
	else {
	  cout << "You can't you that here." << endl;
	}
      }
      else if (i == 6) {
	if (r == 9 && event[9] == false) {
	  cout << "You unlocked the chest with the key and found a matchbox full of matches inside the chest!" << endl;
	  cout << "<Matchbox> is added to your inventory." << endl;
	  Item* matchbox = new Item();
	  matchbox->index = 7;
	  strcpy(matchbox->name, "Matchbox");
	  inventory.push_back(matchbox);
	  event[9] = true;
	}
	else if (r == 7 && event[7] == false) {
	  cout << "You tried to unlock the chest with the key but it doesn't seem to fit..." << endl;
	}
	else {
	  cout << "You can't use that here." << endl;
	}
      }
      else if (i == 8) {
	cRoom = dog;
	cout << "You closed your eyes and rang the bell. By the time you open your eyes, you realize that you are back in the room with the dog statue." << endl;
      }
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
  else {
    cout << "Invalid command" << endl;
  }
}
