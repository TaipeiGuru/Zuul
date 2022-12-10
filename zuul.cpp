#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <map>
#include <iterator>
#include "room.h"
#include "item.h"

/* This is the game of Zuul, a text-based adventure game that focuses on the user finding
 * certain items in the rooms of a castle and making it out safely. It was initially created 
 * by Michael Kolling and David J. Barnes, and was modified by Jason Randolph. Last edits were 
 * made 12/2/22. */

void createRooms(vector<room*>* rooms, vector<item*> roomItems, vector<char*> inventory);
void printWelcome();
void getItems(vector<char*>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom);
void dropItems(vector<char*>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom);

/**
* Create the game and initialise its internal map.
*/

// Main method
int main() {
  vector<room*> rooms;
	vector<item*> roomItems;
  vector<char*> inventory;
  int thisRoom = 0;
  createRooms(vector<room*>* rooms, vector<item*> roomItems, vector<char*> inventory);
	printWelcome();
	char input[10];

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the game is over.

	bool finished = false;
	while (finished == false) {
		cout << "Your commands are \"go\", \"quit\", \"inventory\", \"get\", \"drop\", and \"help\"." << endl; 
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		if (commandWord.equals("go")) {
			cout << "Which direction do you want to go? Your options are:" << endl;
			getCurrentRoom()->listExits();
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			thisRoom = goRoom(rooms, input, thisRoom);
		} else if (commandWord.equals("quit")) {
			cout << "Thank you for playing. Good bye." << endl;
			finished = true;
		} else if (commandWord.equals("inventory")) {
			printInventory();
		} else if (commandWord.equals("get")) {
      getItems(inventory, rooms, roomItems, thisRoom);
		} else if (commandWord.equals("drop")) {
			dropItems(inventory, rooms, roomItems, thisRoom);
		}
	}
}

int goRoom(vector<Room*> rooms, char* direction, int thisRoom) {
  map<Room*>::iterator iter;
  for(iter = rooms.begin(); iter != rooms.end(); iter++) {
    if(strcmp(thisRoom, (*iter)->getRoom()) == 0) {
      cout << "You are now " << (*iter)->showDescription() << endl;
      cout << "Items in the room: " << endl;
      cout << (*iter)->listItems() << endl;
      room newRoom = (*iter)->getRoomByDirection(direction);
      return newRoom->getRoom();
    }
  }
  delete direction;
}

