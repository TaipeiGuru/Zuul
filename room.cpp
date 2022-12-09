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

char* room::showDescription() {
  return description;
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

vector<item*>* 

void room::
