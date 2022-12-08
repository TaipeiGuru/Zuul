#include <iostream>
#include <cstring>

using namespace std;

class room {
public:
  room();
  setExits();
  setDescription();
  getItems();
  printItems();
  dropItems();
private:
  char description[200];
};
