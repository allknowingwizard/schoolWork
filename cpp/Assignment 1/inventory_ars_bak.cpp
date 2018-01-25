#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void sortArray(int array[], int size);
void displayPartInfo(int, int, int);
int readInputData(int[], float[], int[]);
void swap(float[], int, int);
void swap(int[], int, int);
void bubbleSort(int[], float[], int[], int);
void listPartsData(int[], float[], int[], int);
int binarySearch(int[], int, int, int);

const int MAX_DATA_SIZE = 100;

int main()
{
    //declare parllel storage arrays
    int partNumbers[MAX_DATA_SIZE];
    float partCosts[MAX_DATA_SIZE];
    int partQuantities[MAX_DATA_SIZE];

    // read and store data
    int size = readInputData(partNumbers, partCosts, partQuantities);

    // sort data
    bubbleSort(partNumbers, partCosts, partQuantities, size);

    // list out sorted data
    listPartsData(partNumbers, partCosts, partQuantities, size);
    
    //error callback
    string searchType = "linear";
    loopStart:
        int query;
        int optionQuery;
        do {
            cout << "Options: \n" << right << setw(20) << "1) Search " << searchType << ")\n";
            cout << setw(20) << "2) Linear Search (Multiple Results)\n" << setw(20) << "3) Binary Search (Single Result)\n";
            cout << setw(20) << "4) Exit\n";
            //ask user for query
            cout << "\n\nSelect An Option Above: ";
            cin >> optionQuery;
            switch(optionQuery) {
                //exit when the escape value is given
                case 1:
                    if(query == -1)
                        break;
                    //throw an error if the query is negative
                    if(query < 0) {
                        cout << "Query entered is invalid. Negatives not allowed.\n";
                        goto loopStart;
                    } else {
                        //search partNumbers for query
                        int queryIndex = binarySearch(partNumbers, 0, size, query);
                        //if nothing is found, inform the user and restart the loop
                        if(queryIndex == -1) {
                            cout << "NO MATCHING RESULTS\n";
                            goto loopStart;
                        } else {
                            //if something is found display it on screen
                            cout << "FOUND RESULT\n";

                            //create parallel arrays of only one item to reuse preexisting function
                            int a[1] = {partNumbers[queryIndex]};
                            float b[1] = {partCosts[queryIndex]};
                            int c[1] = {partQuantities[queryIndex]};
                            listPartsData(a, b, c, 1);
                        }
                    }
                    break;
                case 2:
                    cout << "Switching to a Linear Search algorithm capabable of finding multiple results...\n";
                    searchType = "linear";
                    goto loopStart;
                    break;
                case 3:
                    cout << "Switching to a Binary Search algorithm capable of finding only one result...\n";
                    searchType = "binary";
                    goto loopStart;
                    break;
            }
        } while (optionQuery != 4); // as long as the exit query isn't called


    return 0;
}

//lists out the part data into labled columns
void listPartsData(int partNumbers[], float partCosts[], int partQuantities[], int size) {
    // displays column lables
    cout << right << setw(8) << "Part #" << setw(8) << "Cost" << setw(8) << "Qty" << endl;
    for(int i = 0; i < size; i++) {
        //lists the part data for each stored part
        displayPartInfo(partNumbers[i], partCosts[i], partQuantities[i]);
    }
}

//reads input data from parts.txt and returns the size of part data
int readInputData(int partNumbers[], float partCosts[], int partQuantities[]) {
    //open parts.txt
    ifstream inFile;
    inFile.open("parts.txt");
    //if the file doesn't open, call an error and exit
    if(!inFile.is_open()) {
        cout << "Failed to open \"parts.txt\"! Closing...";
        exit(0);
    }
    int size = 0;
    //read in all of the data available and store it in the parallel arrays
    while (size < MAX_DATA_SIZE && inFile >> partNumbers[size] >> partCosts[size] >> partQuantities[size]) {
        size++;
    }
    //close file stream
    inFile.close();
    return size;
}

//displays the information of a part on the screen in columns
void displayPartInfo(int partNumber, int partCost, int partQty) {
    cout << right << setw(8) << partNumber << setw(8) << partCost << setw(8) << partQty << endl;
}

//bubble sort of three arrays based on partNumbers
void bubbleSort(int partNumbers[], float partCosts[], int partQuantities[], int size)
{
    //declaration of temp variables
    bool doSwap;
    int temp1;
    int temp2;
    int temp3;
    do
    {
        //resets loop continuation
        doSwap = false;
        //loops through entire array
        for (int i = 0; i < size - 1; i++)
        {   
            //if the lower index has a higher value than the higher index
            if (partNumbers[i] > partNumbers[i+1])
            {   
                // swaps the two variables in each array
                swap(partNumbers, i, i+1);
                swap(partCosts, i, i+1);
                swap(partQuantities, i, i+1);
                //ensures the loop continues
                doSwap = true;
            }
        }
    }
    while (doSwap); // continue as long as there is still something to swap
}

//recurrsive binary search that returns the index of the query match
int binarySearch(int partNumbers[], int start, int end, int query) {
    //as long as the scope is greater than 0 (there is still something to be searched)
    if (end >= start)
        {
            //find the middle of the array
            int middle = start + (end - start)/2;
    
            // if the middle is the query, return it
            if (partNumbers[middle] == query)  
                return middle;
    
            // if the query is lower than the middle
            if (partNumbers[middle] > query) 
                // start a new binary search in the lower half of the current scope
                return binarySearch(partNumbers, start, middle-1, query);
    
            //if the query is not lower than the middle
            return binarySearch(partNumbers, middle+1, end, query);
        }
    //returns -1 if query is not present in array
    return -1;
}

//swaps two elements within an integer array
void swap(int parts[], int indexOne, int indexTwo) {
    //stores first indexed value in temp
    int temp = parts[indexOne];
    //stores second index value in the first index
    parts[indexOne] = parts[indexTwo];
    //sets the second index value to temp
    parts[indexTwo] = temp;
}
//swaps two elements within a float array
void swap(float parts[], int indexOne, int indexTwo) {
    // see swap(int[], int, int) for comments
    int temp = parts[indexOne];
    parts[indexOne] = parts[indexTwo];
    parts[indexTwo] = temp;
}
