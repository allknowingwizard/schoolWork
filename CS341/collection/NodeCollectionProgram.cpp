/*
    Adam Stammer    
    CS250H
    Assignment 8 & 9
    Linked List Storing Characters
*/

#include <iostream>
#include <iomanip>
// #include "NodeCollection.h"
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void readData(ifstream &ifstr, vector<int> &v) {
    ifstr.open("input.dat");
    if(!ifstr) {
        cout << "Unable to open file\n";
        exit(1);
    }
    int inVal = -1;
    while ((ifstr >> inVal)) {
        v.push_back(inVal);
    }
}

void sortData(vector<int> data, vector<int> &dataA, vector<int> &dataB) {
    // int i, j, min_idx;
 
    // // One by one move boundary of unsorted subarray
    // for (i = 0; i < data.size()-1; i++)
    // {
    //     // Find the minimum element in unsorted array
    //     min_idx = i;
    //     for (j = i+1; j < data.size(); j++)
    //       if (data[j] < data[min_idx])
    //         min_idx = j;
 
    //     // Swap the found minimum element with the first element
    //     swap(&arr[min_idx], &arr[i]);
    // }
}

void printData(vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << '\n';
    }
}

void printMenu() {
    cout << "1. Display Raw Data\n";
    cout << "2. Display Ascending\n";
    cout << "3. Display Descending\n";
    cout << "4. Display Mean and Median\n";
    cout << "5. Quit\n";
}
void copyVector(vector<int> &v, vector<int> &w) {
    for(int i = 0; i < v.size(); i++) {
        w.push_back(v[i]);
    }
}
void printMenMed(vector<int> v) {
    
}
int main() {
    ifstream inFile;
    vector<int> data, dataA, dataD;
    readData(inFile, data);
    copyVector(data, dataA);
    copyVector(data, dataD);
    sort(dataA.begin(), dataA.end());
    for(int i = data.size(); i>0; i--) {
        dataA.push_back(dataD[i]);
    }
    int choice = -1;
    while(choice != 5) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                printData(data);
            break;
            case 2:
                printData(dataA);
            break;
            case 3:
                printData(dataD);
            break;
            case 4:
                printMenMed(data);
            break;
            case 5:
                exit(0);
            default:
                cout << "That is not a valid option.\n";
        }
    }
    

    return 0;
}