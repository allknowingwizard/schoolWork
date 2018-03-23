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

const string ITEM_TYPES[] = {"ENTREE", "DRINK", "DESSERT", "Please Select a Type"};
const int MENU_SIZE = 15;
const string INVALID = "Not a valid option. Please try again.\n";

struct MenuItem {string name; ItemType type; float cost; int qty;/*cumulative sales, or qty to buy*/};
struct Check {float total; float tax; float tip;};

int printMenu(const string[], int, string &); // prints the menu to the screen
int readMenuItemsFromFile(MenuItem []); //reads the menuitems from the file taco_menu.txt and stores them in the given array
void printItemInfoByType(MenuItem [], ItemType); // menu option 1 - prints the item info of all the items matching the given itemtype
void printItemInfo(MenuItem, bool); // prints the info of the given menuitem, if bool is true qty is printed too, otherwise not
void addItemToBill(vector<MenuItem> &, MenuItem); //
void searchItems(MenuItem[], MenuItem[], string);//searches the first array for the given string and fills the second array with pointers to the results
void printTotalCost(MenuItem[]); // prints the total cost of the items in the array
void printBill(MenuItem[], vector<MenuItem> &, bool); // finalizes the sale, prints the bill and clears all selections
void printTotalByType(MenuItem[], ItemType); // calculates the total cumulative sales of the given item type
void calcTotalBill(MenuItem[], int, Check &); // calculates the total cost and tax/tip of items in the array and fill theCheckwith it

int main() {
	MenuItem menu[MENU_SIZE];//the available food items, stores amount sold in qty
	vector<MenuItem> bill;//the currently selected items to be purchased, stores amount selected in qty
	int x = readMenuItemsFromFile(menu); // loads in the menu from the file
	if(x == -1) { // file read failed
		cout << "Failed to open file......" << endl << "closing now" << endl;
		return -1;
	}
	bool running = true;
	int iIn = -1;//ui user choice (1-6)
	const string mainMenu[] = {"Print Items By Type", "Add Item(s)", "Print Current Total", "Finalize Sale", "Print Revenue By Type", "Exit", "Please Select An Option"};
	const string addItemMenu[] = {"Add By Number", "Search By Name", "Please Select a Method"};
	string input = "";
	

	while(running) {
		int val = -10;
		while(val != 1) { // until the user enters an integer
			val = printMenu(mainMenu, 6, input); // print the menu
			if(val != 1) // request retry and reprint menu
				cout << "Not Valid Option. Please Try Again.\n";
		}
		val = -1;
		iIn = stoi(input); // get numerical input

		//pre-initialzation to avoid cross initialization of future switch-case
		string itemNames[MENU_SIZE+1] = {};
		MenuItem results[MENU_SIZE] = {};
		bool adding = true;
		ItemType queryType;
		Check revenue;
		//

		switch(iIn) { // main menu input
			case 1: // Print Item Info By Type
				while(val != 1) { // until user enters a string
					val = printMenu(ITEM_TYPES, NUM_TYPES, input); // print item types menu
					if(val == 1) { // user entered an integer
						iIn = stoi(input); // convert string to int
						printItemInfoByType(menu, static_cast<ItemType>(iIn-1)); // print item info by the type chosen
					} else {cout << "Invalid Input. Please Try Again.\n";} // try again
				}
				val = -1; // reset menu input type
				break;
			case 2: // Add Item to Bill
				while(val != 1) { // while user still hasn't entered a number
					val = printMenu(addItemMenu, 2, input); // print the addItemMenu
					if(val == 1) { // if they enter a number
						iIn = stoi(input); // store input as int
					} else { //otherwise, prompt for retry
						cout << "Not valid option. Please try again.\n";
					}
				}
				val = -1; // reset menu input type
				switch(iIn) { // addItemMenu input
					case 1: // add by number
						
						for(int i = 0; i < MENU_SIZE; i++) { // loop through every menu item
							itemNames[i] = menu[i].name; // fill itemNames with the names
						}
						itemNames[15] = "Enter the Item Number to Add (-1 to return)"; // add user prompt
						adding = true; // loop this menu until they enter -1
						while(val != 1 || adding) { // still adding food to selection, or failed to enter valid option
							val = printMenu(itemNames, MENU_SIZE, input); // display item options and prompt for input
							if(val == 1) { // valid input
								iIn = stoi(input); // convert to int
								if(iIn == -1) { // -1 to quit
									adding = false;// quit
									cout << "Returning to Main Menu...\n";
								} else if(iIn > 0 && iIn < MENU_SIZE) { // if valid range
									addItemToBill(bill, menu[iIn-1]); // add the item to the bill
								} else {
									cout << "Not a valid option. Please try again.\n"; // prompt for retry
								}
							} else {
								cout << "Not a valid option. Please try again.\n";
							}
						}
						break;
					case 2: //search by name

						searchItems(menu, results, input);
						break;
					default:
						break;
				}
				break;
			case 3: // Print Current Total
				printBill(menu, bill, false); // prints out the currently selected items and the resulting totals
											  // does not clear selections
				break;
			case 4: // Finalize the Sale and Print the bill
				printBill(menu, bill, true); // prints out the currently selected items and the resulting totals
											 // clears the current selections
				break;
			case 5: // calculate and print the total revenue by type
				val = -1;
				while(val != 1) { // continue until number is entered
					val = printMenu(ITEM_TYPES, NUM_TYPES, input); // display itemType menu
					if(val == 1) { // if int entered
						iIn = stoi(input); // convert to int
						if(iIn > 0 && iIn < 4) { // validate range
							queryType = static_cast<ItemType>(iIn-1); // cast input to ItemType
							val = 0; // using val to count the number of results to save memory
							for(int i = 0; i < MENU_SIZE; i++) { // loop through available items
								if(menu[i].type == queryType && menu[i].qty > 0) { // if itemType equals search type and quantity is greater than 0
									results[val] = menu[i]; // reuse existing array to save memory
									val++; // increase result counter
								}
							}
							calcTotalBill(results, val, revenue); // calculate the bill for the valid items
							cout << "Total Revenue for " << ITEM_TYPES[iIn-1] << ": " << revenue.total << endl; // display result
							val = 1; // reset menu and exit loop
						} else {
							cout << "Not a valid option. Please try again.\n"; // prompt for retry
						}
					} else {
						cout << "Not a valid option. Please try again.\n"; // prompt for retry
					}
				}
				val = -1; // reset menu input
				break;
			case 6: // exit the program
				cout << "Closing"<< endl;
				running = false; // close the program
				break;
			default: // code should never be reached
				cout << "NOT AN OPTION. PLEASE TRY AGAIN.\n";
				break;
		}
		cout << endl << endl; // seperate next menu display from current one
	}
	
	return 0;
}

