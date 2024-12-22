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

    void defrag_2(){
        int start_block_index = full_map.size() - 1;
        int prev_ID = (disk_map.size() % 2 == 0) ? ((disk_map.size() - 1) / 2) + 1 : (disk_map.size() / 2) + 1;

        while (start_block_index != 0) {
        
            int last_ID, last_size, bs, bf;
            bool block_found = false;

            for (int i = start_block_index; i >= 0; i--){
                if (full_map[i] != -1 && !block_found && full_map[i] == prev_ID - 1 && full_map[i] != 0) {
                    last_ID = full_map[i];
                    bf = i;
                    block_found = true;
                } else if (full_map[i] != last_ID && block_found) {
                    bs = i;
                    last_size = bf - bs;
                    start_block_index = i;
                    break;
                }
            }

            if (!block_found) break;
            prev_ID = last_ID;

            int start_space_index = 0;

            while (true) {
                int space_size, ss, sf;
                bool space_found = false;

                for (int i = start_space_index; i < full_map.size(); i++){
                    if (full_map[i] == -1 && !space_found){
                        ss = i;
                        space_found = true;
                    } else if (full_map[i] != -1 && space_found) {
                        sf = i;
                        space_size = sf - ss;
                        start_space_index = i;
                        break;
                    }
                }

                if (ss >= bs) {
                    break;
                } else if (space_size >= last_size) {
                    for (int i = 0; i < last_size; i++){
                        full_map[ss + i] = last_ID;
                        full_map[bf - i] = -1;
                    }
                    break;
                }   
            }
        }
    }

    unsigned long long get_checksum() {
        unsigned long long res = 0;
        for (int i = 0; i < full_map.size(); i++) if (full_map[i] != -1) res += full_map[i] * i;
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
    disk.defrag_2();

    cout << "Checksum: " << disk.get_checksum() << endl;


    return 0;
}