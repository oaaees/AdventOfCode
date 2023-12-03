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

    //Sort array and Print top 3
    int max = calories[0];
    int i, j;

    for(int i = 0; i < calories.size() - 1; i++){
        for(int j = i; j < calories.size(); j++){
            if( calories[i] < calories[j] ){
                int temp = calories[i];
                calories[i] = calories[j];
                calories[j] = temp;
            }
        }
    }

    cout << "Top 3 is \n\n1. " << calories[0] << "\n2. " << calories[1] << "\n3. " << calories[2] << "\n\nAnd sum is " << calories[0] + calories[1] + calories[2] << "\n";
    return 0;
}