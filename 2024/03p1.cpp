#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> search(string s){
    vector<vector<int>> result;
    vector<int> pair;

    for(int i = 0; i < s.length(); i++){
        if (s.substr(i, 4) == "mul(") {
            i = i + 4;
            string num1 = "";
            int j = 0;

            for(j = 0; j < 3; j++){
                if(s[i + j] >= '0' && s[i + j] <= '9'){
                    num1 += s[i + j];
                } else if (s[i + j] == ',') {
                    break;
                } else {
                    num1 = "";
                    break;
                }
            }

            if(s[i + j] != ',') continue;

            i = i + j + 1;

            string num2 = "";
            for(j = 0; j < 3; j++){
                if(s[i + j] >= '0' && s[i + j] <= '9'){
                    num2 += s[i + j];
                } else if (s[i + j] == ')') {
                    break;
                } else {
                    num2 = "";
                    break;
                }
            }

            if(s[i + j] != ')') continue;

            i = i + j;

            if(num1.size() == 0 || num2.size() == 0) continue;

            pair.push_back(stoi(num1));
            pair.push_back(stoi(num2));
            result.push_back(pair);
            pair.clear();
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    vector<vector<int>> mul;

    while (getline(input_file, line)) {
        vector<vector<int>> temp = search(line);
        mul.insert(mul.end(), temp.begin(), temp.end());
    }

    input_file.close();

    long long int sum = 0;

    for(int i = 0; i < mul.size(); i++){
        sum += mul[i][0] * mul[i][1];
    }

    cout << sum;

    return 0;
}