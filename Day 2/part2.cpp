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
        int ply2;
        int result = line[2] - 87;

        if(result == 1){
            sum += 0;
            ply2 = (ply1 == 1) ? 3 : ply1-1;
            sum += ply2;
        } else if(result == 2){
            sum += 3;
            ply2 = ply1;
            sum += ply2;
        } else {
            sum += 6;
            ply2 = (ply1 == 3) ? 1 : ply1+1;
            sum += ply2;
        }
    }

    ReadFile.close(); 

    cout << "Score is: " << sum << endl;

    return 0;
}