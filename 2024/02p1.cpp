#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> split(char delimiter, string s) {
    vector<int> tokens;

    for(int i = 0; i < s.length(); i++) {
        if (s[i] == delimiter) {
            tokens.push_back(stoi(s.substr(0, i)));
            s = s.substr(i + 1);
            i = 0;
        }
    }

    tokens.push_back(stoi(s));
    return tokens;
}

class Report {
    public:
        vector<int> report;
        Report(vector<int> report) {
            this->report = report;
        }

        bool is_increasing(){
            for (int i = 0; i < report.size() - 1; i++) {
                if (report[i] > report[i + 1]) {
                    return false;
                }
            }
            return true;
        }

        bool is_decreasing(){
            for (int i = 0; i < report.size() - 1; i++) {
                if (report[i] < report[i + 1]) {
                    return false;
                }
            }
            return true;
        }

        bool has_jumps(){
            for(int i = 0; i < report.size() - 1; i++) {
                if (report[i + 1] - report[i] > 3 || report[i + 1] - report[i] < -3 || report[i] == report[i + 1]) {
                    return true;
                }
            }
            return false;
        }

        bool is_safe(){
            return (!this->has_jumps() && (this->is_increasing() || this->is_decreasing()));
        }


};

int main(int argc, char* argv[]) {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    string line = "";
    vector<Report> reports;

    while (getline(input_file, line)) {
        vector<int> tokens = split(' ', line);
        reports.push_back(Report(tokens));
    }

    input_file.close();

    int sum = 0;

    for (int i = 0; i < reports.size(); i++) {
        if (reports[i].is_safe()) sum++;
    }

    cout << sum;

    return 0;
}