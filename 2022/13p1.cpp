#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std; 

vector<string> split(string s){
    s = s.substr(1, s.size() - 2);
    vector <string> ans;
    int depth = 0;
    string tmp = "";

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '[') depth++;
        else if (s[i] == ']') depth--;
        else if (s[i] == ',' && depth == 0)
        {
            ans.push_back(tmp);
            tmp.clear();
        }

        if (s[i] != ',' || (s[i] == ',' && depth != 0)) tmp.push_back(s[i]);
    }
    if (tmp.size() != 0) ans.push_back(tmp);

    return ans;
}

vector<int> get_input(string filename){
    string line = "";
    vector<int> input = {};

    ifstream ReadFile(filename);

    while (getline(ReadFile, line)) {
        split(line);
        int a;
    }

    ReadFile.close();
    return input;
}




int main () {
    auto input = get_input("input.txt");

    return 0;
}