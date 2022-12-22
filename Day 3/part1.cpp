#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 
int getPriorityOf(char a);

int main(){
    string line;
    vector<char> duplicates;
    int sum = 0;

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {
        int end = line.size();
        int half = end/2;

        for(int i = 0; i < half; i++){
            for(int j = half; j < end; j++){
                if(line[i] == line[j]){
                    duplicates.push_back(line[i]);
                    goto skip;
                }
            }
        }

        skip: ;

    }

    ReadFile.close(); 

    for( char letter : duplicates ){
        sum += getPriorityOf(letter);
    }
    

    cout << "Score is: " << sum << endl;

    return 0;
}

int getPriorityOf(char a){
    if(a >= 'A' && a <= 'Z'){
        return a - 38;
    } else {
        return a - 96;
    }
}