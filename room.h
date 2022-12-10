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
  map<char*, room*>* setExits();
  char* setDescription();
  void retrieveItems();
  void listItems();
  void dropItems();
  vector<item*>* getItems();
  map<char*, room*>* getExits();
  void listExits();
  room* getRoomByDirection(char* direction);
private:
  char description[300];
  vector<item*> roomItems;
  map<char*, room*>* roomExits;
};

#endif