// Create all the rooms and link their exits together.
void createRooms(vector<room*>* rooms, vector<item*>* roomItems, vector<char*>* inventory) {
	
	// create the rooms and their descriptions 
	Room* Outside = new Room();
	strcpy(Outside->getDescription(), "outside the entrance to the castle");
	Outside->getRoomExits()->insert(pair<char*, Room*>("east", EntryHall));
	Outside->setRoom(1);
	rooms->push_back(Outside);
	
	Room* EntryHall = new Room();
	strcpy(EntryHall->setDescription(), "in the entry hall of the castle. Are those guards carrying swords?");
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("east", Courtyard));
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("west", Outside));
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("north", NorthCorridor));
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("south", SouthCorridor));
	EntryHall->setRoom(2);
	rooms->push_back(EntryHall);
	
	Room* NorthCorridor = new Room();
	strcpy(NorthCorridor->setDescription(), "in a northern corridor connecting the entry hall to other parts of the castle");
	NorthCorridor->getRoomExits()->insert(pair<char*, Room*>("south", EntryHall));
	NorthCorridor->getRoomExits()->insert(pair<char*, Room*>("east", DiningHall));
	NorthCorridor->setRoom(3);
	rooms->push_back(NorthCorridor);
	
	Room* SouthCorridor = new Room();
	strcpy(SouthCorridor->setDescription(), "in a southern corridor connecting the entry hall to other parts of the castle");
	SouthCorridor->getRoomExits()->insert(pair<char*, Room*>("north", EntryHall));
	SouthCorridor->getRoomExits()->insert(pair<char*, Room*>("east", Chapel));
	SouthCorridor->setRoom(4);
	rooms->push_back(SouthCorridor);
		
	Room* DiningHall = new Room();
	strcpy(DiningHall->setDescription(), "in the Dining Hall, a room where food is served. Yum, I do love roast pig");
	DiningHall->getRoomExits()->insert(pair<char*, Room*>("west", NorthCorridor));
	DiningHall->getRoomExits()->insert(pair<char*, Room*>("east", ServantQuarters));
	DiningHall->setRoom(5);
	rooms->push_back(DiningHall);
		
	Room* Courtyard = new Room();
	strcpy(Courtyard->setDescription(), "in the Courtyard, an open-air area in the middle of the castle");
	Courtyard->getRoomExits()->insert(pair<char*, Room*>("west", EntryHall));
	Courtyard->getRoomExits()->insert(pair<char*, Room*>("east", RoyalHall));
	Courtyard->setRoom(6);
	rooms->push_back(Courtyard);
		
	Room* Chapel = new Room();
	strcpy(Chapel->setDescription(), "in the Chapel, the religious center of the castle (also hosts knighting ceremonies");
	Chapel->getRoomExits()->insert(pair<char*, Room*>("east", LivingQuarters));
	Chapel->getRoomExits()->insert(pair<char*, Room*>("west", SouthCorridor));
	Chapel->getRoomExits()->insert(pair<char*, Room*>("south", Watchtower));
	Chapel->setRoom(7);
	rooms->push_back(Chapel);
		
	Room* Watchtower = new Room();
	strcpy(Watchtower->setDescription(), "in the watchtower, which also doubles as a guardpost. Takes a few minutes to get up the 154 steps");
	Watchtower->getRoomExits()->insert(pair<char*, Room*>("north", Chapel));
	Watchtower->setRoom(8);
	rooms->push_back(Watchtower);
		
	Room* Parlor = new Room();
	strcpy(Parlor->setDescription(), "in the Parlor, a communal gathering area for the inhabitants of the castle");
	Parlor->getRoomExits()->insert(pair<char*, Room*>("south", ServantQuarters));
	Parlor->setRoom(9);
	rooms->push_back(Parlor);
		
	Room* ServantQuarters = new Room();
	strcpy(ServantQuarters->setDescription(), "in the Servant Quarters, the place where the servants live");
	ServantQuarters->getRoomExits()->insert(pair<char*, Room*>("west", DiningHall));
	ServantQuarters->getRoomExits()->insert(pair<char*, Room*>("south", Kitchen));
	ServantQuarters->getRoomExits()->insert(pair<char*, Room*>("north", Parlor));
	ServantQuarters->setRoom(10);
	rooms->push_back(ServantQuarters);
		
	Room* Kitchen = new Room();
	strcpy(Kitchen->setDescription(), "in the Kitchen. You can hear all sorts of noises down here...");
	Kitchen->getRoomExits()->insert(pair<char*, Room*>("south", RoyalHall));
	Kitchen->getRoomExits()->insert(pair<char*, Room*>("north", ServantQuarters));
	Kitchen->setRoom(11);
	rooms->push_back(Kitchen);
		
	Room* RoyalHall = new Room();
	strcpy(RoyalHall->setDescription(), "in the Royal Hall, where the king greets his subjects. What a pretty throne!");
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("east", Portico));
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("west", Courtyard));
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("north", Kitchen));
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("south", Library));
	RoyalHall->setRoom(12);
	rooms->push_back(RoyalHall);
	
	Room* Library = new Room();
	strcpy(Library->setDescription(), "in the Library, a room where all the books and manuscripts are kept");
	Library->getRoomExits()->insert(pair<char*, Room*>("south", LivingQuarters));
	Library->getRoomExits()->insert(pair<char*, Room*>("north", RoyalHall));
	Library->setRoom(13);
	rooms->push_back(Library);
		
	Room* LivingQuarters = new Room();
	strcpy(LivingQuarters->setDescription(), "in the Living Quarters, a place where the king and every other non-servant stays in the castle");
	LivingQuarters->getRoomExits()->insert(pair<char*, Room*>("north", Library));
	LivingQuarters->getRoomExits()->insert(pair<char*, Room*>("west", Chapel));
	LivingQuarters->setRoom(4);
	rooms->push_back(LivingQuarters);
		
	Room* Portico = new Room();
	strcpy(Portico->setDescription(), "on the Portico, which also serves as the back exit to the castle. What does that lever do?");
	Portico->getRoomExits()->insert(pair<char*, Room*>("north", SecretPassage));
	Portico->getRoomExits()->insert(pair<char*, Room*>("west", RoyalHall));
	Portico->setRoom(15);
	rooms->push_back(Portico);
		
	Room* SecretPassage = new Room();
	strcpy(SecretPassage->setDescription(), "in a chilly tunnel lit by torches. This looks an awful lot like a secret passage...");
	SecretPassage->getRoomExits()->insert(pair<char*, Room*>("south", Portico));
	SecretPassage->setRoom(16);
	rooms->push_back(SecretPassage);
		
	// Initializing and assigning items to rooms
	item* MagicSpyglass = new item();
  strcpy(MagicSpyglass->getItemType(), "MagicSpyglass");
	Watchtower->dropItems(MagicSpyglass);

	item* MagicRose = new item();
  strcpy(MagicRose->getItemType(), "MagicRose");
	Courtyard->dropItems(MagicRose);
	
	item* MagicCrystalBall = new item();
  strcpy(MagicCrystalBall->getItemType(), "MagicCrystalBall");
	Parlor->dropItems(MagicCrystalBall);
	
	item* MagicCrown = new item();
  strcpy(MagicCrown->getItemType(), "MagicCrown");
	RoyalHall->dropItems(MagicCrown);
	
	item* MagicScepter = new item();
  strcpy(MagicScepter->getItemType(), "MagicScepter");
	SecretPassage->dropItems(MagicScepter);

	// adding items to the player's inventory to begin the game 
  
  item* Keystone = new item();
  strcpy(Keystone->getItemType(), "Keystone");
  inventory.push_back(Keystone);

  item* PetDuckling = new item();
  strcpy(PetDuckling->getItemType(), "PetDuckling");
	inventory.push_back(PetDuckling);
}

