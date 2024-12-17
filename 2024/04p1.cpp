#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int countXmas(vector<vector<char>> M){
    int count = 0;

    for(int i = 0; i < M.size(); i++){
        for(int j = 0; j < M[i].size(); j++){
            if (j < M[i].size() - 3 && M[i][j] == 'X' && M[i][j + 1] == 'M' && M[i][j + 2] == 'A' && M[i][j + 3] == 'S') count += 1;
            if (i < M.size() - 3 && M[i][j] == 'X' && M[i + 1][j] == 'M' && M[i + 2][j] == 'A' && M[i + 3][j] == 'S') count += 1;
            if (j < M[i].size() - 3 && i < M.size() - 3 && M[i][j] == 'X' && M[i + 1][j + 1] == 'M' && M[i + 2][j + 2] == 'A' && M[i + 3][j + 3] == 'S') count += 1;
            if (j < M[i].size() - 3 && i < M.size() - 3 && M[i][j + 3] == 'X' && M[i + 1][j + 2] == 'M' && M[i + 2][j + 1] == 'A' && M[i + 3][j] == 'S') count += 1;

            if (j < M[i].size() - 3 && M[i][j] == 'S' && M[i][j + 1] == 'A' && M[i][j + 2] == 'M' && M[i][j + 3] == 'X') count += 1;
            if (i < M.size() - 3 && M[i][j] == 'S' && M[i + 1][j] == 'A' && M[i + 2][j] == 'M' && M[i + 3][j] == 'X') count += 1;
            if (j < M[i].size() - 3 && i < M.size() - 3 && M[i][j] == 'S' && M[i + 1][j + 1] == 'A' && M[i + 2][j + 2] == 'M' && M[i + 3][j + 3] == 'X') count += 1;
            if (j < M[i].size() - 3 && i < M.size() - 3 && M[i][j + 3] == 'S' && M[i + 1][j + 2] == 'A' && M[i + 2][j + 1] == 'M' && M[i + 3][j] == 'X') count += 1;
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    vector<vector<char>> M;

    while (getline(input_file, line)) {
        vector<char> temp;
        for(int i = 0; i < line.size(); i++) temp.push_back(line[i]);
        M.push_back(temp);
    }

    input_file.close();

    int sum = countXmas(M);

    cout << sum;

    return 0;
}