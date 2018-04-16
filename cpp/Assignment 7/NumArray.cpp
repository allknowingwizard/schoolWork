#include <iostream>
#include <iomanip>
#include "NumArray.h"

using namespace std;

const string BOOLS[] = {"false", "true"};

NumArray::NumArray(int size) {
    iSize = size;
    bSorted = false;
    pNumbers = new int[iSize];
}
NumArray::NumArray(NumArray &num) {
    iSize = num.size();
    bSorted = num.sorted();
    pNumbers = new int[iSize];
    for(int i = 0; i < iSize; i++) {
        pNumbers[i] = num.getItem(i);
    }
}

NumArray::~NumArray() {
    delete pNumbers;
}

float NumArray::findAvg() {
    float sum = 0;
    for(int i = 0; i < size(); i++) {
        sum += pNumbers[i];
    }
    return (sum / size());
}

void NumArray::sortAscend() {
    for(int i = 0; i < size() - 1; i++) {
        int smallIndex = i;
        for(int j = i+1; j < iSize; j++) {
            if(pNumbers[j] < pNumbers[smallIndex])
                smallIndex = j;
        }
        float temp = pNumbers[i];
        pNumbers[i] = pNumbers[smallIndex];
        pNumbers[smallIndex] = temp;
    }
    bSorted = true;
}

float NumArray::findMedian() {
    if(!sorted())
        sortAscend();
    int mid = (size() / 2) - 1;
    if(size() % 2 == 1) // it is odd, there is a middle index
        return pNumbers[mid];
    float sum = 0;
    sum += pNumbers[mid] + pNumbers[mid + 1];
    return sum / 2;
}

void NumArray::printData() {
    cout << "Array Size: " << iSize << endl;
    cout << "Is Sorted: " << BOOLS[bSorted] << endl;
    if(sorted()) {
        cout << "Average: " << findAvg() << endl;
        cout << "Median: " << findMedian() << endl;
    }
    cout << "\tValues" << endl;
    cout << "\t------" << endl;
    for(int i = 0; i < iSize; i++) {
        cout << "\t   " << pNumbers[i] << endl;
    }
}