void searchItems(MenuItem menu[], MenuItem results[], string querry) {

}

void addItemToBill(vector<MenuItem> &bill, MenuItem mi) {
	bool newItem = true; // item is new by default
	for(int i = 0; i < bill.size(); i++) { // loop through all items
		if(bill[i].name == mi.name) { // if addItem is already on the list
			newItem = false; // it's not longer new
			bill[i].qty++; // increase quantity
			cout << "Increasing item quantity\n"; // prompt success
		}
	}
	if(newItem) { // if it is still new (not on list yet)
		mi.qty++; // increase quantity of local item (does carry over to menu)
		bill.push_back(mi); // add it to the bill
		cout << mi.name << " added to bill.\n"; // prompt success
	}

}

void calcTotalBill(MenuItem bill[], int size, Check &check) {
	check = {}; // clear out check
	for (int i = 0; i < size; i++) { // loop through the whole check
		check.total += (bill[i].cost * bill[i].qty); // calculate the total
	}
	check.tax = check.total * 0.07; // calc tax
	check.tip = check.total * 0.15; // calc tip
}

void printBill(MenuItem menu[], vector<MenuItem> &bill, bool finalSale) {
	Check check; // temp check
	calcTotalBill(&(bill[0]), static_cast<int>(bill.size()), check); // calc bill using temp check and vector
	for(int i = 0; i < bill.size(); i++) { // loop through the bill
		printItemInfo(bill[i], true); // print the item info
		if(finalSale) { // if the sale is final
			for(int j = 0; j < MENU_SIZE; j++) { // loop through menu items
				if(bill[i].name == menu[j].name) { // and increment qty for revenue
					menu[j].qty++;
				}
			}
		}
	}
	//diplay calculated costs
	cout << setprecision(2) <<  "Subtotal: $" << check.total << "\nTax: $" << check.tax << "\nTotal: $" << (check.total+check.tax) 
		 << "\nTotal /w 15% Tip: $" << (check.total+check.tax+check.tip) << endl;
	
	if(finalSale) { // if final, clear selection and thank user
		cout << "\n--------------------------------------------------\n";
		cout << "Thank You for your patronage. Have a nice day!";
		cout << "\n--------------------------------------------------\n";
		bill = {}; // reset bill
	}
}

void printItemInfoByType(MenuItem menu[], ItemType itemType) {
	MenuItem mi; // temp menuItem
	for(int i = 0; i < MENU_SIZE; i++) { // loop through menu
		if(menu[i].type == itemType) { // if the type is correct
			cout << i+1 << ": "; // print the item info
			printItemInfo(menu[i], false);
		}
	}
}

void printItemInfo(MenuItem mi, bool printQty) {
	cout << ITEM_TYPES[mi.type] << ": " << mi.name << "  Cost: " << mi.cost; // print the item info
	if(printQty) // and quantity if specified
		cout << "  Qty: " << mi.qty;
	cout << endl; 
}

int readMenuItemsFromFile(MenuItem menuItem[MENU_SIZE]) {
	ifstream file;
	file.open("taco_menu.txt");// open the file
	if(file.fail()) { // if it fails, return escape value
		file.close();
		return -1;
	} else {
		MenuItem i = {}; //otherwise, create temp variables
		int iter = 0;
		string itemName = "";
		int iType = 0;
		//and read in the data
		/*	name
			type(0-2) cost	*/
		while(getline(file, i.name) && file >> iType && file.ignore() && file >> i.cost && file.ignore()) {
			i.type = static_cast<ItemType>(iType); // cast the type number
			menuItem[iter] = i; // store the menu
			iter++; // increase iteration
		}
	}
	file.close(); // done reading, close stream
	return 0; // return success value
}

//prints the options in a numbered menu and the final string in the array as a user input prompt
//return 0 if the input is a string, 1 if a number, and -1 otherwise (both alpha and number, or special characters)
int printMenu(const string options[], int nOptions, string &input) {
	cout << endl << endl; //seperate from previous text stream
	for(int i = 0; i < nOptions; i++) { // print out the options
		cout << i+1 << ". " << options[i] << endl;
	}
	cout << options[nOptions] << ": "; // prompt for input
	getline(cin, input); // read input
	bool digit = true; // initialize validation variables
	bool alpha = true;
	for (int i = 0; i < input.length(); i++) {
		if(!(isdigit(input[i]) || input[i] == '-' || input[i] == '.')) { // check each character for digit and alpha
			digit = false;
		}
		if(!(isalpha(input[i]))) {
			alpha = false;
		}
	}
	if(digit && !alpha) // only digits
		return 1;
	else if(!digit && alpha) // only alphas
		return 0;
	return -1; // both or neither
}
