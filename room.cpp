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
  for(iter = exits.begin(); iter != exits.end(); iter++) {
    cout << it->first << endl; 
  }
} 

map<char*, room*>* room::getRoomExits() {
  return &exits; 
}

char* room::showDescription() {
  return description;
}

void room::listItems() {
  vector<item*>::iterator iter;
  for(iter = items.begin(); iter != items.end(); iter++) {
    cout << (*iter)->getItemType() << endl; 
  }
}

vector <item*>* room::getItems() {
  return &items; 
}

void room::dropItems(item* myItem) {
  items.push_back(myItem);
}

void room::retrieveItems(item* myItem) {
  vector<item*>::iterator iter;
  for(iter = items.begin(); iter != items.end(); iter++) {
    if(strcmp((*iter)->getItemType(), myItem->getItemType()) == 0) {
      items.erase(iter);
      return;
    }
  }
}

Room* room::getRoomByDirection(char* direction) {
  map<char*, room*>::iterator iter;
  for(iter = exits.begin(); iter != exits.end(); iter++) {
    if(strcmp(iter->first, direction) == 0) {
      return it->second; 
    }
  }
  return this;
}
