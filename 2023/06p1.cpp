#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

vector<string> split(string &s, char c){
    vector<string> v;
    int last = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == c){ 
            if (i - last > 0) v.push_back(s.substr(last, i - last));
            last = i + 1;
        }
    }
    v.push_back(s.substr(last));
    return v;
};

struct Race {
    int time;
    int record;

    Race(int t, int r){
        time = t;
        record = r;
    }
};

vector<Race> get_races(string s){
    ifstream file;
    file.open(s);

    string line = "";
    vector<string> temp = {};
    vector<int> times = {};
    vector<int> records = {};

    getline(file, line);
    temp = split(line, ' ');
    for(int i = 1; i < temp.size(); i++) times.push_back(stoi(temp[i]));
    getline(file, line);
    temp = split(line, ' ');
    for(int i = 1; i < temp.size(); i++) records.push_back(stoi(temp[i]));

    file.close();
    vector<Race> races = {};
    for(int i = 0; i < times.size(); i++) races.push_back(Race(times[i], records[i]));
    return races;
}

int main (){
    vector<Race> races = get_races("input.txt");
    vector<int> results = vector<int>(races.size(), 0);

    for(int i = 0; i < races.size(); i++){
        int count = 0;
        for(int j = 0; j < races[i].time; j++){
            if ( (races[i].time - j) * j > races[i].record ) count++;
        }
        results[i] = count;
    }

    int result = 1;

    for(int i = 0; i < results.size(); i++){
        result *= results[i];
    }

    cout << result;
    return 0;
}