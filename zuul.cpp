#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

/* This is the game of Zuul, a text-based adventure game that focuses on the user finding
 * certain items in the rooms of a castle and making it out safely. It was initially created 
 * by Michael Kolling and David J. Barnes, and was modified by Jason Randolph. Last edits were 
 * made 12/2/22. */

void createRoom();

// Establishing variables and creating array lists that will be used later in the program 
Room Outside, EntryHall, EastCorridor, WestCorridor, DiningHall, Courtyard, Chapel, Watchtower, Parlor, ServantQuarters, Kitchen, RoyalHall, Library, LivingQuarters, Portico, SecretPassage;
ArrayList<Item> inventory = new ArrayList<Item>();

/**
* Create the game and initialise its internal map.
*/

// Main method
int main() {
	char input[10];
	createRooms();
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the game is over.

	bool finished = false;
	while (finished == false) {
		cout << "Your commands are \"go\", \"quit\", \"inventory\", \"get\", \"drop\", and \"help\"." << endl; 
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		if (commandWord.equals("go")) {
			cout << "Which direction (\"east\", \"south\", \"west\", \"north\") do you want to go?" << endl;	
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			goRoom(input);
		} else if (commandWord.equals("quit")) {
			cout << "Thank you for playing. Good bye." << endl;
			finished = true;
		} else if (commandWord.equals("inventory")) {
			printInventory();
		} else if (commandWord.equals("get")) {
			cout << "Which item do you want to get?" << endl;	
			cin.get(input, 50);
			cin.clear();
			cin.ignore(10000, '\n');
			getItem(input);
		} else if (commandWord.equals("drop")) {
			cout << "Which item do you want to drop?" << endl;	
			cin.get(input, 50);
			cin.clear();
			cin.ignore(10000, '\n');
			dropItem(input);
		}
	}
}

