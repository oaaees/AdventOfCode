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

struct knot {
    int x;
    int y;
    knot * next;

    knot(int _x, int _y){
        x = _x;
        y = _y;
        next = nullptr;
    }

    void add_after(knot * _next){
        next = _next;
    }
};

struct rope {
    knot * head;

    rope(int x, int y, int length){
        head = new knot(x,y);
        knot * current = head;

        for(int i = 0; i < length - 1; i++){
            current->add_after(new knot(x,y));
            current = current->next;
        }
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

void extend_left(deque<deque<bool>> &m, rope &rope){
    m.push_front(deque<bool>(m[0].size(), false));

    knot * current = rope.head;

    while(current != nullptr){
        current->x++;
        current = current->next;
    }
}

void extend_up(deque<deque<bool>> &m, rope &rope){
    for(int i = 0; i < m.size(); i++) m[i].push_front(false);

    knot * current = rope.head;

    while(current != nullptr){
        current->y++;
        current = current->next;
    }
}

void extend_right(deque<deque<bool>> &m, rope &rope){
    m.push_back(deque<bool>(m[0].size(), false));
}

void extend_down(deque<deque<bool>> &m, rope &rope){
    for(int i = 0; i < m.size(); i++) m[i].push_back(false);
}

bool are_touching(knot * head, knot * tail){
    int distance_squared = (head->x - tail->x) * (head->x - tail->x) + (head->y - tail->y) * (head->y - tail->y) ;
    return (distance_squared <= 2);  
}

void move_tail(deque<deque<bool>> &has_tail_been_here, knot * head, knot * tail){
    if (!(head->y == tail->y)){
        (head->y < tail->y) ? tail->y-- : tail->y++;
    } 
    if (!(head->x == tail->x)){
        (head->x < tail->x) ? tail->x-- : tail->x++;
    }

    if (tail->next == nullptr) has_tail_been_here[tail->x][tail->y] = true;
}

void move_head(deque<deque<bool>> &has_tail_been_here, rope &rope, dir direction){
    knot * head = rope.head;

    switch (direction){
        case dir::left:
            if (head->x == 0) extend_left(has_tail_been_here, rope);
            head->x--;
            break;
        case dir::up:
            if (head->y == 0) extend_up(has_tail_been_here, rope);
            head->y--;
            break;
        case dir::right:
            if (head->x == has_tail_been_here.size() - 1) extend_right(has_tail_been_here, rope);
            head->x++;
            break;
        case dir::down:
            if (head->y == has_tail_been_here[0].size() - 1) extend_down(has_tail_been_here, rope);
            head->y++;
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
    rope rope(0,0,10);

    while(!instructions.empty()){
        auto current_instruction = instructions.front();

        for(int i = 0; i < current_instruction.second; i++){
            move_head(has_tail_been_here, rope, current_instruction.first);

            knot * current = rope.head;
            knot * next = current->next;

            while(next != nullptr){
                if (!are_touching(current, next)) move_tail(has_tail_been_here, current, next);
                current = next;
                next = next->next;
            }            
        }

        instructions.pop();
    }

    cout << count_spots(has_tail_been_here);

    return 0;
}