#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>

using namespace std; 

enum command {
    noop,
    addx
};

struct instruction {
    command c;
    int value;

    instruction(command _c, int _v){
        c = _c;
        value = _v;
    }

    int get_cycles(){
        int cycles = 0;
        switch (c){
        case noop:
            cycles = 1;
            break;
        case addx:
            cycles = 2;
            break;
        default:
            break;
        }
        return cycles;
    }
};

vector<string> tokenize_line(string s, char d){
    vector<string> output = {};
    int last = 0;

    for(int i = 0; i < s.size(); i++){
        if(s[i] == d){
            string token = s.substr(last, i - last);
            last = i + 1;
            if (token.size() > 0) output.push_back(token);
        }
    }

    output.push_back(s.substr(last));
    return output;
}

queue<instruction> get_input(string filename){
    string line = "";
    queue<instruction> input = {};

    ifstream ReadFile(filename);

    while (getline(ReadFile, line)) {
        vector<string> tokens = tokenize_line(line, ' ');
        command cmd = (tokens[0] == "addx") ? addx : noop;  
        int value = (cmd == addx) ? stoi(tokens[1]) : 0;
        input.push(instruction(cmd, value));
    }

    ReadFile.close();
    return input;
}

void print_screen(vector<vector<char>> pixels){
    for(int i = 0; i < pixels.size(); i++){
        for(int j = 0; j < pixels[i].size(); j++){
            cout << pixels[i][j];
        }

        cout << "\n";
    }
}

int main (){
    queue<instruction> instructions = get_input("input.txt");
    vector<vector<char>> screen(6, vector<char>(40, ' '));
    int clock = 0;
    int x = 1;

    while(!instructions.empty()){
        instruction current = instructions.front();

        for(int i = 0; i < current.get_cycles(); i++){
            int row = (clock / 40);
            int col = (clock % 40);

            //During
            if (col >= x - 1 && col <= x + 1) screen[row][col] = '+';
            clock++;
        }
        
        //After
        x += current.value;
        instructions.pop();
    }

    print_screen(screen);

    return 0;
}