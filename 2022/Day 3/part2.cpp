#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 
int getPriorityOf(char a);

int main(){
    string group[3];
    vector<char> duplicates;
    int sum = 0;

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, group[0])) {
        getline(ReadFile, group[1]);
        getline(ReadFile, group[2]);

        for(int i = 0; i < group[0].size(); i++){
            for(int j = 0; j < group[1].size(); j++){
                for(int k = 0; k < group[2].size(); k++){
                    if(group[0][i] == group[1][j] && group[0][i] == group[2][k]){
                        duplicates.push_back(group[0][i]);
                        goto skip;
                    }
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