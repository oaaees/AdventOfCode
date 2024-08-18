#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 
using uint = unsigned int;

string get_input(string filename){
    string line = "";
    string input = "";

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {
        input += line;
    }

    ReadFile.close();
    return input;
}

bool are_all_less_than_2(vector<uint> v){
    for(uint i = 0; i < v.size(); i++) if(v[i] >= 2) return false;
    return true;
}

int get_som_marker(string s){
    vector<uint> alphabet(26, 0);

    for(int i = 0; i < s.size(); i++){
        if(i >= 14){
            if(are_all_less_than_2(alphabet)) return i; 
            alphabet[s[i - 14] - 97]--;
        }

        char c = s[i];
        alphabet[c - 97]++;
    }

    return -1;
}

int main(){
    string input = get_input("input.txt");
    cout << get_som_marker(input);

    return 0;
}