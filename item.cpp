#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

item::item() {
  
}

char* item::getItemType() {
  return itemType; 
}

int item::getItemID() {
  return itemID; 
}

void item::setItemID(int id) {
  itemID = id;
}
