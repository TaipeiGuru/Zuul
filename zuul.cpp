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
void printInventory(vector<char*> inventory);
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
  createRooms(rooms, roomItems, inventory);
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
			  if(roomIter->getRoom() == thisRoom) {
			    roomIter->listExits();
			  }
			}
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			thisRoom = goRoom(rooms, input, thisRoom);
		} else if (strcmp(input, "quit") == 0) {
			cout << "Thank you for playing. Good bye." << endl;
			finished = true;
		} else if (strcmp(input, "inventory") == 0) {
			printInventory(inventory);
		} else if (strcmp(input, "get") == 0) {
      getItems(inventory, rooms, roomItems, thisRoom);
		} else if (strcmp(input, "drop") == 0) {
			dropItems(inventory, rooms, roomItems, thisRoom);
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
  for(iter = rooms.begin(); iter != rooms.end(); iter++) {
    if(thisRoom == (*iter)->getRoom()) {
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
	room* Outside = new room();
	strcpy(Outside->getDescription(), "outside the entrance to the castle");
	Outside->getRoomExits()->insert(pair<char*, Room*>("east", EntryHall));
	Outside->setRoom(1);
	rooms->push_back(Outside);
	
	room* EntryHall = new room();
	strcpy(EntryHall->setDescription(), "in the entry hall of the castle. Are those guards carrying swords?");
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("east", Courtyard));
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("west", Outside));
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("north", NorthCorridor));
	EntryHall->getRoomExits()->insert(pair<char*, Room*>("south", SouthCorridor));
	EntryHall->setRoom(2);
	rooms->push_back(EntryHall);
	
	room* NorthCorridor = new room();
	strcpy(NorthCorridor->setDescription(), "in a northern corridor connecting the entry hall to other parts of the castle");
	NorthCorridor->getRoomExits()->insert(pair<char*, Room*>("south", EntryHall));
	NorthCorridor->getRoomExits()->insert(pair<char*, Room*>("east", DiningHall));
	NorthCorridor->setRoom(3);
	rooms->push_back(NorthCorridor);
	
	room* SouthCorridor = new room();
	strcpy(SouthCorridor->setDescription(), "in a southern corridor connecting the entry hall to other parts of the castle");
	SouthCorridor->getRoomExits()->insert(pair<char*, Room*>("north", EntryHall));
	SouthCorridor->getRoomExits()->insert(pair<char*, Room*>("east", Chapel));
	SouthCorridor->setRoom(4);
	rooms->push_back(SouthCorridor);
		
	room* DiningHall = new room();
	strcpy(DiningHall->setDescription(), "in the Dining Hall, a room where food is served. Yum, I do love roast pig");
	DiningHall->getRoomExits()->insert(pair<char*, Room*>("west", NorthCorridor));
	DiningHall->getRoomExits()->insert(pair<char*, Room*>("east", ServantQuarters));
	DiningHall->setRoom(5);
	rooms->push_back(DiningHall);
		
	room* Courtyard = new room();
	strcpy(Courtyard->setDescription(), "in the Courtyard, an open-air area in the middle of the castle");
	Courtyard->getRoomExits()->insert(pair<char*, Room*>("west", EntryHall));
	Courtyard->getRoomExits()->insert(pair<char*, Room*>("east", RoyalHall));
	Courtyard->setRoom(6);
	rooms->push_back(Courtyard);
		
	room* Chapel = new room();
	strcpy(Chapel->setDescription(), "in the Chapel, the religious center of the castle (also hosts knighting ceremonies");
	Chapel->getRoomExits()->insert(pair<char*, Room*>("east", LivingQuarters));
	Chapel->getRoomExits()->insert(pair<char*, Room*>("west", SouthCorridor));
	Chapel->getRoomExits()->insert(pair<char*, Room*>("south", Watchtower));
	Chapel->setRoom(7);
	rooms->push_back(Chapel);
		
	room* Watchtower = new room();
	strcpy(Watchtower->setDescription(), "in the watchtower, which also doubles as a guardpost. Takes a few minutes to get up the 154 steps");
	Watchtower->getRoomExits()->insert(pair<char*, Room*>("north", Chapel));
	Watchtower->setRoom(8);
	rooms->push_back(Watchtower);
		
	room* Parlor = new room();
	strcpy(Parlor->setDescription(), "in the Parlor, a communal gathering area for the inhabitants of the castle");
	Parlor->getRoomExits()->insert(pair<char*, Room*>("south", ServantQuarters));
	Parlor->setRoom(9);
	rooms->push_back(Parlor);
		
	room* ServantQuarters = new room();
	strcpy(ServantQuarters->setDescription(), "in the Servant Quarters, the place where the servants live");
	ServantQuarters->getRoomExits()->insert(pair<char*, Room*>("west", DiningHall));
	ServantQuarters->getRoomExits()->insert(pair<char*, Room*>("south", Kitchen));
	ServantQuarters->getRoomExits()->insert(pair<char*, Room*>("north", Parlor));
	ServantQuarters->setRoom(10);
	rooms->push_back(ServantQuarters);
		
	room* Kitchen = new room();
	strcpy(Kitchen->setDescription(), "in the Kitchen. You can hear all sorts of noises down here...");
	Kitchen->getRoomExits()->insert(pair<char*, Room*>("south", RoyalHall));
	Kitchen->getRoomExits()->insert(pair<char*, Room*>("north", ServantQuarters));
	Kitchen->setRoom(11);
	rooms->push_back(Kitchen);
		
	room* RoyalHall = new room();
	strcpy(RoyalHall->setDescription(), "in the Royal Hall, where the king greets his subjects. What a pretty throne!");
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("east", Portico));
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("west", Courtyard));
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("north", Kitchen));
	RoyalHall->getRoomExits()->insert(pair<char*, Room*>("south", Library));
	RoyalHall->setRoom(12);
	rooms->push_back(RoyalHall);
	
	room* Library = new room();
	strcpy(Library->setDescription(), "in the Library, a room where all the books and manuscripts are kept");
	Library->getRoomExits()->insert(pair<char*, Room*>("south", LivingQuarters));
	Library->getRoomExits()->insert(pair<char*, Room*>("north", RoyalHall));
	Library->setRoom(13);
	rooms->push_back(Library);
		
	room* LivingQuarters = new room();
	strcpy(LivingQuarters->setDescription(), "in the Living Quarters, a place where the king and every other non-servant stays in the castle");
	LivingQuarters->getRoomExits()->insert(pair<char*, Room*>("north", Library));
	LivingQuarters->getRoomExits()->insert(pair<char*, Room*>("west", Chapel));
	LivingQuarters->setRoom(4);
	rooms->push_back(LivingQuarters);
		
	room* Portico = new room();
	strcpy(Portico->setDescription(), "on the Portico, which also serves as the back exit to the castle. What does that lever do?");
	Portico->getRoomExits()->insert(pair<char*, Room*>("north", SecretPassage));
	Portico->getRoomExits()->insert(pair<char*, Room*>("west", RoyalHall));
	Portico->setRoom(15);
	rooms->push_back(Portico);
		
	room* SecretPassage = new room();
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
		  cout << (*iter)->getItemType() << endl;
		}
  }
}


