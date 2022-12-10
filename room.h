#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "item.h"

#ifndef ROOM_H
#define ROOM_H

using namespace std;

class room {
public:
  room();
  map<char*, room*>* getRoomExits();
  char* showDescription();
  void retrieveItems();
  void listItems();
  void dropItems();
  vector<item*>* getRoomItems();
  void listExits();
  room* getRoomByDirection(char* direction);
  int setRoom();
  int getRoom();
private:
  int thisRoom;
  char description[300];
  vector<item*> roomItems;
  map<char*, room*>* roomExits;
};

#endif
