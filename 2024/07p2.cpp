#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void increment(vector<int>& v, int max) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == max) {
            v[i] = 0;
        } else {
            v[i]++;
            break;
        }
    }
}

class Equation {
public:
    long long unsigned int result;
    vector<long long unsigned int> tokens;

    Equation(string s) {
        int last_space = 0;
        for(int i = 0; i < s.size(); i++){
            if (s[i] == ':') {
                result = stoull(s.substr(0, i));
                last_space = i + 1;
                i++;
            } else if (s[i] == ' ') {
                tokens.push_back(stoull(s.substr(last_space, i)));
                last_space = i + 1;
            }
        }
        tokens.push_back(stoull(s.substr(last_space)));
    }

    bool is_solvable(){
        vector<int> operators(tokens.size() - 1, 0);

        do {
            unsigned long long int r = tokens[0];

            for (int i = 0; i < operators.size(); i++) {
                if (operators[i] == 0) {
                    r += tokens[i + 1];
                } else if (operators[i] == 1) {
                    r *= tokens[i + 1];
                } else if (operators[i] == 2) {
                    r = stoull(to_string(r) + to_string(tokens[i + 1]));
                }
            }

            if (r == result) {
                return true;
            }

            increment(operators, 2);

        } while (operators != vector<int>(operators.size(), 0));

        return false;
    }
};

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    vector<Equation> equations;

    while (getline(input_file, line)) {
        equations.push_back(Equation(line));
    }

    input_file.close();

    unsigned long long sum = 0;

    for (int i = 0; i < equations.size(); i++) {
        if (equations[i].is_solvable()) {
            sum += equations[i].result;
        }
    }

    cout << sum;

    return 0;
}