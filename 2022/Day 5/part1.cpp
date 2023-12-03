#include <iostream>
#include <fstream>

using namespace std; 

int main(){
    string line;
    int sum = 0;

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {
    
    }

    ReadFile.close(); 

    cout << "Score is: " << sum << endl;

    return 0;
}