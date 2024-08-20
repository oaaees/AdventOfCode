#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

vector<vector<int>> get_input(string filename){
    string line = "";
    vector<vector<int>> input = {};

    ifstream ReadFile(filename);

    while (getline(ReadFile, line)) {
        input.push_back({});

        for(int i = 0; i < line.size(); i++){
            input[input.size() - 1].push_back(line[i] - 48);
        }
    }

    ReadFile.close();
    return input;
}

int count_to_left(vector<vector<int>>& input, int y, int x){
    for(int i = x - 1; i >= 0; i--){
        if( input[y][i] >= input[y][x]) return (x - i);
    }

    return x;
}

int count_to_up(vector<vector<int>>& input, int y, int x){
    for(int i = y - 1; i >= 0; i--){
        if( input[i][x] >= input[y][x]) return (y - i);
    }

    return y;
}

int count_to_right(vector<vector<int>>& input, int y, int x){
    for(int i = x + 1; i < input[x].size(); i++){
        if( input[y][i] >= input[y][x]) return (i - x);
    }

    return input[x].size() - x - 1;
}

int count_to_down(vector<vector<int>>& input, int y, int x){
    for(int i = y + 1; i < input.size(); i++){
        if( input[i][x] >= input[y][x]) return (i - y);
    }

    return input.size() - y - 1;
}

unsigned long long max(vector<vector<unsigned long long>>& v_score){
    unsigned long long max = 0;

    for(int i = 0; i < v_score.size(); i++){
        for(int j = 0; j < v_score[i].size(); j++){
            if (v_score[i][j] > max) max = v_score[i][j];
        }
    }

    return max;
}

int main (int argc, char* argv[]){
    vector<vector<int>> input = get_input("input.txt");
    vector<vector<unsigned long long>> v_score(input.size(), vector<unsigned long long>(input[0].size(), 0));

    for(int i = 1; i < input.size() - 1; i++){
        for(int j = 1; j < input[i].size() - 1; j++){
            int left = count_to_left(input, i, j);
            int up = count_to_up(input, i, j);
            int right = count_to_right(input, i, j);
            int down = count_to_down(input, i, j);

            v_score[i][j] = left * up * right * down;
        }
    }

    cout << max(v_score);

    return 0;
}