// Create all the rooms and link their exits together.
void createRooms() {

	map<char*, Room*> myMap;
	
	// create the rooms and their descriptions 
	Room* Outside = new Room();
	strcpy(Outside->getDescription(), "outside the entrance to the castle");
	myMap["east"] = EntryHall; 
	
	Room* EntryHall = new Room();
	strcpy(EntryHall->setDescription(), "in the entry hall of the castle. Are those guards carrying swords?");
	myMap["east"] = Courtyard;
	myMap["west"] = Outside;
	myMap["south"] = SouthCorridor;
	myMap["north"] = NorthCorridor;
	
	Room* NorthCorridor = new Room();
	strcpy(NorthCorridor->setDescription(), "in a corridor connecting the entry hall to other parts of the castle");
	myMap["south"] = EntryHall;
	myMap["east"] = DiningHall;
	
	Room* SouthCorridor = new Room();
	strcpy(SouthCorridor->setDescription(), "in a corridor connecting the entry hall to other parts of the castle");
	myMap["north"] = EntryHall;
	myMap["east"] = Chapel;
	
	Room* DiningHall = new Room();
	strcpy(DiningHall->setDescription(), "in the Dining Hall, a room where food is served. Yum, I do love roast pig");
	myMap["west"] = NorthCorridor;
	myMap["east"] = ServantQuarters;
	
	Room* Courtyard = new Room();
	strcpy(Courtyard->setDescription(), "in the Courtyard, an open-air area in the middle of the castle");
	myMap["west"] = EntryHall;
	myMap["east"] = RoyalHall;
	
	Room* Chapel = new Room();
	strcpy(Chapel->setDescription(), "in the Chapel, the religious center of the castle (also hosts knighting ceremonies");
	myMap["south"] = Watchtower;
	myMap["west"] = SouthCorridor;	
	myMap["east"] = LivingQuarters;
	
	Room* Watchtower = new Room();
	strcpy(Watchtower->setDescription(), "in the watchtower, which also doubles as a guardpost. Takes a few minutes to get up the 154 steps");
	myMap["north"] = Chapel;
	
	Room* Parlor = new Room();
	strcpy(Parlor->setDescription(), "in the Parlor, a communal gathering area for the inhabitants of the castle");
	myMap["south"] = ServantQuarters;
	
	Room* ServantQuarters = new Room();
	strcpy(ServantQuarters->setDescription(), "in the Servant Quarters, the place where the servants live");
	myMap["south"] = Kitchen;
	myMap["west"] = DiningHall;
	myMap["north"] = Parlor;
	
	Room* Kitchen = new Room();
	strcpy(Kitchen->setDescription(), "in the Kitchen. You can hear all sorts of noises down here...");
	myMap["south"] = RoyalHall;
	myMap["north"] = ServantQuarters;
	
	Room* RoyalHall = new Room();
	strcpy(RoyalHall->setDescription(), "in the Royal Hall, where the king greets his subjects. What a pretty throne!");
	myMap["south"] = Library;
	myMap["east"] = Portico;
	myMap["north"] = Kitchen;
	myMap["west"] = Courtyard;
	
	Room* Library = new Room();
	strcpy(Library->setDescription(), "in the Library, a room where all the books and manuscripts are kept");
	myMap["south"] = LivingQuarters;
	myMap["north"] = RoyalHall;
	
	Room* LivingQuarters = new Room();
	strcpy(LivingQuarters->setDescription(), "in the Living Quarters, a place where the king and every other non-servant stays in the castle");
	myMap["north"] = Library;
	myMap["west"] = Chapel;
	
	Room* Portico = new Room();
	strcpy(Portico->setDescription(), "on the Portico, which also serves as the back exit to the castle. What does that lever do?");
	myMap["north"] = SecretPassage;
	myMap["west"] = RoyalHall;
	
	Room* SecretPassage = new Room();
	strcpy(SecretPassage->setDescription(), "in a chilly tunnel lit by torches. Leads right into the thick forest behind the castle. This looks an awful lot like a secret passage...");
	myMap["south"] = Portico;
	
	// Initializing and assigning items to rooms
	Item* MagicSpyglass = new Item();
	Watchtower->setItem(MagicSpyglass);
	
	Item* MagicRose = new Item();
	Courtyard->setItem(MagicRose);
	
	Item* MagicCrystalBall = new Item();
	Parlor->setItem(MagicCrystalBall);
	
	Item* MagicCrown = new Item();
	RoyalHall->setItem(MagicCrown);
	
	Item* MagicScepter = new Item();
	SecretPassage->setItem(MagicScepter);

	// adding items to the player's inventory to begin the game 
	inventory.add(new Item("Keystone"));
	inventory.add(new Item("PetDuckling"));
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
private void printInventory() {

	cout << "You are carrying:" << endl;

	/* For loop used to run through the inventory array list and print any items that are in the inventory.
	 * It looks more complicated than it actually is - I included some if-else statements to ensure that 
	 * proper grammatical conventions are followed depending on the number of items in the inventory (mostly
	 * because I was bored and it bothered me) 
	 * */
	for (int i = 0; i < inventory.size(); i++) {
		if(inventory.size() == 1) {
			output += inventory.get(i).getDescription() + " ";

		} else if(inventory.size() == 2) {
			if(i == inventory.size() - 1) {
				output += inventory.get(i).getDescription();
			} else {
				output += inventory.get(i).getDescription() + " and ";
			}
		} else {
			if(i == inventory.size() - 1) {
				output += "and " + inventory.get(i).getDescription() + " ";
			} else {
				output += inventory.get(i).getDescription() + ", ";
			}
		}
	}
	cout << output << endl;
}
// implementations of user commands:

/** 
* Try to go to one direction. If there is an exit, enter the new
* room, otherwise print an error message.
*/
private boolean goRoom(char* input) {
	
}

String direction = command.getSecondWord();

// Try to leave current room.
Room nextRoom = currentRoom.getExit(direction);

if (nextRoom == null)
    System.out.println("There is no door!");
else {
    currentRoom = nextRoom;
    System.out.println(currentRoom.getLongDescription());

    /* Help with "contains()" method from https://www.geeksforgeeks.org/arraylist-contains-java/ 
     * This is the winning condition. If the player's outside AND the number of items in the inventory 
     * is 7 AND the inventory doesn't contain PetDucking or Keystone, the boolean will return as true 
     * and the game ends. If not, play continues. 
     * */
    if(currentRoom == Outside && inventory.size() == 7 && inventory.contains("PetDuckling") == false && inventory.contains("Keystone") == false) {
	System.out.println("Congratulations, all the magic items were collected. You won!");
	return true;
    }
}
return false;
}

// Method for picking up items 
private void getItem(Command command) 
{
if(!command.hasSecondWord()) {
    // if there is no second word, we don't know what to get...
    System.out.println("Get what?");
    return;
}

String item = command.getSecondWord();

// Try to pick up item.
Item newItem = currentRoom.getItem(item);

if (newItem == null)
    System.out.println("That is not a valid item!");

/* 
 * Very similar to the goRoom method. If a valid item is entered, 
 * that item will be removed from the current room and added to the 
 * user's inventory. 
 * */
else {
    inventory.add(newItem);
    currentRoom.removeItem(item);
    System.out.println("You picked up the item: " + item);

}
}

// Method for dropping items. Basically the same as the previous method but adding to room and removing from inventory instead.
private void dropItem(Command command) 
{
if(!command.hasSecondWord()) {
    // if there is no second word, we don't know what to drop...
    System.out.println("Drop what?");
    return;
}

String item = command.getSecondWord();

// Try to drop item.
Item newItem = null;
int index = 0;

/* 
 * This for loop runs through the inventory list and looks for an item that matches the user's input.
 * If an item is found, the index variable is set to that index and then that item is removed from the inventory
 * and placed in the current room. 
 * */
for (int i = 0; i < inventory.size(); i++) {
		if(inventory.get(i).getDescription().equals(item)) {
			newItem = inventory.get(i);
			index = i;
		}
	}

if (newItem == null)
    System.out.println("You don't have that item!");
else {
    inventory.remove(index);
    currentRoom.setItem(new Item(item));
    System.out.println("You dropped the item: " + item);

}
}
