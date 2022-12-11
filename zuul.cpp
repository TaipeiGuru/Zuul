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

void createRooms(vector<room*>* rooms, vector<item*>* roomItems, vector<int>* inventory);
int goRoom(vector<room*>* rooms, char* direction, int thisRoom);
void printWelcome();
void printInventory(vector<int> inventory);
void getItems(vector<int>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom);
void dropItems(vector<int>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom);

/*
* Create the game and initialise its internal map.
*/

// Main method
int main() {
  vector<room*> rooms;
  vector<item*> roomItems;
  vector<int> inventory;
  int thisRoom = 0;
  createRooms(&rooms, &roomItems, &inventory);
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
		if (strcmp(input, "go") == 0) {
			cout << "Which direction do you want to go? Your options are:" << endl;
			vector<room*>::iterator roomIter;
			for(roomIter = rooms.begin(); roomIter != rooms.end(); roomIter++) {
			  if((*roomIter)->getRoom() == thisRoom) {
			    (*roomIter)->listExits();
			  }
			}
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			thisRoom = goRoom(&rooms, input, thisRoom);
		} else if (strcmp(input, "quit") == 0) {
			cout << "Thank you for playing. Good bye." << endl;
			finished = true;
		} else if (strcmp(input, "inventory") == 0) {
			printInventory(inventory);
		} else if (strcmp(input, "get") == 0) {
      getItems(&inventory, &rooms, &roomItems, thisRoom);
		} else if (strcmp(input, "drop") == 0) {
			dropItems(&inventory, &rooms, &roomItems, thisRoom);
		}
    if(thisRoom == 0) {
      if(inventory.size() == 5) {
        vector<int>::iterator iter;
        for(iter = inventory.begin(); iter != inventory.end(); iter++) {
          if(strcmp(iter->getItemType(), "PetDuckling") != 0) {
            if(strcmp(iter->getItemType(), "Keystone") != 0) {
              cout << "Congratulations, you won!" << endl;
              finished = true;
            } else {
              cout << "Uh oh....you went outside with the keystone. Game over - the castle is now collapsing on you..." << endl;
              finished = true;
            }
          } else {
            cout << "Uh oh....you went outside with the king's pet duckling. Game over - prepare to die..." << endl;
            finished = true;
          }
        } 
      }  
    }
	}
}

int goRoom(vector<room*>* rooms, char* direction, int thisRoom) {
  vector<room*>::iterator iter;
  for(iter = rooms->begin(); iter != rooms->end(); iter++) {
    if(thisRoom == (*iter)->getRoom()) {
      cout << "You are now " << (*iter)->showDescription() << endl;
      cout << "Items in the room: " << endl;
      (*iter)->listItems();
      room* newRoom = (*iter)->getRoomByDirection(direction);
      return newRoom->getRoom();
    }
  }
  delete direction;
}

