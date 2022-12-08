#include <iostream>
#include <cstring>

using namespace std;

class Room {
public:
  Room();
  setExits();
  setDescription();
  getItems();
  printItems();
  dropItems();
private:
  char description[200];
};
