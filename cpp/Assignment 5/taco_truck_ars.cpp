#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

enum ItemType {};

struct MenuItem {};

void printMenu(); // prints the menu to the screen
void readMenuInput(); //reads input from the user based on the menu and 
void readMenuItemsFromFile(MenuItem *); //reads the menuitems from the file taco_menu.txt
void printItemInfoByType(ItemType); // menu option 1 - prints the item info of all the items matching the given itemtype
void printItemInfo(MenuItem); // prints the info of the given menuitem
void addItemToBill(MenuItem); // adds the given menuitem to the bill


int main() {
	
	
	return 0;
}
