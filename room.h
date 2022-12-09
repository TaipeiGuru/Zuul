#include <iostream>
#include <cstring>

#ifndef ROOM_H
#define ROOM_H

using namespace std;

class Room {
public:
  Room();
  map<char*, Room*>* setExits();
  char* setDescription();
  void getItems();
  void listItems();
  void dropItems();
  vector<Item*>* getItems();
  map<char*, Room*>* getExits();
  void listExits();
  Room* getRoomByDirection(char* direction);
private:
  char description[300];
  vector<Item*> roomItems;
  map<char*, Room*>* roomExits;
};

#endif
