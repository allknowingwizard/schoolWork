/*
	Adam Stammer
	CS 250 H, SDSU
	April 2nd, 2018
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

const int NAME_SIZE = 51;
const string mainMenu[] = {"Add a Flavour", "List Available Flavours", "Search Flavours", "Calculate Stock Value", "Modify Existing Item", "Clear Inventory Record", "Exit", "Please Select an Option"};
const string levelNames[] = {"RUNTIME", "DEBUG", "WARNING", "ERROR"};
const string IN_ERROR = "That is not a valid option. Please try again.\n";
const bool DEBUG = true;

struct IceCream {
	char flavour[NAME_SIZE];
	float quantity;
	float price;
};

enum MENU_OPTION {ADD=1, LIST, SEARCH, TOTAL, MODIFY, CLEAR, EXIT, COUNT_P1};

void displayFlavourData(IceCream &); // reads the next IceCream data from the file and prints it on screen
void modifyItem(fstream &, bool); // modifies the next IceCream item in the file if bool if false, otherwise appends a new IceCream item
int listFlavours(fstream &, bool); // reads all of the IceCream items from the file and prints the data on the screen, as solection list as specified
				   // returns the amount of flavours read
void displayStockValue(fstream &); // calculates the monetary value of all on hand IceCream and prints it to the screen
int displayPrompt(const string[], int, string &); // displays the contents of the array, of the given size, as a menu and prompts user for input stored in string
										  // returns value based on input type (0 => string, 1 => int, -1 => combo or failure)
void clearFile(fstream &, string); // clears the content of the file; destroys the stock record
void searchFlavours(fstream &); // prompts the user for an item search
void showStreamState(fstream &); // debugs the state of the given file stream


class Logger { // experimenting with "static classes", I may add file based logging to this later
	public:
		enum LEVEL {
			RUNTIME, DEBUG, WARNING, ERROR, SIZE
		};
		static const LEVEL threshold = ERROR;
		static void log(int warningLevel, string message) {
			if(warningLevel <= threshold && DEBUG)
				cout << levelNames[warningLevel] << ": " << message << endl;
		}
	private:
		Logger() {} // make it uninitializable (static) by hiding the constructor
};

int main() {
	string fileName = "ice_cream.dat";
	fstream file(fileName.c_str(), ios::in | ios::binary);
	if(!file) {
		file.close();
		file.open(fileName.c_str(), ios::out | ios::binary);
	}
	file.close();
	file.open(fileName.c_str(), ios::out | ios::in | ios::binary);


	if(!file) {
		Logger::log(Logger::ERROR, "Filed to open " + fileName + ". Closing...");
		return -1;
	}
	string input = "";
	int value = -1;
	while(value != 1) {// until the user enters a number
		value = displayPrompt(mainMenu, 7, input);
		if(value == 1 && stoi(input) < 8 && stoi(input) > 0) { // valid integer input
			switch(stoi(input)) {
				case ADD: // add a flavour
					modifyItem(file, true);
					break;
				case LIST: // list available flavours
					listFlavours(file, false);
					break;
				case SEARCH: // search flavours
					searchFlavours(file);
					break;
				case TOTAL: // calculate stock values
					displayStockValue(file);
					break;
				case MODIFY:
					modifyItem(file, false);
					break;
				case CLEAR: // clear inventory record
					clearFile(file, fileName);
					break;
				case EXIT: // exit
					cout << "Have a nice day!" << endl;
					file.close();
					return 0;
					break;
			}
			value = -5;
		} else { // invalid option
			cout << IN_ERROR;
		}
		value = -5;
	}

	return 0;
}

void displayFlavourData(IceCream &tempFlav) {
		cout << "--------------------------------------------------------\n"; // and print the info
		cout << left << setw(25) << "Flavour: " << tempFlav.flavour << endl;
		cout << left << setw(25) << "Quantity Available: " << tempFlav.quantity << endl;
		cout << left << setw(25) << "Price: $" << fixed << setprecision(2) << tempFlav.price << endl;
}

void modifyItem(fstream &file, bool newF) {
	//print flavour list
	string choice[] = {"Please Selected a Flavour Number"};
	string input;
	int value = -5;
	if(!newF) {
		int count = listFlavours(file, true);
		if(count > 0) {
			while(value != 1) {
				value = displayPrompt(choice, 0, input);
				if(value == 1) {
					file.seekg((stoi(input)-1) * sizeof(IceCream), ios::beg);
					file.seekp((stoi(input)-1) * sizeof(IceCream), ios::beg);
				} else {
					cout << IN_ERROR;
				}
			}
		} else {
			cout << "No existing files. Adding new entry." << endl;
			file.seekp(0, ios::end);
			newF = true;
		}
	} else {
		file.seekp(0, ios::end);
	}
	file.clear();
	IceCream tempFlav = {0};
	cout << "Please Enter the Information." << endl;
	if(!newF) {
		cout << "Return to leave unchanged." << endl;
		file.read(reinterpret_cast<char*>(&tempFlav), sizeof(IceCream));///////////////////////////////////////////////////////////////
		file.seekg(-sizeof(IceCream), ios::cur); // back up one item (the one you just read)
	}
	string flavour[] = {"Flavour Name"};
	string quantity[] = {"Quantity (lbs.)"};
	string price[] = {"Price"};
	value = -5;
	while(!(value == 0 || value == -2)) { // wait for string or empty input
		value = displayPrompt(flavour, 0, input);
		if(value == 0) { //  change the name
			strcpy(tempFlav.flavour, input.c_str());
		}
	}
	value = -5; // reset for continued input
	while(!(value == 1 || value == -2)) { // wait for int or empty input
		value = displayPrompt(quantity, 0, input);
		if(value == 1) { // change the qty
			tempFlav.quantity = stof(input);
		}
	}
	value = -5; // reset for continued input
	while(!(value == 1 || value == -2)) { // wait for int or empty input
		value = displayPrompt(price, 0, input);
		if(value == 1) { // change the price
			tempFlav.price = stof(input);
		}
	}
	value = -5; // reset for continued input
	
	file.write(reinterpret_cast<char *>(&tempFlav), sizeof(IceCream));
}

int listFlavours(fstream &file, bool selList) {
	file.clear();
	file.seekg(0, ios::beg); // start reading from the beginning
	showStreamState(file);
	IceCream tempFlav = {"TestFlavour", 0, 0};
	int iter = 0;
	while(file.read(reinterpret_cast<char *>(&tempFlav), sizeof(IceCream))) { // read all of the flavor data
		if(!selList) {
			displayFlavourData(tempFlav);
		} else {
			cout << right << setw(3) << (iter+1) << ": " << tempFlav.flavour << endl;
		}
		iter++;
	}
	return iter;
}

void displayStockValue(fstream &file) {
	file.clear();
	file.seekg(0, ios::beg); // reset to the beginning of the file
	IceCream temp = {"", 0, 0};
	float stockValue = 0;
	float flavourValue = 0;
	while(file.read(reinterpret_cast<char *>(&temp), sizeof(IceCream))) {
		flavourValue = (temp.price * temp.quantity);
		cout << temp.flavour << ": $" << setprecision(2) << flavourValue << endl;
		stockValue += flavourValue;
	}
	cout << "Total: $" << setprecision(2) << stockValue << endl;
	
}

int displayPrompt(const string options[], int nOptions, string &input) {
	cout << endl << endl; //seperate from previous text stream
	for(int i = 0; i < nOptions; i++) { // print out the options
		cout << right << setw(2) << i+1 << ". " << options[i] << endl;
	}
	cout << options[nOptions] << ": "; // prompt for input
	getline(cin, input); // read input
	if(input.length() == 0)
		return -2;
	bool digit = true; // initialize validation variables
	bool alpha = true;
	for (int i = 0; i < input.length(); i++) {
		if(!(isdigit(input[i]) || input[i] == '-' || input[i] == '.')) { // check each character for digit and alpha
			digit = false;
		}
		if(!(isalpha(input[i]) || input[i] == ' ' || input[i] == '.')) {
			alpha = false;
		}
	}
	if(digit && !alpha) // only digits
		return 1;
	else if(!digit && alpha) // only alphas
		return 0;
	return -1; // both or neither
}

void searchFlavours(fstream &file) {
	file.clear();
	string promptQuery[] = {"Enter a search term (-1 to exit)"};
	int val = -5;
	string input = "";
	IceCream tempFlav = {0};
	file.seekg(0, ios::beg);
	bool resultFound = false;
	bool c1, c2 = false;
	char ch1[NAME_SIZE];
	char ch2[NAME_SIZE];
	while (val != 0) {
		val = displayPrompt(promptQuery, 0, input);
		if(val == 0) {
			while(file.read(reinterpret_cast<char *>(&tempFlav), sizeof(IceCream))) {
				int i = 0;
				strcpy(ch1, tempFlav.flavour);
				strcpy(ch2, input.c_str());
				c1 = c2 = false;
				while(!(c1 || c2)) {
					if(!c1) {
						if(ch1[i] == '\0')
							c1 = true;
						ch1[i] = tolower(ch1[i]);
					}
					if(!c2) {
						if(ch2[i] == '\0')
							c2 = true;
						ch2[i] = tolower(ch2[i]);
					}
					i++;
				}
				
				cout << "ch1: " << ch1 << endl;
				cout << "ch2: " << ch2 << endl;
				
				if(strstr(ch1, ch2) != nullptr) {
					displayFlavourData(tempFlav);
					resultFound = true;
				}
			}
			if(!resultFound) {
				cout << "No results found matching that query.\n\n";
				val = -5; // reset the loop to ask for more input
			}
		} else if(val == 1) {
			if(stoi(input) == -1) { // -1 has been entered
				cout << "Returning to main menu.\n\n";
			} else { // not a valid number
				cout << IN_ERROR; // prompt error
				val = -5; // reset loop
			}
		} else {
			cout << IN_ERROR; // wrong data type
		}
	}
}

void showStreamState(fstream &file) {
	cout << "EOF: " << file.eof() << endl;
	cout << "Good: " << file.good() << endl;
	cout << "fail: " << file.fail() << endl;
	cout << "bad: " << file.bad() << endl;
}

void clearFile(fstream &file, string fileName) {
	file.clear();
	file.close();
	file.open(fileName.c_str(), ios::out | ios::binary);
	file.close();
	file.open(fileName.c_str(), ios::out | ios::in | ios::app | ios::binary);
	if(DEBUG)
		showStreamState(file);
	file.clear();
}
