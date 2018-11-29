#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main() {
    
    
    ifstream infile;
    ofstream outfile;

    infile.open("preProcess/infile.txt");
    if(!infile) {
        cout << "File failed to open.";
        return 0;
    }
    outfile.open("postProcess/outfile.txt");
    if(!outfile) {
        cout << "Can't output to file. Likely missing permissions.";
        return 0;
    }

    cout << "Processing Data...\n";
    string str = "";
    while (infile >> str) {
        for(int i = 0; i < str.length(); i++) {
            if(str[i] == '\'') {
                for(int j = i; j < str.length()-1;j++) {
                    str[i] = str[i+1];
                }
                str = str.substr(0, str.length() -1);
            }
        }
        
        outfile << str;
    }
    cout << "Data Processed!";

    infile.close();
    outfile.close();
    return 0;
}