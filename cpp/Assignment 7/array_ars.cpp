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
    num2.printData();

    return 0;
}