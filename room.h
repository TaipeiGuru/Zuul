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
  map<const char*, room*>* getRoomExits();
  char* showDescription();
  void retrieveItems(item* myItem);
  void listItems();
  void dropItems(item* myItem);
  vector<item*>* getRoomItems();
  void listExits();
  room* getRoomByDirection(char* direction);
  void setRoom(int roomNum);
  int getRoom();
private:
  int thisRoom;
  char description[300];
  vector<item*> roomItems;
  map<const char*, room*> roomExits;
};

#endif
