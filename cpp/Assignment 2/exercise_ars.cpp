/*
    Adam Stammer
    January 30th, 2018, 11:00am

    Exercise Calculation Program:
            Usage: exercise.exe [option]
                "--log"..............initializes logging to the screen
                "--file [filename]"......sets the file name to file (relative to program location)
*/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// constants for array size
const int DAYS = 7;
const int PEOPLE = 5;

string daySuffix(int); // returns the suffix of the day based on index (index 1 is the second day -> returns "nd" from "2nd")
void calcTotals(int[][DAYS], int[]); // calculates the totals per person and puts them in an int[]
void readData(int[][DAYS], string); //reads the input data from ex_data.txt
void errorCheck(int [][DAYS]); // check the input data for errors and zero any out
void calcMaxDay(int[][DAYS], int[]); // calculates the peak exercise day for each person, index of day stores in int[]
void calcAvgs(int[][DAYS], int[]); // calculates the average exercise per day per person, index of avg stored in int[]
int calcTotal(int[]); //returns the total exercise done by all of the people throughout the week
int calcMaxDayPerPerson(int[]); //calculates the total exercise for the week for one person and returns it
int calcAvgPerDay(int[]); // calculates the avg exercise per person on any one day and returns it
void outputCalculations(int[][DAYS], int[], int[], int[], int); // prints to the screen the peak exercise day and value for each person,
                                                                // the average minutes of exercise per day for the group,
                                                                // the relative contribution to the total,
                                                                // and the total minutes of exercise for the week
void LOG(int, string);
//turn log on or off
static bool log = false;
//prints out a message of the given priority
void LOG(int priority, string logMes) {
    if(log) {
        cout << "-----------------------" << endl;
        if(priority == 1)
            cout << "LOG: ";
        else if(priority == 2)
            cout << "WARNING(1): ";
        else if(priority == 3)
            cout << "WARNING(2): ";
        else if(priority == 4)
            cout << "WARNING(3): ";
        cout << logMes;
        cout << endl << "-----------------------" << endl;
    }
}                                                          

int main(int argc, char** argv/*could be: --- char *argv[] ---  */) {
    //default filename 
    string file = "ex_data.txt";
    //if there are arguments
    if(argc > 1) {
        //loop through them all
        for(int i = 1; i < argc; i++) {
            string arg = (string) argv[i];
            //turn on logging
            if(arg == "--log") {
                log = true;
                LOG(1, "LOGGING INITIALIZED");
            } else if(arg == "--file" || arg == "-f") {// change the filename
                if(argc >= i+2 && ((string) argv[i+1])[0] != '-') {
                    file = string(argv[i+1]);
                    i++; // skip the next argument becuase it is the file name
                } else {
                    //display usage
                    cout << "Usage: exercise.exe --file [filename]";
                    LOG(4, "FILE NAME NOT SET...TERMINATING");
                    return 1;
                }
            } else {
                //if the arguments mean nothing, print out the usage
                cout << "Usage: exercise [options]\n    \"--log\"       turns on debug logging\n"
                        "   \"--file [file]\"       sets the active data file (default: ex_data.txt)\n";
                return 1;
            }
        }
    }
    int exData[PEOPLE][DAYS];
    //read data from file into exData
    readData(exData, file);
    //check the read exData for errors and correct
    errorCheck(exData);
    LOG(1, "DATA READ AND ERROR CHECKED");
    int maxDays[DAYS];
    //calculate the peak exercise day for each person in exData and store the indexes into maxDays
    calcMaxDay(exData, maxDays);
    LOG(1, "MAX DAYS CALCULATED");
    int dayAvgs[DAYS];
    //calculate the averages for each person within exData and store it in dayAvgs
    calcAvgs(exData, dayAvgs);
    LOG(1, "AVERAGES CALCULATED");
    int totals[PEOPLE] = {0};
    //calculate the totals for each person and store them in totals
    calcTotals(exData, totals);
    LOG(1, "TOTALS CALCULATED");
    //output all of the data calculated and calculate and output the overall total along with each persons
    //contribuition to the total
    outputCalculations(exData, maxDays, dayAvgs, totals, calcTotal(totals));
    LOG(1, "DONE....PROGRAM TERMINATING");
    //exit program
    return 0;
}

