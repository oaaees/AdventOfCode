#include <iostream>
#include <fstream>

using namespace std; 

int main(){
    string line;
    int sum = 0;

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {
        int ply1 = line[0] - 64;
        int ply2 = line[2] - 87;
        
        sum += ply2;

        if(ply2 == ply1+1 || (ply2 == 1 && ply1 == 3)){
            sum += 6;
        } else if(ply1 == ply2){
            sum += 3;
        }
    }

    ReadFile.close(); 

    cout << "Score is: " << sum << endl;

    return 0;
}