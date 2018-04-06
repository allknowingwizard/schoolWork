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
void listFlavours(fstream &); // reads all of the IceCream items from the file and prints the data on the screen
void displayStockValue(fstream &); // calculates the monetary value of all on hand IceCream and prints it to the screen
int displayPrompt(const string[], int, string &); // displays the contents of the array, of the given size, as a menu and prompts user for input stored in string
										  // returns value based on input type (0 => string, 1 => int, -1 => combo or failure)
void clearFile(fstream &, string); // clears the content of the file; destroys the stock record
void searchFlavours(fstream &); // prompts the user for an item search
void showStreamState(fstream &);


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
					listFlavours(file);
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
		cout << "Flavour: " << tempFlav.flavour << endl;
		cout << "Quantity Available: " << tempFlav.quantity << endl;
		cout << "Price: $" << fixed << setprecision(2) << tempFlav.price << endl;
}

void modifyItem(fstream &file, bool newF) {
	cout << "Please Enter the Information.";
	file.seekp(0, ios::beg);
	file.seekg(0, ios::beg);
	IceCream tempFlav = {"", 0, 0};
	if(!newF) {
		cout << "Leave empty to remain unchanged.";
		file.read(reinterpret_cast<char*>(&tempFlav), sizeof(IceCream));///////////////////////////////////////////////////////////////
		file.seekg(-sizeof(IceCream), ios::cur); // back up one item (the one you just read)
	} else {
		//file.seekg(0L, ios::end);
	}
	cout << endl;
	string flavour[] = {"Flavour Name"};
	string quantity[] = {"Quantity (lbs.)"};
	string price[] = {"Price"};
	string input = "";
	int value = -1;
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
//	if(tempFlav != {"", 0, 0}) { // make sure there is information
		file.write(reinterpret_cast<char *>(&tempFlav), sizeof(IceCream));
//	}
}

void listFlavours(fstream &file) {
	file.seekg(0, ios::beg); // start reading from the beginning
	showStreamState(file);
	IceCream tempFlav = {"TestFlavour", 0, 0};
	while(file.read(reinterpret_cast<char *>(&tempFlav), sizeof(IceCream))) { // read all of the flavor data
		displayFlavourData(tempFlav);
	}
	file.clear();
}

void displayStockValue(fstream &file) {
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

void searchFlavours(fstream &file) {
/*
	string promptQuery[] = {"Enter a search term"};
	int val = -5;
	string input = "";
	while (val != 0) {
		val = displayPrompt(promptQuery, 0, input);
		if(val == 0) {
			while
		} else {
			cout << IN_ERROR; // wrong data type
		}
	}
*/
}

void showStreamState(fstream &file) {
	cout << "EOF: " << file.eof() << endl;
	cout << "Good: " << file.good() << endl;
	cout << "fail: " << file.fail() << endl;
	cout << "bad: " << file.bad() << endl;
}

void clearFile(fstream &file, string fileName) {
	file.close();
	file.open(fileName.c_str(), ios::out | ios::binary);
	file.close();
	file.open(fileName.c_str(), ios::out | ios::in | ios::app | ios::binary);
	if(DEBUG)
		showStreamState(file);
}
