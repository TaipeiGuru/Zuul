#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

item::item() {
  
}

char* getItemType() {
  return itemType; 
}

int getItemID() {
  return itemID; 
}

void setItemID(int id) {
  itemID = id;
}
