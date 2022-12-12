#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include <map>
#include "room.h"

using namespace std;

room::room() {
  roomItems = new vector<item*>();
}

void room::listExits() {
  map<const char*, room*>::iterator iter;
  for(iter = roomExits.begin(); iter != roomExits.end(); iter++) {
    cout << iter->first << endl; 
  }
} 

map<const char*, room*>* room::getRoomExits() {
  return &roomExits; 
}

char* room::showDescription() {
  return description;
}

void room::listItems() {
  vector<item*>::iterator iter;
  if(roomItems->size() == 0) {
    cout << "No items in this room." << endl;
  } else {
    for(iter = roomItems->begin(); iter != roomItems->end(); iter++) {
      cout << (*iter)->getItemType() << endl;
    }
  }
}

vector<item*>* room::getRoomItems() {
  return roomItems; 
}

void room::dropItems(item* myItem) {
  roomItems->push_back(myItem);
}

void room::retrieveItems(item* myItem) {
  vector<item*>::iterator iter;
  for(iter = roomItems->begin(); iter != roomItems->end(); iter++) {
    if(strcmp((*iter)->getItemType(), myItem->getItemType()) == 0) {
      roomItems->erase(iter);
      return;
    }
  }
}

room* room::getRoomByDirection(const char* direction) {
  map<const char*, room*>::iterator iter;
  for(iter = roomExits.begin(); iter != roomExits.end(); iter++) {
    if(strcmp(iter->first, direction) == 0) {
      return iter->second; 
    }
  }
  return this;
}

void room::setRoom(int roomNum) {
  thisRoom = roomNum; 
}

int room::getRoom() {
  return thisRoom; 
}
