#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int NAME_SIZE = 51;
const string mainMenu[] = {"Add a Flavour", "List Available Flavours", "Search Flavours", "Calculate Stock Value", "Clear Inventory Record", "Exit", "Please Select an Option"};

struct IceCream {
	char flavor[NAME_SIZE];
	float quantity;
	float price;
};

void displayFlavourData(fstream &); // reads the next IceCream data from the file and prints it on screen
void modifyItem(fstream &, bool); // modifies the next IceCream item in the file if bool if false, otherwise appends a new IceCream item
void listFlavours(fstream &); // reads all of the IceCream items from the file and prints the data on the screen
void displayStockValue(fstream &); // calculates the monetary value of all on hand IceCream and prints it to the screen
int dispPrompt(const string[], string &); // displays the contents of the array as a menu and prompts user for input stored in string
										  // returns value based on input type (0 => string, 1 => int, -1 => combo or failure)
void clearFile(fstream &); // clears the content of the file; destroys the stock record


int main() {
	
	fstream file("inventory.dat", ios::out | ios::app | ios::binary);
	if(file) {
		Logger.log(2, "Filed to open " + fileName + ". Closing...");
	}
	return 0;
}

void displayFlavourData(fstream &file) {

}

void modifyItem(fstream &file, bool newF) {

}

void listFlavours(fstream &) {

}

void displayStockValue(fstream &) {

}

int dispPrompt(const string[], string &) {

}

class Logger {
	enum LEVELS {
		DEBUG, WARNING, ERROR, SIZE
	};
	string const levelNames[] = {"DEBUG", "WARNING", "ERROR"};
	static void log(int warningLevel, string message) {
		cout << levelNames[warningLevel] << ": " << message << endl;
	}
}