#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int NAME_SIZE = 51;
const string mainMenu[] = {"Add a Flavour", "List Available Flavours", "Search Flavours", "Calculate Stock Value", "Clear Inventory Record", "Exit", "Please Select an Option"};
const string levelNames[] = {"DEBUG", "WARNING", "ERROR"};
const string IN_ERROR = "That is not a valid option. Please try again.\n";

struct IceCream {
	char flavour[NAME_SIZE];
	float quantity;
	float price;
};

void displayFlavourData(fstream &); // reads the next IceCream data from the file and prints it on screen
void modifyItem(fstream &, bool); // modifies the next IceCream item in the file if bool if false, otherwise appends a new IceCream item
void listFlavours(fstream &); // reads all of the IceCream items from the file and prints the data on the screen
void displayStockValue(fstream &); // calculates the monetary value of all on hand IceCream and prints it to the screen
int displayPrompt(const string[], int, string &); // displays the contents of the array, of the given size, as a menu and prompts user for input stored in string
										  // returns value based on input type (0 => string, 1 => int, -1 => combo or failure)
void clearFile(fstream &); // clears the content of the file; destroys the stock record


class Logger { // experimenting with "static classes", I may add file based logging to this later
	public:
		enum LEVEL {
			DEBUG, WARNING, ERROR, SIZE
		};
		static const LEVEL threshold = ERROR;
		static void log(int warningLevel, string message) {
			if(warningLevel <= threshold)
				cout << levelNames[warningLevel] << ": " << message << endl;
		}
	private:
		Logger() {} // make it uninitializable (static) by hiding the constructor
};

int main() {
	string fileName = "inventory.dat";
	fstream file("inventory.dat", ios::out | ios::app | ios::binary);
	if(!file) {
		Logger::log(Logger::ERROR, "Filed to open " + fileName + ". Closing...");
		return -1;
	}
	string input = "";
	int value = -1;
	while(value != 1) {// until the user enters a number
		value = displayPrompt(mainMenu, 6, input);
		if(value == 1 && value < 6 && value > 0) { // valid integer input
			switch(value) {
				case 1: // add a flavour
					modifyItem(file, true);
					break;
				case 2: // list available flavours

					break;
				case 3: // search flavours

					break;
				case 4: // calculate stock values

					break;
				case 5: // clear inventory record

					break;
				case 6: // exit
					cout << "Have a nice day!" << endl;
					return 0;
					break;
			}
		} else { // invalid option
			Logger::log(Logger::ERROR, "Invalid Option: " + value);
			cout << IN_ERROR;
		}
	}

	return 0;
}

void displayFlavourData(fstream &file) {
	IceCream tempFlav;
	file.read(reinterpret_cast<char*>(&file), sizeof(IceCream));
	if(!file.fail()) {
		cout << "--------------------------------------------------------\n"; // and print the info
		cout << "Flavour: " << tempFlav.flavour << endl;
		cout << "Quantity Available: " << tempFlav.quantity << endl;
		cout << "Price: $" << setprecision(2) << tempFlav.price << endl;
	}
}

void modifyItem(fstream &file, bool newF) {
	cout << "Please Enter the Information.";
	IceCream tempFlav = {};
	if(!newF) {
		cout << "Leave empty to remain unchanged.";
		file.read(reinterpret_cast<char*>(&tempFlav), sizeof(IceCream));///////////////////////////////////////////////////////////////
		file.seekg(file.tellg(), ios::beg); // back up one item (the one you just read)
	}
	cout << endl;
	string flavour[] = {"Flavour Name"};
	string input = "";
	int value = -1;
	while(!(value == 0 || value == -2)) { // wait for string or empty input
		value = displayPrompt(flavour, 0, input);
		if(value == -2) { // don't change the name
			
		}
	}
}

void listFlavours(fstream &file) {
	file.seekg(0L, ios::beg); // start reading from the beginning
	while(!(file.eof())) { // read all of the flavor data
		displayFlavourData(file);
	}
}

void displayStockValue(fstream &) {

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


