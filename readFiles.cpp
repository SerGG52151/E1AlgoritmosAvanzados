#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string getString(string fileName){
    ifstream file(fileName);
    if(!file){
        cout << "No file found\n" << endl;
        return "";
    }

    string s, line;

    while(getline(file, line)){
        s += line;
    }

    return s;
}
