/*
    Adam Stammer
    January 30th, 2018, 11:00am

    Exercise Calculation Program:
            Usage: exercise.exe [option]
                --log %initializes logging to the screen
                --file [file] -> sets the file name to file
*/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int DAYS = 7;
const int PEOPLE = 5;

string daySuffix(int); // returns the suffix of the day based on index (index 1 is the second day -> returns "nd" from "2nd")
void calcTotals(int[][DAYS], int[]); // calculates the totals per person and puts them in an int[]
void readData(int[][DAYS], string); //reads the input data from ex_data.txt
void errorCheck(int[][DAYS]); // check the input data for errors and zero any out
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
static bool log = false;
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

int main(int argc, char** argv) {
    string file = "ex_data.txt";
    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            string arg = (string) argv[i];
            if(arg == "--log") {
                log = true;
                LOG(1, "LOGGING INITIALIZED");
            } else if(arg == "--file" || arg == "-f") {
                if(argc >= i+2 && ((string) argv[i+1])[0] != '-') {
                    file = string(argv[i+1]);
                    i++;
                } else {
                    cout << "Usage: exercise.exe --file [filename]";
                    LOG(4, "FILE NAME NOT SET...TERMINATING");
                    return 1;
                }
            }
        }
    }
    int exData[PEOPLE][DAYS];
    readData(exData, file);
    errorCheck(exData);
    LOG(1, "DATA READ AND ERROR CHECKED");
    int maxDays[DAYS];
    calcMaxDay(exData, maxDays);
    LOG(1, "MAX DAYS CALCULATED");
    int dayAvgs[DAYS];
    calcAvgs(exData, dayAvgs);
    LOG(1, "AVERAGES CALCULATED");
    int totals[PEOPLE] = {0};
    calcTotals(exData, totals);
    LOG(1, "TOTALS CALCULATED");
    outputCalculations(exData, maxDays, dayAvgs, totals, calcTotal(totals));
    LOG(1, "DONE....PROGRAM TERMINATING");
    return 0;
}

void readData(int exData[][DAYS], string file) {
    ifstream inFile;
    inFile.open(file);
    //LOG(1, "Reading data");
    for(int i = 0; i < PEOPLE; i++) {
        for (int j =0 ; j < DAYS; j++) {
            inFile >> exData[i][j];
        }
    }
    //LOG(1, "Done reading data");
}

void errorCheck(int exData[][DAYS]) {
    for(int i = 0; i < PEOPLE; i++) {
        for (int j = 0; j < DAYS; j++) {
            if(exData[i][j] > 250 || exData[i][j] < 0)
                exData[i][j] = 0;
                //LOG(3, "Zeroing out " + i + ", " + j);
        }
    }
}

void calcMaxDay(int exData[][DAYS], int maxDays[]) {
    for(int i = 0; i < PEOPLE; i++) {
        maxDays[i] = calcMaxDayPerPerson(exData[i]);
    }
}

void calcAvgs(int exData[][DAYS], int dayAvgs[]) {
    for(int i =0 ; i < PEOPLE; i++) {
        dayAvgs[i] = calcAvgPerDay(exData[i]);
    }
}

void calcTotals(int exData[][DAYS], int totals[]) {
    for(int i = 0; i < PEOPLE; i++) {
        for(int j = 0; j < DAYS; j++) {
            totals[i] += exData[i][j];
        }
    }
}

int calcTotal(int totals[]) {
    int sum = 0;
    for(int i = 0; i < PEOPLE; i++) {
        sum += totals[i];
    }
    return sum;
}

int calcMaxDayPerPerson(int exDataP[]) {
    int maxIndex = 0;
    for (int i = 0; i < DAYS; i++) {
        if(exDataP[i] > exDataP[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}

int calcAvgPerDay(int exDataP[]) {
    int sum = 0;
    for (int i =0 ; i < DAYS; i++) {
        sum += exDataP[i];
    }
    return sum / DAYS;
}

void outputCalculations(int exData[][DAYS], int maxDays[], int dayAvgs[], int totals[], int total) {
    for (int i = 0; i < PEOPLE; i++) {
        cout << "Person " << i+1 << ":"<< endl;
        cout << "   " << "Performed the most exercise on the " << maxDays[i]+1 << daySuffix(maxDays[i]) << " day with " << exData[i][maxDays[i]] << " minutes." << endl;
        cout << "   " << "Had an average exercise of " << dayAvgs[i] << " minutes per day.\n";
        cout << "   " << "Contributed "  << ((float) totals[i] / (float) total) * 100.0 << "% to the group total.\n";
    }
}

string daySuffix(int dayIndex) {
    int day = dayIndex+1;
    string suffix = "th";
    if(day == 1)
        suffix = "st";
    if(day == 2)
        suffix = "nd";
    if(day == 3)
        suffix = "rd";
    return suffix;
}