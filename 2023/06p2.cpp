#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

string get_number(string &s){
    string n = "";
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 48 && s[i] <= 57){ 
            n += s[i];
        }
    }
    return n;
};

struct Race {
    unsigned long long time;
    unsigned long long record;

    Race(unsigned long long t, unsigned long long r){
        time = t;
        record = r;
    }
};

Race get_race(string s){
    ifstream file;

    string line = "";
    unsigned long long time = 0;
    unsigned long long record = 0;

    file.open(s);
    getline(file, line);
    time = stoull(get_number(line));
    getline(file, line);
    record = stoull(get_number(line));
    file.close();

    return Race(time, record);
}

int main (){
    Race race = get_race("input.txt");

    unsigned long long count = 0;
    for(unsigned long long j = 0; j < race.time; j++){
        if ( (race.time - j) * j > race.record ) count++;
    }

    cout << count;
    return 0;
}