#include <iostream>
#include <fstream>
#include <iomanip>
#define arrayDefine int[] partNumbers, float[] partCosts, int[] partQuantities
#define arrayCall partNumbers, partCosts, partQuantities

using namespace std;

void sortArray(int array[], int size);
void displayPartInfo(int, int, int);
void readInputData(int[], float[], int[]);

const int MAX_DATA_SIZE = 100;
bool fileOpen = false;
int size = 0;


int main()
{
    int partNumbers[MAX_DATA_SIZE];
    float partCosts[MAX_DATA_SIZE];
    int partQuantities[MAX_DATA_SIZE];
    readInputData(arrayCall);

    //displayPartInfo(276, 102.45, 3);

    //sortArray(a, asize);

    //printArray(a, asize);

    return 0;
}

void readInputData(int partNumbers[], float partCosts[], int partQuantities[]) {
    ifstream inFile;
    if(inFile.open("files.txt")) {
        fileOpen = true;
    } else {
        cout << "WARNING: Error opening files.txt!!!";
        inFile.close();

    }




}

void displayPartInfo(int partNumber, int partCost, int partQty) {
    cout << right << setw(6) << partNumber << setw(6) << partCost << setw(6) << partQty;
}

void bubbleSort(int a[], int asize)
{
    bool doSwap;
    int temp;
    do
    {
        doSwap = false;
        for (int i = 0; i < asize - 1; i++)
        {
            if (a[i] > a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                doSwap = true;
            }
        }
    }
    while (doSwap);
}
