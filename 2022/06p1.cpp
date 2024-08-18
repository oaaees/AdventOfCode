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

bool is_in(char c, string s){
    for(int i = 0; i < s.size(); i++){
        if (s[i] == c) return true;
    }
    return false;
}

int get_sop_marker(string s){
    for(uint i = 3; i < s.size(); i++){
        if( !is_in(s[i], s.substr(i - 3, 3)) && !is_in(s[i - 1], s.substr(i - 3, 2)) && !is_in(s[i - 2], s.substr(i - 3, 1))) return i + 1; 
    }

    return -1;
}

int main(){
    string input = get_input("input.txt");
    cout << get_sop_marker(input);

    return 0;
}