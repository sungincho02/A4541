#include <iostream>
#include <cstring>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include "Room.h"

using namespace std;

struct Item {
  int index;
  char name[20];
};

void createRooms();
void checkEvent();
void useItem();

const char E = 'E';
const char W = 'W';
const char S = 'S';
const char N = 'N';

vector<Room*> list;
Room* cRoom;

int main() {
  createRooms();
  cout << "You wake up in an empty room with a big hole in front of you." << endl;
  cout << "You hear an echoing voice inside your head saying \n\"Light up the four torches hidden in the dungeon and the dragon shall take you home. Dive down the hole when you are prepared.\"" << endl;
  cout << "Strange as it might sound, you decided to follow what the voice was saying to escape from this dungeon." << endl;
  cout << "Type 'help' if you need help." << endl;

  


  
  return 0;
}

void createRooms() {
  
  Room *start = new Room((char*)"a big hole in front of you. Let's follow what the voice said for now."),
    *mouse = new Room((char*)"a mouse statue."),
    *cow = new Room((char*)"a cow statue."),
    *tiger = new Room((char*)"a tiger statue."),
    *rabbit = new Room((char*)"a rabbit statue."),
    *dragon = new Room((char*)"a dragon statue. As you look closer into it, you notice that it's missing a single scale."),
    *snake = new Room((char*)"a snake statue."),
    *horse = new Room((char*)"a horse statue."),
    *sheep = new Room((char*)"a sheep statue."),
    *monkey = new Room((char*)"a monkey statue."),
    *chicken = new Room((char*)"a chicken statue."),
    *dog = new Room((char*)"a dog statue."),
    *pig = new Room((char*)"a pig statue. There's a hole in the ceiling in which you entered this dungeon."),
    *torch1 = new Room((char*)"a giant torch."),
    *torch2 = new Room((char*)"a giant torch."),
    *torch3 = new Room((char*)"a giant torch."),
    *torch4 = new Room((char*)"a giant torch.");

  start->setExit(N, pig);
  
  mouse->setExit(E, tiger);
  mouse->setExit(W, cow);
  mouse->setExit(S, chicken);
  mouse->setExit(N, torch2);

  cow->setExit(E, mouse);
  cow->setExit(W, torch1);
  cow->setExit(S, torch4);
  cow->setExit(N, rabbit);

  tiger->setExit(E, torch1);
  tiger->setExit(W, mouse);
  tiger->setExit(S, pig);
  tiger->setExit(N, snake);
  
  rabbit->setExit(E, torch2);
  rabbit->setExit(W, dragon);
  rabbit->setExit(S, cow);
  rabbit->setExit(N, sheep);
  
  dragon->setExit(E, rabbit);
  dragon->setExit(W, snake);
  dragon->setExit(S, torch1);
  dragon->setExit(N, monkey);
  
  snake->setExit(E, dragon);
  snake->setExit(W, torch2);
  snake->setExit(S, tiger);
  snake->setExit(N, torch3);
  
  horse->setExit(E, torch3);
  horse->setExit(W, sheep);
  horse->setExit(S, torch2);
  horse->setExit(N, chicken);

  sheep->setExit(E, horse);
  sheep->setExit(W, monkey);
  sheep->setExit(S, rabbit);
  sheep->setExit(N, torch4);

  monkey->setExit(E, sheep);
  monkey->setExit(W, torch3);
  monkey->setExit(S, dragon);
  monkey->setExit(N, dog);

  chicken->setExit(E, pig);
  chicken->setExit(W, torch4);
  chicken->setExit(S, horse);
  chicken->setExit(N, mouse);

  dog->setExit(E, torch4);
  dog->setExit(W, pig);
  dog->setExit(S, monkey);
  dog->setExit(N, torch1);

  pig->setExit(E, dog);
  pig->setExit(W, chicken);
  pig->setExit(S, torch3);
  pig->setExit(N, tiger);

  torch1->setExit(E, cow);
  torch1->setExit(W, tiger);
  torch1->setExit(S, dog);
  torch1->setExit(N, dragon);

  torch2->setExit(E, snake);
  torch2->setExit(W, rabbit);
  torch2->setExit(S, mouse);
  torch2->setExit(N, horse);

  torch3->setExit(E, monkey);
  torch3->setExit(W, horse);
  torch3->setExit(S, snake);
  torch3->setExit(N, pig);

  torch4->setExit(E, chicken);
  torch4->setExit(W, dog);
  torch4->setExit(S, sheep);
  torch4->setExit(N, cow);
		      
  cRoom = start;
}

void checkEvent() {

}

void useItem() {

}
