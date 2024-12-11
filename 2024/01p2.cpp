#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
    public:
        int key;
        int value;
        Node(int key, int value) {
            this->key = key;
            this->value = value;
        }
};

class HashTable {
    public:
        vector<vector<Node>> table;
        HashTable(int size) {
            table.resize(size);
        }
        int hash(int key) {
            return key % table.size();
        }

        void insert(int key) {
            int index = hash(key);
            
            for (int i = 0; i < table[index].size(); i++) {
                if (table[index][i].key == key) {
                    table[index][i].value += 1;
                    return;
                }
            }

            table[index].push_back(Node(key, 1));
        }

        int find(int key) {
            int index = hash(key);

            for (int i = 0; i < table[index].size(); i++) {
                if (table[index][i].key == key) {
                    return table[index][i].value;
                }
            }

            return 0;
        }

        int size(){
            return table.size();
        }
};


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

    HashTable table1(10);
    HashTable table2(10);

    while (getline(input_file, line)) {
        vector<string> tokens = split(' ', line);

        if (tokens.size() != 2) { break; }

        table1.insert(stoi(tokens[0]));
        table2.insert(stoi(tokens[1]));
    }

    input_file.close();

    int sum = 0;

    for (int i = 0; i < table1.size(); i++) {
        for (int j = 0; j < table1.table[i].size(); j++) {
            sum += (table2.find(table1.table[i][j].key) * table1.table[i][j].key) * table1.table[i][j].value;
        }
    }

    cout << sum;

    return 0;
}