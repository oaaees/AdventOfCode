#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int countXmas(vector<vector<char>> M){
    int count = 0;

    for(int i = 1; i < M.size() - 1; i++){
        for(int j = 1; j < M[i].size() - 1; j++){
            if (M[i][j] == 'A'){
                if (M[i - 1][j - 1] == 'M' && M[i - 1][j + 1] == 'M' && M[i + 1][j - 1] == 'S' && M[i + 1][j + 1] == 'S') count += 1;
                if (M[i - 1][j - 1] == 'S' && M[i - 1][j + 1] == 'S' && M[i + 1][j - 1] == 'M' && M[i + 1][j + 1] == 'M') count += 1;
                if (M[i - 1][j - 1] == 'M' && M[i - 1][j + 1] == 'S' && M[i + 1][j - 1] == 'M' && M[i + 1][j + 1] == 'S') count += 1;
                if (M[i - 1][j - 1] == 'S' && M[i - 1][j + 1] == 'M' && M[i + 1][j - 1] == 'S' && M[i + 1][j + 1] == 'M') count += 1;
            }
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