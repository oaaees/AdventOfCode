#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std; 

struct coordinates {
    int x;
    int y;

    coordinates(int x, int y) : x(x), y(y){}
};

tuple<vector<vector<int>>, coordinates, coordinates> get_input(string filename){
    string line = "";
    vector<vector<int>> input = {};
    int sx, sy, ex, ey;

    ifstream ReadFile(filename);

    while (getline(ReadFile, line)) {
        input.push_back(vector<int>(line.size()));

        for(int i = 0; i < line.size(); i++){
            if (line[i] == 'S'){ input[input.size() - 1][i] = 0; sx = i; sy = input.size() - 1;}
            else if (line[i] == 'E'){ input[input.size() - 1][i] = 25; ex = i; ey = input.size() - 1; }
            else{ input[input.size() - 1][i] = line[i] - 97; }
        }
    }

    ReadFile.close();
    return make_tuple(input, coordinates(sx, sy), coordinates(ex, ey));
}

void print_matrix(vector<vector<int>> pixels){
    for(int i = 0; i < pixels.size(); i++){
        for(int j = 0; j < pixels[i].size(); j++) cout << pixels[i][j] << " ";
        cout << "\n";
    }
}

bool change_left(vector<vector<int>> &map, vector<vector<int>> &dte, coordinates c){
    if(map[c.y][c.x - 1] >= map[c.x][c.y] && dte[c.y][c.x - 1] > dte[c.y][c.x] + 1){
        dte[c.y][c.x - 1] = dte[c.y][c.x] + 1;
        return true;
    }
    return false;
}

bool change_up(vector<vector<int>> &map, vector<vector<int>> &dte, coordinates c){
    if(map[c.y - 1][c.x] >= map[c.x][c.y] && dte[c.y - 1][c.x] > dte[c.y][c.x] + 1){
        dte[c.y - 1][c.x] = dte[c.y][c.x] + 1;
        return true;
    }
    return false;
}

bool change_right(vector<vector<int>> &map, vector<vector<int>> &dte, coordinates c){
    if(map[c.y][c.x + 1] >= map[c.x][c.y] && dte[c.y][c.x + 1] > dte[c.y][c.x] + 1){
        dte[c.y][c.x + 1] = dte[c.y][c.x] + 1;
        return true;
    }
    return false;
}

bool change_down(vector<vector<int>> &map, vector<vector<int>> &dte, coordinates c){
    if(map[c.y + 1][c.x] >= map[c.x][c.y] && dte[c.y + 1][c.x] > dte[c.y][c.x] + 1){
        dte[c.y + 1][c.x] = dte[c.y][c.x] + 1;
        return true;
    }
    return false;
}

int main (int argc, char* argv[]){
    auto input =  get_input("input.txt");

    vector<vector<int>> map = get<0>(input);
    coordinates start = get<1>(input);
    coordinates end = get<2>(input);

    vector<vector<int>> dte(map.size(), vector<int>(map[0].size(), map.size() * map[0].size()));

    queue<coordinates> q({ end });
    dte[end.y][end.x] = 0;
    bool stop_flag = false;

    while(!q.empty()){
        coordinates c = q.front();

        if( c.x > 0 && map[c.y][c.x - 1] >= map[c.y][c.x] - 1 && dte[c.y][c.x - 1] > dte[c.y][c.x] + 1 ){
            dte[c.y][c.x - 1] = dte[c.y][c.x] + 1;
            q.push(coordinates(c.x - 1, c.y));
        }
        if( c.y > 0 && map[c.y - 1][c.x] >= map[c.y][c.x] - 1 && dte[c.y - 1][c.x] > dte[c.y][c.x] + 1){
            dte[c.y - 1][c.x] = dte[c.y][c.x] + 1;
            q.push(coordinates(c.x, c.y - 1));
        }
        if(c.x < map[c.y].size() - 1 && map[c.y][c.x + 1] >= map[c.y][c.x] - 1 && dte[c.y][c.x + 1] > dte[c.y][c.x] + 1){
            dte[c.y][c.x + 1] = dte[c.y][c.x] + 1;
            q.push(coordinates(c.x + 1, c.y));
        }
        if(c.y < map.size() - 1 && map[c.y + 1][c.x] >= map[c.y][c.x] - 1 && dte[c.y + 1][c.x] > dte[c.y][c.x] + 1){
            dte[c.y + 1][c.x] = dte[c.y][c.x] + 1;
            q.push(coordinates(c.x, c.y + 1));
        }

        q.pop();
    }

    cout << dte[start.y][start.x];

    return 0;
}