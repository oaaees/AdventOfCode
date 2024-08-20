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

void check_from_left(vector<vector<bool>>& is_visible, vector<vector<int>>& input){
    for(int i = 0; i < input.size(); i++){
        int max = -1;

        for(int j = 0; j < input[i].size(); j++){
            if(input[i][j] > max){
                is_visible[i][j] = true;
                max = input[i][j];
            }
            if(max == 9) break;
        } 
    }
}

void check_from_up(vector<vector<bool>>& is_visible, vector<vector<int>>& input){
    for(int i = 0; i < input[0].size(); i++){
        int max = -1;

        for(int j = 0; j < input.size(); j++){
            if(input[j][i] > max){
                is_visible[j][i] = true;
                max = input[j][i];
            }
            if(max == 9) break;
        } 
    }
}

void check_from_right(vector<vector<bool>>& is_visible, vector<vector<int>>& input){
    for(int i = 0; i < input.size(); i++){
        int max = -1;

        for(int j = input[i].size() - 1; j >= 0; j--){
            if(input[i][j] > max){
                is_visible[i][j] = true;
                max = input[i][j];
            }
            if(max == 9) break;
        } 
    }
}

void check_from_down(vector<vector<bool>>& is_visible, vector<vector<int>>& input){
    for(int i = input[0].size() - 1; i >= 0; i--){
        int max = -1;

        for(int j = input.size() - 1; j >= 0; j--){
            if(input[j][i] > max){
                is_visible[j][i] = true;
                max = input[j][i];
            }
            if(max == 9) break;
        } 
    }
}

int count_visible(vector<vector<bool>>& is_visible){
    int sum = 0;

    for(int i = 0; i < is_visible.size(); i++){
        for(int j = 0; j < is_visible[i].size(); j++){
            sum += is_visible[i][j];
        }
    }

    return sum;
}

int main (int argc, char* argv[]){
    vector<vector<int>> input = get_input("input.txt");
    vector<vector<bool>> is_visible(input.size(), vector<bool>(input[0].size(), false));

    check_from_left(is_visible, input);
    check_from_up(is_visible, input);
    check_from_right(is_visible, input);
    check_from_down(is_visible, input);

    cout << count_visible(is_visible);

    return 0;
}