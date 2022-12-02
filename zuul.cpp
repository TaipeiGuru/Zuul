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
Room Outside, EntryHall, EastBalcony, EastCorridor, WestBalcony, WestCorridor, BlueRoom, DiningHall, Courtyard, Chapel, Watchtower, Parlor, ServantQuarters, Kitchen, RoyalHall, Library, LivingQuarters, GreyRoom, Portico, SecretPassage;
ArrayList<Item> inventory = new ArrayList<Item>();

/**
* Create the game and initialise its internal map.
*/

// Main method
int main() {
	createRooms();
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the game is over.

	bool finished = false;
	while (finished == false) {
			Command command = parser.getCommand();
			finished = processCommand(command);
	}
	System.out.println("Thank you for playing. Good bye.");
}

/**
* Create all the rooms and link their exits together.
*/
private void createRooms()
{

// create the rooms and their descriptions 
Outside = new Room("outside the entrance to the castle");
EntryHall = new Room("in the entry hall of the castle. Are those guards carrying swords?");
EastBalcony = new Room("on the East Balcony, the eastern part of the balcony overlooking the valley");
WestBalcony = new Room("on the West Balcony, western part of the balcony overlooking the valley. What a view!");
EastCorridor = new Room("in a corridor connecting the east balcony to other parts of the castle");
WestCorridor = new Room("in a corridor connecting the west balcony to other parts of the castle");
BlueRoom = new Room("in the Blue Room, a room full of treasure. Wow, are those diamonds?!");
DiningHall = new Room("in the Dining Hall, a room where food is served. Yum, I do love roast pig");
Courtyard = new Room("in the Courtyard, an open-air area in the middle of the castle");
Chapel = new Room("in the Chapel, the religious center of the castle (also hosts knighting ceremonies");
Watchtower = new Room("in the watchtower, which also doubles as a guardpost. Takes a few minutes to get up the 154 steps");
Parlor = new Room("in the Parlor, a communal gathering area for the inhabitants of the castle");
ServantQuarters = new Room("in the Servant Quarters, the place where the servants live");
Kitchen = new Room("in the Kitchen. You can hear all sorts of noises down here...");
RoyalHall = new Room("in the Royal Hall, where the king greets his subjects. What a pretty throne!");
Library = new Room("in the Library, a room where all the books and manuscripts are kept");
LivingQuarters = new Room("in the Living Quarters, a place where the king and every other non-servant stays in the castle");
GreyRoom = new Room("in a very dark and dusty place called the Grey Room. I wonder what it's used for?");
Portico = new Room("on the Portico, which also serves as the back exit to the castle. What does that lever do?");
SecretPassage = new Room("in a chilly tunnel lit by torches. Leads right into the thick forest behind the castle. This looks an awful lot like a secret passage...");


// initialise room exits
Outside.setExit("east", EntryHall);

EntryHall.setExit("west", Outside);
EntryHall.setExit("east", Courtyard);
EntryHall.setExit("north", WestBalcony);
EntryHall.setExit("south", EastBalcony);

WestBalcony.setExit("south", EntryHall);
WestBalcony.setExit("north", WestCorridor);

EastBalcony.setExit("south", EastCorridor);
EastBalcony.setExit("north", EntryHall);

WestCorridor.setExit("south", WestBalcony);
WestCorridor.setExit("east", DiningHall);

EastCorridor.setExit("east", Chapel);
EastCorridor.setExit("north", EastBalcony);

DiningHall.setExit("west", WestCorridor);
DiningHall.setExit("east", ServantQuarters);
DiningHall.setExit("north", BlueRoom);

BlueRoom.setExit("east", Parlor);
BlueRoom.setExit("south", DiningHall);

Courtyard.setExit("east", RoyalHall);
Courtyard.setExit("west", EntryHall);

Chapel.setExit("west", EastCorridor);
Chapel.setExit("south", Watchtower);
Chapel.setExit("east", LivingQuarters);

Watchtower.setExit("north", Chapel);
Watchtower.setExit("east", GreyRoom);

GreyRoom.setExit("west", Watchtower);
GreyRoom.setExit("north", LivingQuarters);

LivingQuarters.setExit("west", Chapel);
LivingQuarters.setExit("south", GreyRoom);
LivingQuarters.setExit("north", Library);

Library.setExit("south", LivingQuarters);
Library.setExit("north", RoyalHall);

RoyalHall.setExit("east", Portico);
RoyalHall.setExit("west", Courtyard);
RoyalHall.setExit("south", Library);
RoyalHall.setExit("north", Kitchen);

Kitchen.setExit("south", RoyalHall);
Kitchen.setExit("north", ServantQuarters);

ServantQuarters.setExit("south", Kitchen);
ServantQuarters.setExit("north", Parlor);
ServantQuarters.setExit("west", DiningHall);

Parlor.setExit("south", ServantQuarters);
Parlor.setExit("west", BlueRoom);

Portico.setExit("west", RoyalHall);
Portico.setExit("north", SecretPassage);

SecretPassage.setExit("south", Portico);

currentRoom = Outside;  // start game outside

// adding items and setting them to specific rooms 
EastCorridor.setItem(new Item("MagicCloak"));
Watchtower.setItem(new Item("MagicSpyglass"));
Courtyard.setItem(new Item("MagicRose"));
BlueRoom.setItem(new Item("MagicGems"));
Parlor.setItem(new Item("MagicCrystalBall"));
RoyalHall.setItem(new Item("MagicCrown"));
SecretPassage.setItem(new Item("MagicScepter"));

// adding items to the player's inventory to begin the game 
inventory.add(new Item("Keystone"));
inventory.add(new Item("PetDuckling"));
}