/**
* Print out the opening message for the player.
*/
void printWelcome() {
	cout << endl; 
	cout << "Welcome to Adventure!" << endl;
	cout << "This is a castle with 15 rooms (26 if you include outside). Each room connects to at least one other room." << endl;
	cout << "There are also 5 magic items spread throughout the castle." << endl;
	cout << "To win, you must have all 5 magic items in your inventory and then go outside." << endl;
	cout << "\nWarning: don't leave with the castle's keystone or the king's pet duckling!" << endl;
	cout << "If you leave with the keystone, the castle will crumble to ruins. If you leave with the duckling, the king will become furious and have you killed." << endl;
	cout << "\nType 'help' if you need help." << endl;
	cout << endl;
	cout << currentRoom.getLongDescription() << endl;
}

// Print inventory method
void printInventory(vector<char*>* inventory) {
  
  vector<char*>::iterator iter;
  
  if(inventory.size() == 0){
    cout << "You aren't carrying anything." << endl;
  } else {
    cout << "You are carrying: " << endl;
    for (iter = inventory.begin(); iter != inventory.end(); iter++) {
		  cout << (*iter)->getItemType();
		}
  }
}


// Method for picking up items 
void getItems(vector<char*>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom) {
  char input[15];
  map<room*>::iterator roomIter;
  vector<item*>::iterator itemIter;
  for(roomIter = rooms.begin(); roomIter != rooms.end(); roomIter++) {
    if(strcmp(thisRoom, (*roomIter)->getRoom()) == 0) {
      cout << "Which item would you like to pick up?" << endl;
      cin >> input;
		  cin.clear();
		  cin.ignore(10000, '\n');
      for(itemIter = rooms.begin(); itemIter != rooms.end(); itemIter++) {
        if(strcmp(input, (*itemIter)->getItemType()) == 0) {
          inventory->push_back(
        }
      }
      cout << (*iter)->listItems() << endl;
      room newRoom = (*iter)->getRoomByDirection(direction);
      return newRoom->getRoom();
    }
  }
}

