#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>

using namespace std; 

enum dir {
    left,
    up,
    right,
    down
};

struct position {
    int x;
    int y;
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

queue<pair<dir, int>> get_input(string filename){
    string line = "";
    queue<pair<dir, int>> input = {};

    ifstream ReadFile(filename);

    while (getline(ReadFile, line)) {
        vector<string> tokens = tokenize_line(line, ' ');
        dir dir;

        switch (tokens[0][0]){
            case 'L':
                dir = dir::left;
                break;
            case 'U':
                dir = dir::up;
                break;
            case 'R':
                dir = dir::right;
                break;
            case 'D':
                dir = dir::down;
                break;
            default:
                break;
        }

        input.push(make_pair(dir, stoi(tokens[1])));
    }

    ReadFile.close();
    return input;
}

void extend_left(deque<deque<bool>> &m, position &head_pos, position &tail_pos){
    m.push_front(deque<bool>(m[0].size(), false));
    head_pos.x++;
    tail_pos.x++;
}

void extend_up(deque<deque<bool>> &m, position &head_pos, position &tail_pos){
    for(int i = 0; i < m.size(); i++) m[i].push_front(false);
    head_pos.y++;
    tail_pos.y++;
}

void extend_right(deque<deque<bool>> &m, position &head_pos, position &tail_pos){
    m.push_back(deque<bool>(m[0].size(), false));
}

void extend_down(deque<deque<bool>> &m, position &head_pos, position &tail_pos){
    for(int i = 0; i < m.size(); i++) m[i].push_back(false);
}

bool are_touching(position &head_pos, position &tail_pos){
    float distance_squared = (head_pos.x - tail_pos.x) * (head_pos.x - tail_pos.x) + (head_pos.y - tail_pos.y) * (head_pos.y - tail_pos.y) ;
    return (distance_squared <= 2.0);  
}

void move_tail(deque<deque<bool>> &has_tail_been_here, position &head_pos, position &tail_pos){
    if (!(head_pos.y == tail_pos.y)){
        (head_pos.y < tail_pos.y) ? tail_pos.y-- : tail_pos.y++;
    } 
    if (!(head_pos.x == tail_pos.x)){
        (head_pos.x < tail_pos.x) ? tail_pos.x-- : tail_pos.x++;
    }

    has_tail_been_here[tail_pos.x][tail_pos.y] = true;
}

void move_head(deque<deque<bool>> &has_tail_been_here, position &head_pos, position &tail_pos, dir direction){
    switch (direction){
        case dir::left:
            if (head_pos.x == 0) extend_left(has_tail_been_here, head_pos, tail_pos);
            head_pos.x--;
            break;
        case dir::up:
            if (head_pos.y == 0) extend_up(has_tail_been_here, head_pos, tail_pos);
            head_pos.y--;
            break;
        case dir::right:
            if (head_pos.x == has_tail_been_here.size() - 1) extend_right(has_tail_been_here, head_pos, tail_pos);
            head_pos.x++;
            break;
        case dir::down:
            if (head_pos.y == has_tail_been_here[0].size() - 1) extend_down(has_tail_been_here, head_pos, tail_pos);
            head_pos.y++;
            break;
        default:
            break;
    }
}

int count_spots(deque<deque<bool>>& m){
    int sum = 0;

    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m[i].size(); j++){
            sum += m[i][j];
        }
    }

    return sum;
}

int main (){
    queue<pair<dir, int>> instructions = get_input("input.txt");

    deque<deque<bool>> has_tail_been_here(1, deque<bool>(1, true));

    position head_pos = {0, 0};
    position tail_pos = {0, 0};

    while(!instructions.empty()){
        auto current_instruction = instructions.front();

        for(int i = 0; i < current_instruction.second; i++){
            move_head(has_tail_been_here, head_pos, tail_pos, current_instruction.first);
            if (!are_touching(head_pos, tail_pos)) move_tail(has_tail_been_here, head_pos, tail_pos);
        }

        instructions.pop();
    }

    cout << count_spots(has_tail_been_here);

    return 0;
}