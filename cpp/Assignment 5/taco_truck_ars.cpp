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
#include <vector>

using namespace std;

enum ItemType {ENTREE, DRINK, DESSERT, NUM_TYPES};

const string ITEM_TYPES[] = {"ENTREE", "DRINK", "DESSERT"};

struct MenuItem {string name; ItemType type; float cost; int qty;/*cumulative sales, or qty to buy*/};
struct Bill {float total; float tax; float tip;};

int printMenu(const string[], int, string &); // prints the menu to the screen
int readMenuItemsFromFile(MenuItem []); //reads the menuitems from the file taco_menu.txt and stores them in the given array
void printItemInfoByType(MenuItem [], ItemType); // menu option 1 - prints the item info of all the items matching the given itemtype
void printItemInfo(MenuItem); // prints the info of the given menuitem
void addItemToBill(MenuItem[], MenuItem [], int); // add the menuItem at the given index to the given position in the bill (menu,bill,index)
						  // also increments cumultiveSales of menuItems
void searchItems(MenuItem[], MenuItem[], string);//searches the first array for the given string and fills the second array with the results
void printTotalCost(MenuItem[]); // prints the total cost of the items in the array
void printBill(MenuItem[], MenuItem[]); // finalizes the sale, prints the bill and clears all selections
void printTotalByType(MenuItem[], ItemType); // calculates the total cumulative sales of the given item type
void calcTotalBill(MenuItem[], Bill &); // calculates the total cost and tax/tip of items in the array and fill the Bill with it

int main() {
	MenuItem menu[15];//the available food items
	vector<MenuItem> bill;//the currently selected items to be purchased
	int x = readMenuItemsFromFile(menu); // loads in the menu from the file
	if(x == -1) { // file read failed
		cout << "Failed to open file......" << endl << "closing now" << endl;
		return -1;
	}
	bool running = true;
	int iIn = 6;//ui user choice (1-6)
	const string mainMenu[] = {"Print Items By Type", "Add Item(s)", "Print Current Total", "Finalize Sale", "Print Revenue By Type", "Exit"};
	string input = "";
	while(running) {
		int val = -1;
		while(val != 1) {//if user has yet to enter an integer
			val = printMenu(mainMenu, 6, input);
			if(val != 1)
				cout << "Not Valid Option. Please Try Again.\n";
		}
		iIn = stoi(input);
		switch(iIn) {
			case 1:
				int i = -1;
				while(i != 0) {
					i = printMenu(ITEM_TYPES, NUM_TYPES, input);
					if(i == 0) {
						int choice = stoi(input);
						if(choice > 0 && choice < 4)
							printItemInfoByType(menu, static_cast<ItemType>(choice));
					} else {i = -1;  cout << "Invalid Input. Please Try Again.\n";}
				}
				break;
			case 2:
				cout << "\t1. Add by Number\n\t2. Search by Name\n";
				
				iIn = stoi(input);
				if(iIn == 1) {
					cout << "Please enter the number: ";
					//					iIn = stoi(input);
					
				}
				break;
			case 4:

				break;
			case 5:

				break;

			case 6:
				cout << "Closing"<< endl;
				running = false;
				break;
			default:
				cout << "NOT AN OPTION. PLEASE TRY AGAIN.\n";
				break;
		}
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
		MenuItem i = {};
		int iter = 0;
		string itemName = "";
		int iType = 0;
		while(getline(file, i.name) && file >> iType && file >> i.cost) {
			i.type = static_cast<ItemType>(iType);
			menuItem[iter] = i;
			iter++;
		}
	}
	file.close();
	return 0;
}

void printMenu(string options[], int nOptions, string &input) {
	for(int i = 0; i < nOptions; i++) {
		cout << i << ". " << options[i] << endl;
	}
}
