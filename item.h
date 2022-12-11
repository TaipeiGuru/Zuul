#include <iostream>
#include <cstring>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class item {
 public: 
  item();
  char* getItemType();
  int getItemID();
  void setItemID(int id);
 private:
  char itemType[50];
  int itemID;
};

#endif
