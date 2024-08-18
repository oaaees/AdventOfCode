#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std; 

vector<stack<char>> get_crate_labels(vector<string> M){
    unsigned int width = M[M.size() - 1].size() + 1;
    unsigned int height = M.size() - 1;

    vector<stack<char>> o(width / 4);

    for(int i = 1; i < width; i += 4){
        for(int j = height - 1; j >= 0; j--){
            if (M[j][i] == ' ') continue;

            o[i / 4].push(M[j][i]);
        }
    }

    return o;
}

vector<unsigned int> get_instructions(string s){
    vector<unsigned int> o = {};
    string num = "";

    for(int i = 0; i < s.size(); i++){
        if(s[i] >= '0' && s[i] <= '9'){
            num += s[i];

            if(i+1 >= s.size() || s[i+1] < '0' || s[i+1] > '9'){
                o.push_back(stoi(num));
                num = "";
            }
        }
    }

    return o;
}

int main() {
    string line;
    vector<string> crates = {};
    vector<vector<unsigned int>> instructions = {};
    bool passed_crates = false;
    
    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {
        if(line == ""){
            passed_crates = true;
            continue;
        }

        if(!passed_crates){
            crates.push_back(line);
        } else {
            instructions.push_back(get_instructions(line));
        }
    }

    ReadFile.close();

   vector<stack<char>> stacks = get_crate_labels(crates);

    for(int i = 0; i < instructions.size(); i++){
        unsigned int from = instructions[i][1] - 1;
        unsigned int to = instructions[i][2] - 1;
        
        stack<char> temp;

        for(int j = 0; j < instructions[i][0]; j++){
            temp.push(stacks[from].top());
            stacks[from].pop();
        }

        for(int j = 0; j < instructions[i][0]; j++){
            stacks[to].push(temp.top());
            temp.pop();
        }
    }

    string output = "";

    for(int i = 0; i < stacks.size(); i++) output += stacks[i].top();
    cout << output;

    return 0;
}