void readData(int exData[][DAYS], string file) {
    ifstream inFile;
    //open the input file stream with the given filename
    inFile.open(file.c_str());
    for(int i = 0; i < PEOPLE; i++) {
        for (int j =0 ; j < DAYS; j++) {
            //loop through and read all of the ex data from the file and store it in exdata
            inFile >> exData[i][j];
        }
    }
}

void errorCheck(int  exData[][DAYS]) {
    for(int i = 0; i < PEOPLE; i++) {
        for (int j = 0; j < DAYS; j++) {
            //loop through all of exData and check to see if it is greater than zero and less than 250
            //if not, set it to zero
            if(exData[i][j] > 250 || exData[i][j] < 0)
                exData[i][j] = 0;
                //LOG(3, "Zeroing out " + i + ", " + j);
        }
    }
}

void calcMaxDay(int exData[][DAYS], int maxDays[]) {
    for(int i = 0; i < PEOPLE; i++) {
        //loop through all of exData and fill maxData with the returned index found by calcMaxDayPerPerson
        maxDays[i] = calcMaxDayPerPerson(exData[i]);
    }
}

void calcAvgs(int exData[][DAYS], int dayAvgs[]) {
    for(int i =0 ; i < PEOPLE; i++) {
        //loop through all of exData and fill dayAvgs with the averages found by calcAvgPerDay
        dayAvgs[i] = calcAvgPerDay(exData[i]);
    }
}

void calcTotals(int exData[][DAYS], int totals[]) {
    for(int i = 0; i < PEOPLE; i++) {
        for(int j = 0; j < DAYS; j++) {
            //loop through all of exData and fill totals with the row (person) totals
            totals[i] += exData[i][j];
        }
    }
}

int calcTotal(int totals[]) {
    int sum = 0;
    for(int i = 0; i < PEOPLE; i++) {
        sum += totals[i];
        //loop through all of totals and add it all to a sum
    }
    //return the total found
    return sum;
}

int calcMaxDayPerPerson(int exDataP[]) {
    int maxIndex = 0;
    for (int i = 0; i < DAYS; i++) {
        if(exDataP[i] > exDataP[maxIndex])
            maxIndex = i;
            //loop through all of exDataP and if the current value is greater than the value
            //of the current stored value, replace the stored index with the new one
    }
    //return the maxIndex found
    return maxIndex;
}

int calcAvgPerDay(int exDataP[]) {
    int sum = 0;
    for (int i =0 ; i < DAYS; i++) {
        //loop through all of exDataP and add the values to sum
        sum += exDataP[i];
    }
    //return the found sum divided by the days, which is the average
    return sum / DAYS;
}

void outputCalculations(int exData[][DAYS], int maxDays[], int dayAvgs[], int totals[], int total) {
    for (int i = 0; i < PEOPLE; i++) {
        //loop through all of the people and print out the found statistics in an ordered manner
        cout << "Person " << i+1 << ":"<< endl;
        cout << "   " << "Performed the most exercise on the " << maxDays[i]+1 << daySuffix(maxDays[i]) << " day with " << exData[i][maxDays[i]] << " minutes." << endl;
        cout << "   " << "Had an average exercise of " << dayAvgs[i] << " minutes per day.\n";
        cout << "   " << "Contributed "  << /*calculate the percentage contributed*/((float) totals[i] / (float) total) * 100.0 << "% to the group total.\n";
    }
}

string daySuffix(int dayIndex) {
    int day = dayIndex+1;
    //default the suffix to th, because it is the most common
    string suffix = "th";
    //if the day suffix needs to change, change it and then return it
    if(day == 1)
        suffix = "st";
    if(day == 2)
        suffix = "nd";
    if(day == 3)
        suffix = "rd";
    //since the max day is 7 we only need to check the first 3, the last 4 all end in the default "th"
    return suffix;
}
