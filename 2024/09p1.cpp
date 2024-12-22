#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Disk {
public:
    vector<int> disk_map;
    vector<int> full_map;
    int checksum;

    Disk(vector<int> map) {
        disk_map = map;

       full_map = {};
        int ID = 0;

        for (int i = 0; i < disk_map.size(); i+=2) {
            for (int j = 0; j < disk_map[i]; j++) full_map.push_back(ID);
            if (i + 1 < disk_map.size()) for (int j = 0; j < disk_map[i + 1]; j++) full_map.push_back(-1);
            ID++;
        }

        checksum = 0;
    }

    void defrag(){
        vector<int> new_map;
        size_t last = full_map.size() - 1;

        for (int i = 0; i <= last; i++) {
            if (full_map[i] == -1 && i < last) {
                new_map.push_back(full_map[last]);
                do { last--; } while (full_map[last] == -1);
            } else {
                new_map.push_back(full_map[i]);
            }
        }

        full_map = new_map;
    }

    unsigned long long get_checksum() {
        unsigned long long res = 0;
        for (int i = 0; i < full_map.size(); i++) res += full_map[i] * i;
        checksum = res;
        return res;
    }

    void print_map() {
        for (int i = 0; i < full_map.size(); i++) 
            if (full_map[i] == -1) cout << ".";
            else cout << full_map[i];
        cout << endl;
    }
};

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    vector<int> disk_map;

    while (getline(input_file, line)) {
        for (int i = 0; i < line.size(); i++) disk_map.push_back(line[i] - '0');
    }

    input_file.close();

    Disk disk(disk_map);
    disk.defrag();

    cout << "Checksum: " << disk.get_checksum() << endl;


    return 0;
}