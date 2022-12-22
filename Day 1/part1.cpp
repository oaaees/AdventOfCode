#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

int main(){
    string line;
    vector<int> nums;
    int sum = 0;


    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {

        if(line == ""){
            nums.push_back(sum);
            sum = 0;
            continue;
        }

        int input;
        input = stoi(line);

        sum += input;
    }

    ReadFile.close(); 

    for(int elf : nums){
        cout << elf << endl;
    }

    return 0;
}