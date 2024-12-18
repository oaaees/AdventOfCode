#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Lab {
    public:
        vector<vector<char>> map;
        int current_x;
        int current_y;
        char dir;
        bool is_done = false;

        Lab() {
            this->map = {};
            this->current_x = -1;
            this->current_y = -1;
            this->dir = ' ';
        }

        void step(){
            switch (dir){
                case '^':
                    map[current_y][current_x] = 'X';
                    if (current_y > 0){ current_y--; }
                    if (current_y > 0 && map[current_y - 1][current_x] == '#') dir = '>';  
                    map[current_y][current_x] = dir;
                    if (current_y == 0 && dir == '^') is_done = true;
                    break;
                case 'v':
                    map[current_y][current_x] = 'X';
                    if (current_y < map.size() - 1) current_y++;
                    if (current_y < map.size() - 1 && map[current_y + 1][current_x] == '#') dir = '<';  
                    map[current_y][current_x] = dir;
                    if (current_y == map.size() - 1 && dir == 'v') is_done = true;
                    break;
                case '>':
                    map[current_y][current_x] = 'X';
                    if (current_x < map[current_y].size() - 1) current_x++;
                    if (current_x < map[current_y].size() - 1 &&map[current_y][current_x + 1] == '#') dir = 'v';  
                    map[current_y][current_x] = dir;
                    if (current_x == map[current_y].size() - 1 && dir == '>') is_done = true;
                    break;
                case '<':
                    map[current_y][current_x] = 'X';
                    if (current_x > 0) current_x--;
                    if (current_x > 0 && map[current_y][current_x - 1] == '#') dir = '^';  
                    map[current_y][current_x] = dir;
                    if (current_x == 0 && dir == '<') is_done = true;
                    break;
                default:
                    break;
            }
        }

        int count_x (){
            int count = 0;
            for (int i = 0; i < map.size(); i++){
                for (int j = 0; j < map[i].size(); j++){
                    if (map[i][j] == 'X') count++;
                }
            }
            return count;
        }   

};

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    Lab lab;

    while (getline(input_file, line)) {
        vector<char> temp;
        for(int i = 0; i < line.size(); i++){ 
            temp.push_back(line[i]);
            if(line[i] == '^' || line[i] == 'v' || line[i] == '>' || line[i] == '<'){
                lab.current_x = i;
                lab.current_y = lab.map.size();
                lab.dir = line[i];
            }
        }
        lab.map.push_back(temp);
    }

    input_file.close();

    while (!lab.is_done){
        lab.step();
    }

    cout << lab.count_x() + 1;

    return 0;
}