#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> extract_rule(string s){
    vector<int> rule;
    rule.push_back(stoi(s.substr(0, 2)));
    rule.push_back(stoi(s.substr(3, 5)));
    return rule;
}

vector<int> extract_update(string s){
    vector<int> update;
    for(int i = 0; i < s.length(); i += 3){
        update.push_back(stoi(s.substr(i, 2)));
    }
    return update;
}

bool is_good_update(vector<vector<int>> &rules, vector<int> &update){
    for(int i = 0; i < update.size(); i++){
        for(int j = 0; j < rules[update[i]].size(); j++){
            for(int k = i - 1; k >= 0; k--){
                if (update[k] == rules[update[i]][j]) return false;
            }
        }
    }

    return true;
}

void order_update(vector<vector<int>> &rules, vector<int> &update){
    for(int i = 1; i < update.size(); i++){
        for(int j = 0; j < rules[update[i]].size(); j++){
            for(int k = i - 1; k >= 0; k--){
                if (update[k] == rules[update[i]][j]){
                    swap(update[k], update[i]);
                    i = k;
                    j = 0;
                    break;
                }
            }
        }
    }

}


int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    bool first_part = true;
    vector<vector<int>> rules(100, vector<int>(0,0));
    vector<vector<int>> updates(0, vector<int>(0,0));

    while (getline(input_file, line)) {
        if (first_part && line != "") {
            vector<int> rule = extract_rule(line);
            rules[rule[0]].push_back(rule[1]);
        } else if (first_part && line == "") {
            first_part = false;
        } else {
            updates.push_back(extract_update(line));
        }
    }

    input_file.close();

    int sum = 0;

    for(int i = 0; i < updates.size(); i++){
        if (!is_good_update(rules, updates[i])){
            order_update(rules, updates[i]);
            sum += updates[i][(updates[i].size() - 1) / 2];
        }
    }

    cout << sum;

    return 0;
}