#include <iostream>
#include <cstring>

#infdef ITEM_H
#define ITEM_H

using namespace std;

class item {
 public: 
  item();
  char* getItemType();
 private:
  char itemType[50];
};

#endif
