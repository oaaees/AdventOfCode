#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(char delimiter, string s) {
    vector<string> tokens;

    for(int i = 0; i < s.length(); i++) {
        if (s[i] == delimiter) {
            tokens.push_back(s.substr(0, i));
            s = s.substr(i + 1);
            i = 0;
        }
    }

    tokens.push_back(s);
    return tokens;
}

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";

    vector<int> arr1;
    vector<int> arr2;

    while (getline(input_file, line)) {
        vector<string> tokens = split(' ', line);

        if (tokens.size() != 2) { break; }

        arr1.push_back(stoi(tokens[0]));
        arr2.push_back(stoi(tokens[1]));
    }

    input_file.close();

    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    int sum = 0;

    for (int i = 0; i < arr1.size(); i++) {
        sum += abs(arr1[i] - arr2[i]);
    }

    cout << sum;

    return 0;
}