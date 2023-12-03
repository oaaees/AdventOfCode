#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

int main(){
    string line;
    vector<int> calories;
    int sum = 0;

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {

        if(line == ""){
            calories.push_back(sum);
            sum = 0;
            continue;
        }

        int input;
        input = stoi(line);

        sum += input;
    }

    calories.push_back(sum);

    ReadFile.close(); 

    //Find max
    int max = calories[0];

    for(int elf : calories){
        if(elf > max){
            max = elf;
        }
    }

    cout << "Max is " << max << " calories\n";
    return 0;
}