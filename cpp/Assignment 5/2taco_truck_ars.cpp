/*
		Adam Stammer
		3/18/2018
		CS250 - Assignment 5
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int ENTREE = 0;
const int DRINK = 1;
const int DESSERT = 2;
struct MenuItem {string item; int type; float cost; int qty;};

void printMenu(); // prints the menu to the screen
void readMenuInput(string &); //reads input from the user based on the menu and stores it into the given string
int readMenuItemsFromFile(MenuItem []); //reads the menuitems from the file taco_menu.txt and stores them in the given array
void printItemInfoByType(MenuItem [], int); // menu option 1 - prints the item info of all the items matching the given itemtype
void printItemInfo(MenuItem); // prints the info of the given menuitem
void addItemToBill(MenuItem); // adds the given menuitem to the bill


int main() {
	MenuItem menu[15] = {};
	int x = readMenuItemsFromFile(menu);
	if(x == -1) {
		cout << "Failed to open file......" << endl << "closing now" << endl;
		return -1;
	}

	printMenu();
	string input = "";
	
	printItemInfoByType(menu, ENTREE);

	return 0;
}

void printItemInfoByType(MenuItem menu[15], int itemType) {
	MenuItem mi;
	for(int i = 0; i < 15; i++) {
		if((mi = menu[i]).type == itemType) {
			cout << i << ":  " << "Item: " << mi.item << "  Cost: " << mi.cost << "  Qty: " << mi.qty << endl; 
		}
	}
}

int readMenuItemsFromFile(MenuItem menuItem[15]) {
	ifstream file;
	file.open("taco_menu.txt");
	if(file.fail()) {
		cout << "fail" << endl;
		file.close();
		return -1;
	} else {
		cout << "success";
		MenuItem i;
		string iType = "";
		int iter = 0;
		while(file >> i.item && file >> iType && file >> i.cost && file >> i.qty) {
			if(iType == "ENTREE")
				i.type = ENTREE;
			else if(iType == "DRINK")
				i.type = DRINK;
			else if(iType == "DESSERT")
				i.type = DESSERT;
			else {
				cout << "Error finding type!" << endl;
				file.close();
				return -1;
			}
			cout << i.item << endl;
			menuItem[iter] = i;
			iter++;
		}
	}
	file.close();
	return 0;
}

void printMenu() {
	cout << "1. Print Item Info By Type\n";
	cout << "2. Add Item To Bill\n";
	cout << "3. Print Total Cost\n";
	cout << "4. Finalize Sale\n";
	cout << "5. Print Sales By Type\n";
	cout << "6. Exit\n";
}
