#include <iostream>
#include <iomanip>

#include "NumArray.h"

using namespace std;

int main() {
    cout << "Size of the array: ";
    int size = 0;
    cin >> size;
    NumArray num(size);
    float temp;
    for(int i = 0; i< size; i++) {
        cout << "Element " << i << ": ";
        cin >> temp;
        num.setItem(i, temp);
    }
    string lines = "------------------------\n";
    cout << lines;
    cout << setw((lines.length() / 2) + 5) << right << "Non-Sorted\n";
    cout << lines;
    num.printData();

    cout << lines;
    cout << setw((lines.length() / 2) + 3) << right << "Sorted\n";
    cout << lines;
    num.sortAscend();
    num.printData();

    cout << lines;
    cout << setw((lines.length() / 2) + 3) << right << "Copied\n";
    cout << lines;
    NumArray num2(num);
	cout << "num 2 before:"  << endl;
    num2.printData();
    num2.setItem(1, 8008);
	cout << "num 2 after:" << endl;
    num2.printData();
	cout << "num 1 after:" << endl;
    num.printData();
    return 0;
}
