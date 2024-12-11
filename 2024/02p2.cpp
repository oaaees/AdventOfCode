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
        bool has_removed;

        Report(vector<int> report) {
            has_removed = false;
            this->report = report;
        }

        Report(vector<int> report, bool has_removed, int index_removed) {
            this->has_removed = has_removed;
            this->report = report;
            this->report.erase(this->report.begin() + index_removed);
        }

        bool is_increasing(){
            for (int i = 0; i < report.size() - 1; i++) {
                if (report[i] > report[i + 1] && !this->has_removed) {
                    Report temp1(report, true, i);
                    Report temp2(report, true, i + 1);
                    if(temp1.is_safe() || temp2.is_safe()){
                        this->has_removed = true;
                        int index_removed = (temp1.is_safe() ? i : i + 1);
                        this->report.erase(this->report.begin() + index_removed);
                        continue;
                    }
                    return false;
                } else if (report[i] > report[i + 1] && this->has_removed) {
                    return false;
                }
            }
            return true;
        }

        bool is_decreasing(){
            for (int i = 0; i < report.size() - 1; i++) {
                if (report[i] < report[i + 1] && !this->has_removed) {
                    Report temp1(report, true, i);
                    Report temp2(report, true, i + 1);
                    if(temp1.is_safe() || temp2.is_safe()){
                        this->has_removed = true;
                        int index_removed = (temp1.is_safe() ? i : i + 1);
                        this->report.erase(this->report.begin() + index_removed);
                        continue;
                    }
                    return false;
                } else if (report[i] < report[i + 1] && this->has_removed) {
                    return false;
                }
            }
            return true;
        }

        bool has_jumps(){
            for(int i = 0; i < report.size() - 1; i++) {
                if ((report[i + 1] - report[i] > 3 || report[i + 1] - report[i] < -3) && !this->has_removed) {
                    Report temp1(report, true, i);
                    Report temp2(report, true, i + 1);
                    if(temp1.is_safe() || temp2.is_safe()){
                        this->has_removed = true;
                        int index_removed = (temp1.is_safe() ? i : i + 1);
                        this->report.erase(this->report.begin() + index_removed);
                        continue;
                    }
                    return true;
                } else if ((report[i + 1] - report[i] > 3 || report[i + 1] - report[i] < -3) && this->has_removed) {
                    return true;
                } else if (report[i] == report[i + 1] && !this->has_removed) {
                    Report temp(report, true, i);
                    if(temp.is_safe()){
                        this->has_removed = true;
                        this->report.erase(this->report.begin() + i);
                        continue;
                    }
                    return true;
                } else if (report[i] == report[i + 1] && this->has_removed) {
                    return true;
                }
            }
            return false;
        }

        bool is_safe(){
            return (this->is_increasing() || this->is_decreasing()) && !this->has_jumps() ;
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