/**
*  Main play routine.  Loops until end of play.
*/

/**
* Print out the opening message for the player.
*/
void printWelcome() {
	cout << endl; 
	cout << "Welcome to Adventure!" << endl;
	cout << "This is a castle with 19 rooms (20 if you include outside). Each room connects to at least one other room." << endl;
	cout << "There are also 7 magic items spread throughout the castle." << endl;
	cout << "To win, you must have all 7 magic items in your inventory and then go outside." << endl;
	cout << "\nWarning: don't leave with the castle's keystone or the king's pet duckling!" << endl;
	cout << "If you leave with the keystone, the castle will crumble to ruins. If you leave with the duckling, the king will become furious and order you to be killed." << endl;
	cout << "\nType 'help' if you need help." << endl;
	cout << endl;
	cout << currentRoom.getLongDescription() << endl;
}

/**
* Given a command, process (that is: execute) the command.
* If this command ends the game, true is returned, otherwise false is
* returned.
*/
private boolean processCommand(Command command) 
{
boolean wantToQuit = false;

if(command.isUnknown()) {
    System.out.println("I don't know what you mean...");
    return false;
}

String commandWord = command.getCommandWord();
if (commandWord.equals("help")) {
    printHelp();
}

/* 
 * wantToQuit is set equal to the "go" command. This ensure that if the 
 * player enters a room and they've met the specified criteria, they'll 
 * be able to win the game. This is in addition to the normal command word 
 * of "quit." 
*/

else if (commandWord.equals("go")) {
    wantToQuit = goRoom(command);
}
else if (commandWord.equals("quit")) {
    wantToQuit = quit(command);
}
else if (commandWord.equals("inventory")) {
	printInventory();
} else if (commandWord.equals("get")) {
	getItem(command);
} else if (commandWord.equals("drop")) {
	dropItem(command);
}
return wantToQuit;
}

// Print inventory method
private void printInventory() {

// Starting output is blank (so nothing gets printed if there's nothing in the inventory)
String output = "";

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
System.out.println("You are carrying:");
System.out.println(output);

}
// implementations of user commands:

/**
* Print out some help information.
* Here we print some stupid, cryptic message and a list of the 
* command words.
*/
private void printHelp() 
{
System.out.println("You are lost. You are alone. You wander");
System.out.println("around in the castle.");
System.out.println();
System.out.println("Your command words are:");
parser.showCommands();
System.out.println("\nTo go somewhere, type \"go \" followed by a direction");
System.out.println("To pick up an item, type \"get \" followed by the item");
System.out.println("To drop an item, type \"drop \" followed by the item");   
System.out.println("To see your inventory, type \"inventory\"");
System.out.println("To quit the game, type \"quit\"");
}

/** 
* Try to go to one direction. If there is an exit, enter the new
* room, otherwise print an error message.
*/
private boolean goRoom(Command command) 
{
if(!command.hasSecondWord()) {
    // if there is no second word, we don't know where to go...
    System.out.println("Go where?");
    return false;
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
/** 
* "Quit" was entered. Check the rest of the command to see
* whether we really quit the game. Return true, if this command
* quits the game, false otherwise.
*/
private boolean quit(Command command) 
{
if(command.hasSecondWord()) {
    System.out.println("Quit what?");
    return false;
}
else
    return true;  // signal that we want to quit
}

