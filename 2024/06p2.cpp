#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Lab {
    public:
        vector<vector<char>> map;
        vector<vector<vector<bool>>> visited;
        int current_x;
        int current_y;
        int start_x;
        int start_y;
        char dir;
        bool is_done = false;
        bool is_loop = false;

        Lab(vector<vector<char>> map){
            this->map = map;
            this->visited = vector<vector<vector<bool>>>(map.size(), vector<vector<bool>>(map[0].size(), vector<bool>(4, false)));
            find_current_pos();
            this->start_x = current_x;
            this->start_y = current_y;
        }

        void find_current_pos(){
            for (int i = 0; i < map.size(); i++){
                for (int j = 0; j < map[i].size(); j++){
                    if (map[i][j] == '^' || map[i][j] == 'v' || map[i][j] == '>' || map[i][j] == '<'){
                        current_x = j;
                        current_y = i;
                        dir = map[i][j];
                        return;
                    }
                }
            }
        }

        int dir_to_int(char dir){
            if (dir == '^') return 0;
            if (dir == '>') return 1;
            if (dir == 'v') return 2;
            if (dir == '<') return 3;
            return -1;
        }

        void change_dir(){
            if (dir == '^' && current_y > 0 && map[current_y - 1][current_x] == '#'){ dir = '>'; change_dir(); }
            else if (dir == '>' && current_x < map[current_y].size() - 1 && map[current_y][current_x + 1] == '#'){ dir = 'v'; change_dir(); }
            else if (dir == 'v' && current_y < map.size() - 1 && map[current_y + 1][current_x] == '#'){ dir = '<'; change_dir(); }
            else if (dir == '<' && current_x > 0 && map[current_y][current_x - 1] == '#'){ dir = '^'; change_dir(); }
            return;
        }

        void step(){
            switch (dir){
                case '^':
                    map[current_y][current_x] = 'X';
                    if (current_y > 0){ current_y--; }
                    change_dir();
                    map[current_y][current_x] = dir;
                    if (current_y == 0 && dir == '^') is_done = true;
                    if (visited[current_y][current_x][dir_to_int(dir)]){ is_loop = true; is_done = true; }
                    visited[current_y][current_x][dir_to_int(dir)] = true;
                    break;
                case 'v':
                    map[current_y][current_x] = 'X';
                    if (current_y < map.size() - 1) current_y++;
                    change_dir();
                    map[current_y][current_x] = dir;
                    if (current_y == map.size() - 1 && dir == 'v') is_done = true;
                    if (visited[current_y][current_x][dir_to_int(dir)]){ is_loop = true; is_done = true; }
                    visited[current_y][current_x][dir_to_int(dir)] = true;
                    break;
                case '>':
                    map[current_y][current_x] = 'X';
                    if (current_x < map[current_y].size() - 1) current_x++;
                    change_dir();
                    map[current_y][current_x] = dir;
                    if (current_x == map[current_y].size() - 1 && dir == '>') is_done = true;
                    if (visited[current_y][current_x][dir_to_int(dir)]){ is_loop = true; is_done = true; }
                    visited[current_y][current_x][dir_to_int(dir)] = true;
                    break;
                case '<':
                    map[current_y][current_x] = 'X';
                    if (current_x > 0) current_x--;
                    change_dir();
                    map[current_y][current_x] = dir;
                    if (current_x == 0 && dir == '<') is_done = true;
                    if (visited[current_y][current_x][dir_to_int(dir)]){ is_loop = true; is_done = true; }
                    visited[current_y][current_x][dir_to_int(dir)] = true;
                    break;
                default:
                    break;
            }
        }

        void make_path(){
            while (!this->is_done){
                this->step();
            }
        }

        vector<vector<int>> empty_x (){
            vector<vector<int>> list;
            for (int i = 0; i < map.size(); i++){
                for (int j = 0; j < map[i].size(); j++){
                    if (map[i][j] == 'X'){
                        list.push_back({i, j});
                        map[i][j] == '.';
                    }
                }
            }
            list.push_back({current_y, current_x});
            map[start_y][start_x] = '^';
            current_x = start_x;
            current_y = start_y;
            return list;
        }   

};

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    vector<vector<char>> map;

    while (getline(input_file, line)) {
        vector<char> temp;
        for(int i = 0; i < line.size(); i++){ 
            temp.push_back(line[i]);
        }
        map.push_back(temp);
    }

    input_file.close();

    Lab lab(map);
    lab.make_path();

    vector<vector<int>> list = lab.empty_x();
    int sum = 0;
    
    for (int i = 0; i < list.size(); i++){
        vector<vector<char>> new_map = map;
        new_map[list[i][0]][list[i][1]] = '#';
        Lab new_lab(new_map);
        new_lab.make_path();
        if (new_lab.is_loop){
            sum++;
        }
    }

    cout << sum;
    return 0;
}