// Create all the rooms and link their exits together.
void createRooms(vector<room*>* rooms, vector<item*>* roomItems, vector<char*>* inventory) {
	
	// create the rooms and their descriptions 
	room* Outside = new room();
  room* EntryHall = new room();
  room* NorthCorridor = new room();
  room* SouthCorridor = new room();
  room* DiningHall = new room();
  room* Courtyard = new room();
  room* Chapel = new room();
  room* Watchtower = new room();
  room* Parlor = new room();
  room* ServantQuarters = new room();
  room* Kitchen = new room();
  room* RoyalHall = new room();
  room* Library = new room();
  room* LivingQuarters = new room();
  room* Portico = new room();
  room* SecretPassage = new room();

	strcpy(Outside->showDescription(), "outside the entrance to the castle");
	Outside->getRoomExits()->insert(pair<char*, room*>("east", EntryHall));
	Outside->setRoom(1);
	rooms->push_back(Outside);
	
	strcpy(EntryHall->showDescription(), "in the entry hall of the castle. Are those guards carrying swords?");
	EntryHall->getRoomExits()->insert(pair<char*, room*>("east", Courtyard));
	EntryHall->getRoomExits()->insert(pair<char*, room*>("west", Outside));
	EntryHall->getRoomExits()->insert(pair<char*, room*>("north", NorthCorridor));
	EntryHall->getRoomExits()->insert(pair<char*, room*>("south", SouthCorridor));
	EntryHall->setRoom(2);
	rooms->push_back(EntryHall);

	strcpy(NorthCorridor->showDescription(), "in a northern corridor connecting the entry hall to other parts of the castle");
	NorthCorridor->getRoomExits()->insert(pair<char*, room*>("south", EntryHall));
	NorthCorridor->getRoomExits()->insert(pair<char*, room*>("east", DiningHall));
	NorthCorridor->setRoom(3);
	rooms->push_back(NorthCorridor);
	
	strcpy(SouthCorridor->showDescription(), "in a southern corridor connecting the entry hall to other parts of the castle");
	SouthCorridor->getRoomExits()->insert(pair<char*, room*>("north", EntryHall));
	SouthCorridor->getRoomExits()->insert(pair<char*, room*>("east", Chapel));
	SouthCorridor->setRoom(4);
	rooms->push_back(SouthCorridor);
		
	strcpy(DiningHall->showDescription(), "in the Dining Hall, a room where food is served. Yum, I do love roast pig");
	DiningHall->getRoomExits()->insert(pair<char*, room*>("west", NorthCorridor));
	DiningHall->getRoomExits()->insert(pair<char*, room*>("east", ServantQuarters));
	DiningHall->setRoom(5);
	rooms->push_back(DiningHall);
		
	strcpy(Courtyard->showDescription(), "in the Courtyard, an open-air area in the middle of the castle");
	Courtyard->getRoomExits()->insert(pair<char*, room*>("west", EntryHall));
	Courtyard->getRoomExits()->insert(pair<char*, room*>("east", RoyalHall));
	Courtyard->setRoom(6);
	rooms->push_back(Courtyard);
		
	strcpy(Chapel->showDescription(), "in the Chapel, the religious center of the castle (also hosts knighting ceremonies");
	Chapel->getRoomExits()->insert(pair<char*, room*>("west", SouthCorridor));
	Chapel->getRoomExits()->insert(pair<char*, room*>("south", Watchtower));
	Chapel->setRoom(7);
	rooms->push_back(Chapel);
		
	strcpy(Watchtower->showDescription(), "in the watchtower, which also doubles as a guardpost. Takes a few minutes to get up the 154 steps");
	Watchtower->getRoomExits()->insert(pair<char*, room*>("north", Chapel));
	Watchtower->setRoom(8);
	rooms->push_back(Watchtower);
		
	strcpy(Parlor->showDescription(), "in the Parlor, a communal gathering area for the inhabitants of the castle");
	Parlor->getRoomExits()->insert(pair<char*, room*>("south", ServantQuarters));
	Parlor->setRoom(9);
	rooms->push_back(Parlor);
		
	strcpy(ServantQuarters->showDescription(), "in the Servant Quarters, the place where the servants live");
	ServantQuarters->getRoomExits()->insert(pair<char*, room*>("west", DiningHall));
	ServantQuarters->getRoomExits()->insert(pair<char*, room*>("south", Kitchen));
	ServantQuarters->getRoomExits()->insert(pair<char*, room*>("north", Parlor));
	ServantQuarters->setRoom(10);
	rooms->push_back(ServantQuarters);
		
	strcpy(Kitchen->showDescription(), "in the Kitchen. You can hear all sorts of noises down here...");
	Kitchen->getRoomExits()->insert(pair<char*, room*>("south", RoyalHall));
	Kitchen->getRoomExits()->insert(pair<char*, room*>("north", ServantQuarters));
	Kitchen->setRoom(11);
	rooms->push_back(Kitchen);
		
	strcpy(RoyalHall->showDescription(), "in the Royal Hall, where the king greets his subjects. What a pretty throne!");
	RoyalHall->getRoomExits()->insert(pair<char*, room*>("east", Portico));
	RoyalHall->getRoomExits()->insert(pair<char*, room*>("west", Courtyard));
	RoyalHall->getRoomExits()->insert(pair<char*, room*>("north", Kitchen));
	RoyalHall->getRoomExits()->insert(pair<char*, room*>("south", Library));
	RoyalHall->setRoom(12);
	rooms->push_back(RoyalHall);
	
	strcpy(Library->showDescription(), "in the Library, a room where all the books and manuscripts are kept");
	Library->getRoomExits()->insert(pair<char*, room*>("south", LivingQuarters));
	Library->getRoomExits()->insert(pair<char*, room*>("north", RoyalHall));
	Library->setRoom(13);
	rooms->push_back(Library);
		
	strcpy(LivingQuarters->showDescription(), "in the Living Quarters, a place where the king and every other non-servant stays in the castle");
	LivingQuarters->getRoomExits()->insert(pair<char*, room*>("north", Library));
	LivingQuarters->getRoomExits()->insert(pair<char*, room*>("west", Chapel));
	LivingQuarters->setRoom(4);
	rooms->push_back(LivingQuarters);
		
	strcpy(Portico->showDescription(), "on the Portico, which also serves as the back exit to the castle. What does that lever do?");
	Portico->getRoomExits()->insert(pair<char*, room*>("north", SecretPassage));
	Portico->getRoomExits()->insert(pair<char*, room*>("west", RoyalHall));
	Portico->setRoom(15);
	rooms->push_back(Portico);
		
	strcpy(SecretPassage->showDescription(), "in a chilly tunnel lit by torches. This looks an awful lot like a secret passage...");
	SecretPassage->getRoomExits()->insert(pair<char*, room*>("south", Portico));
	SecretPassage->setRoom(16);
	rooms->push_back(SecretPassage);
		
	// Initializing and assigning items to rooms
	item* MagicSpyglass = new item();
  strcpy(MagicSpyglass->getItemType(), "MagicSpyglass");
  MagicSpyglass->setItemID(1);
	Watchtower->dropItems(MagicSpyglass);

	item* MagicRose = new item();
  strcpy(MagicRose->getItemType(), "MagicRose");
  MagicRose->setItemID(2);
	Courtyard->dropItems(MagicRose);
	
	item* MagicCrystalBall = new item();
  strcpy(MagicCrystalBall->getItemType(), "MagicCrystalBall");
  MagicCrystalBall->setItemID(3);
	Parlor->dropItems(MagicCrystalBall);
	
	item* MagicCrown = new item();
  strcpy(MagicCrown->getItemType(), "MagicCrown");
  MagicCrown->setItemID(4);
	RoyalHall->dropItems(MagicCrown);
	
	item* MagicScepter = new item();
  strcpy(MagicScepter->getItemType(), "MagicScepter");
  MagicScepter->setItemID(5);
	SecretPassage->dropItems(MagicScepter);

	// adding items to the player's inventory to begin the game 
  
  item* Keystone = new item();
  strcpy(Keystone->getItemType(), "Keystone");
  Keystone->setItemID(6);
  inventory->push_back(Keystone->getItemID());

  item* PetDuckling = new item();
  strcpy(PetDuckling->getItemType(), "PetDuckling");
  PetDuckling->setItemID(7);
	inventory->push_back(PetDuckling->getItemID());
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
}

