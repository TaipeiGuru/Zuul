// Item CPP file for Zuul
#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

item::item() {
  
}

// Returns itemType (aka name)
char* item::getItemType() {
  return itemType; 
}