// Method for picking up items 
void getItems(vector<int>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom) {
  char input[15];
  map<room*>::iterator roomIter;
  vector<item*>::iterator itemIter;
  
  for(roomIter = rooms.begin(); roomIter != rooms.end(); roomIter++) {
    if(strcmp(thisRoom, (*roomIter)->getRoom()) == 0) {
      cout << "Which item would you like to pick up?" << endl;
      cin >> input;
		  cin.clear();
		  cin.ignore(10000, '\n');
      for(itemIter = roomItems.begin(); itemIter != roomItems.end(); itemIter++) {
        if(strcmp(input, (*itemIter)->getItemType()) == 0) {
          inventory->push_back((*item)->getItemID());
          *item = roomItems->erase(*item);
        }
      }
      cout << "The " << input << " has been picked up!" << endl;
    }
  }
}

void dropItems(vector<char*>* inventory, vector<room*>* rooms, vector<item*>* roomItems, int thisRoom) {
  char input[15];
  vector<int>::iterator invIter;
  map<room*>::iterator roomIter;
  vector<item*>::iterator itemIter;
  
  cout << "Items in your inventory:" << endl;
  for(invIter = inventory.begin(); invIter != inventory.end(); invIter++) {
   cout << (*invIter)->getItemType(); 
  }
  
  cout << "Which item would you like to drop?" << endl;
  cin >> input;
	cin.clear();
	cin.ignore(10000, '\n');
  
  for(roomIter = rooms.begin(); roomIter != rooms.end(); roomIter++) {
    if(strcmp(thisRoom, (*roomIter)->getRoom()) == 0) {
      for(itemIter = roomItems.begin(); itemIter != roomItems.end(); itemIter++) {
        if(strcmp(input, (*itemIter)->getItemType()) == 0) {
          (*roomIter)->dropItems(*itemIter);
          inventory->erase(*item);
        }
      }
      cout << "The " << input << " has been dropped!" << endl;
    }
  }
}