// Print inventory method
void printInventory(vector<char*>* inventory) {
  
  vector<char*>::iterator iter;
  
  if(inventory->size() == 0){
    cout << "You aren't carrying anything." << endl;
  } else {
    cout << "You are carrying: " << endl;
    for (iter = inventory->begin(); iter != inventory->end(); iter++) {
		  cout << (*iter)->getItemType() << endl;
		}
  }
}


// Method for picking up items 
void getItems(vector<int>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom) {
  char input[15];
  map<char*, room*>::iterator roomIter;
  vector<item*>::iterator itemIter;
  
  for(roomIter = rooms->begin(); roomIter != rooms->end(); roomIter++) {
    if(strcmp(thisRoom, roomIter->getRoom()) == 0) {
      cout << "Which item would you like to pick up?" << endl;
      cin >> input;
		  cin.clear();
		  cin.ignore(10000, '\n');
      for(itemIter = roomItems->begin(); itemIter != roomItems->end(); itemIter++) {
        if(strcmp(input, (*itemIter)->getItemType()) == 0) {
          inventory->push_back((*item)->getItemID());
          *item = roomItems->erase(*item);
        }
      }
      cout << "The " << input << " has been picked up!" << endl;
    }
  }
}

void dropItems(vector<int>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom) {
  char input[15];
  vector<int>::iterator invIter;
  map<char*, room*>::iterator roomIter;
  vector<item*>::iterator itemIter;
  
  cout << "Items in your inventory:" << endl;
  for(invIter = inventory->begin(); invIter != inventory->end(); invIter++) {
   cout << invIter->getItemType() << endl; 
  }
  
  cout << "Which item would you like to drop?" << endl;
  cin >> input;
	cin.clear();
	cin.ignore(10000, '\n');
  
  for(roomIter = rooms->begin(); roomIter != rooms->end(); roomIter++) {
    if(strcmp(thisRoom, roomIter->getRoom()) == 0) {
      for(itemIter = roomItems->begin(); itemIter != roomItems->end(); itemIter++) {
        if(strcmp(input, (*itemIter)->getItemType()) == 0) {
          (*roomIter)->dropItems(*itemIter);
          inventory->erase(*item);
        }
      }
      cout << "The " << input << " has been dropped!" << endl;
    }
  }
}

