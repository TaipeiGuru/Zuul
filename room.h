// Room class for zuul
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "item.h"

// Header guard
#ifndef ROOM_H
#define ROOM_H

using namespace std;

class room {
public:
  room();
  // Using map to designate exits for each room
  map<const char*, room*>* getRoomExits();
  char* showDescription();
  void retrieveItems(item* myItem);
  void listItems();
  void dropItems(item* myItem);
  // Returns vector pointer of item pointers (items in that particular room)
  vector<item*>* getRoomItems();
  void listExits();
  room* getRoomByDirection(const char* direction);
  // Getter and setters for room values
  void setRoom(int roomNum);
  int getRoom();
private:
  // Current room tracker
  int thisRoom;
  // Room name and description
  char description[300];
  // Items in the room
  vector<item*>* roomItems;
  // Exits for the room
  map<const char*, room*> roomExits;
};

#endif
