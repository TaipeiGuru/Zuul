#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include <map>
#include "room.h"

using namespace std;

room::room() {
  
}

void room::listExits() {
  map<char*, room*>::iterator iter;
  for(iter = roomExits.begin(); iter != roomExits.end(); iter++) {
    cout << it->first << endl; 
  }
} 

map<char*, room*>* room::getRoomExits() {
  return &roomExits; 
}

char* room::showDescription() {
  return description;
}

void room::listItems() {
  vector<item*>::iterator iter;
  for(iter = roomItems.begin(); iter != roomItems.end(); iter++) {
    cout << (*iter)->getItemType() << endl; 
  }
}

vector <item*>* room::getRoomItems() {
  return &roomItems; 
}

void room::dropItems(item* myItem) {
  roomItems.push_back(myItem);
}

void room::retrieveItems(item* myItem) {
  vector<item*>::iterator iter;
  for(iter = roomItems.begin(); iter != roomItems.end(); iter++) {
    if(strcmp((*iter)->getItemType(), myItem->getItemType()) == 0) {
      roomItems.erase(iter);
      return;
    }
  }
}

Room* room::getRoomByDirection(char* direction) {
  map<char*, room*>::iterator iter;
  for(iter = roomExits.begin(); iter != roomExits.end(); iter++) {
    if(strcmp(iter->first, direction) == 0) {
      return it->second; 
    }
  }
  return this;
}

void setRoom(int roomNum) {
  thisRoom = roomNum; 
}

int room::getRoom() {
  return thisRoom; 
}
