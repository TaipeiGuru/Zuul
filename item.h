// Item class for Zuul
#include <iostream>
#include <cstring>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class item {
 public: 
  item();
  char* getItemType();
 private:
  // itemType serves as the item name, used when searching through item vectors
  char itemType[50];
};

#endif
