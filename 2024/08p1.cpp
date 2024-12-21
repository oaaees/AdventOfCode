#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Map {
public:
    vector<vector<int>> antennas;
    vector<vector<int>> antinodes;
    vector<vector<char>> full_map;
    int size_x;
    int size_y;

    Map(vector<vector<char>> map) {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] != '.') antennas.push_back({ i, j, map[i][j] });
            }
        }

        size_x = map[0].size();
        size_y = map.size();

        antinodes = get_antinodes();   
        full_map = get_map();
    }


    vector<vector<int>> get_antinodes(){
        vector<vector<int>> antinodes;

        for (int i = 0; i < antennas.size(); i++){
            for (int j = 0; j < antennas.size(); j++){
                if (i == j || antennas[i][2] != antennas[j][2]) continue;

                antinodes.push_back({ antennas[i][0] + (antennas[i][0] - antennas[j][0]), antennas[i][1] + (antennas[i][1] - antennas[j][1]) });
            }
        }

        return antinodes;
    }

    vector<vector<char>> get_map(){
        vector<vector<char>> map;

        for (int i = 0; i < size_y; i++){
            vector<char> temp;
            for (int j = 0; j < size_x; j++){
                temp.push_back('.');
            }
            map.push_back(temp);
        }

        for (int i = 0; i < antennas.size(); i++){
            map[antennas[i][0]][antennas[i][1]] = antennas[i][2];
        }

        for (int i = 0; i < antinodes.size(); i++){
            if (antinodes[i][0] < 0 || antinodes[i][0] >= size_y || antinodes[i][1] < 0 || antinodes[i][1] >= size_x) continue;
            map[antinodes[i][0]][antinodes[i][1]] = '#';
        }

        return map;
    }

    int count_unique_antinodes(){
        int count = 0;

        for (int i = 0; i < size_y; i++){
            for (int j = 0; j < size_x; j++){
                if (full_map[i][j] == '#') count++;
            }
        }

        return count;
    }

    void print_map(){
        vector<vector<char>> map = get_map();

        for (int i = 0; i < size_y; i++){
            for (int j = 0; j < size_x; j++){
                cout << map[i][j];
            }
            cout << endl;
        }
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
        for (int i = 0; i < line.size(); i++) temp.push_back(line[i]);
        map.push_back(temp);
    }

    input_file.close();


    Map map_obj(map);
    cout << map_obj.count_unique_antinodes() << endl;

    return 0;
}