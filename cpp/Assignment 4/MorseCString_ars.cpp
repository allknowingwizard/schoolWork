#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

const char charTable[50] = {' ', ',' , '.' ,'?' ,'0' ,'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const char morseTable[50][50] = {" ", "--..--", ".-.-.-", "..--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

const bool bin = true;
//recurrsive binary search that returns the index of the query match
int binarySearch(int start, int end, char query) {
    //as long as the scope is greater than 0 (there is still something to be searched)
    if (end >= start)
        {
            //find the middle of the array
            int middle = start + (end - start)/2;
    
            // if the middle is the query, return it
            if (charTable[middle] == query)  
                return middle;
    
            // if the query is lower than the middle
            if (charTable[middle] > query) 
                // start a new binary search in the lower half of the current scope
                return binarySearch(start, middle-1, query);
    
            //if the query is not lower than the middle
            return binarySearch( middle+1, end, query);
        }
    //returns -1 if query is not present in array
    return -1;
}


void cstringtoMorse(char* str, char* mor) {
    int i = 0;
    int index = 0;
    while(str[i] != '\0') {
        index = 0;
        if(!bin) {
            index = binarySearch(0, 40, str[i]);
        } else {
            while(str[i] != charTable[index])
                index++;
        }

        if(i > 0)
            strcat(mor, "Z");
        strcat(mor, morseTable[index]);

        i++;
    }
}

int main() {
    cout << "howdy";
    char c[] = "ADAM";
    char b[4*5+1];
    cstringtoMorse(c, b);
    cout << b << endl;
    string s = "983";
    cout << to_string(stoi(s));
    return 0;
}