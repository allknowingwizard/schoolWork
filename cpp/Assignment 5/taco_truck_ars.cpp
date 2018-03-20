/*
		Adam Stammer
		3/18/2018
		CS250 - Assignment 5
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

enum ItemType {ENTREE, DRINK, DESSERT};

struct MenuItem {string item; ItemType type; float cost; int qty;};

void printMenu(); // prints the menu to the screen
void readMenuInput(string &); //reads input from the user based on the menu and stores it into the given string
int readMenuItemsFromFile(MenuItem []); //reads the menuitems from the file taco_menu.txt and stores them in the given array
void printItemInfoByType(MenuItem [], ItemType); // menu option 1 - prints the item info of all the items matching the given itemtype
void printItemInfo(MenuItem); // prints the info of the given menuitem
void addItemToBill(MenuItem [], int &, MenuItem mi); // add the given menuItem to the given position in the bill

int main() {
	MenuItem menu[15];
	MenuItem bill[15];
	int billQty = 0;
	int x = readMenuItemsFromFile(menu);
	if(x == -1) {
		cout << "Failed to open file......" << endl << "closing now" << endl;
		return -1;
	}
	bool running = true;
	int iIn = 6;
	while(running) {
		printMenu();
		string input = "";
		readMenuInput(input);
		iIn = stoi(input);
		if(iIn == 1) {
			cout << "\t1. Entree\n\t2. Drink\n\t3. Dessert\n\tSelect an item type: ";
			readMenuInput(input);
			printItemInfoByType(menu, ENTREE);
		} else if(iIn == 2) {
			cout << "\t1. Add by Number\n\t2. Search by Name\n";
			readMenuInput(input);
			iIn = stoi(input);
			if(iIn == 1) {
				cout << "Please enter the number: ";
				readMenuInput(input);
//				iIn = stoi(input);
				addItemToBill(bill, billQty, menu[iIn-1]);
			}
		} else if(iIn == 3) {

		} else if(iIn == 4) {

		} else if(iIn == 5) {

		} else if(iIn == 6)
			running = false;
		else cout << "What you have entered is not an option. Please try again.\n";
	}
	return 0;
}

void printItemInfoByType(MenuItem menu[15], ItemType itemType) {
	MenuItem mi;
	for(int i = 0; i < 15; i++) {
		if((mi = menu[i]).type == itemType) {
			cout << i << ":  " << "Item: " << mi.item << "  Cost: " << mi.cost/* << "  Qty: " << mi.qty*/ << endl; 
		}
	}
}

void addItemToBill(MenuItem bill[15], int & billQty, MenuItem mi) {
	bill[billQty] = mi;
	billQty++;
}
int readMenuItemsFromFile(MenuItem menuItem[15]) {
	ifstream file;
	file.open("taco_menu.txt");
	if(file.fail()) {
		file.close();
		return -1;
	} else {
		MenuItem i;
		string iType = "";
		int iter = 0;
		while(file >> i.item && file >> iType && file >> i.cost) {
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
			menuItem[iter] = i;
			iter++;
		}
	}
	file.close();
	return 0;
}

void readMenuInput(string & input) {
	getline(cin, input);
}

void printMenu() {
	cout << "1. Print Item Info By Type\n";
	cout << "2. Add Item To Bill\n";
	cout << "3. Print Total Cost\n";
	cout << "4. Finalize Sale\n";
	cout << "5. Print Sales By Type\n";
	cout << "6. Exit\n";
}
