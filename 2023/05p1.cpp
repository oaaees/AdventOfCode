#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Map {
    string name;
    vector<vector<unsigned long long>> rules;

    Map(string s){
        name = s;
        rules = {};
    }
};

struct Almanac {
    vector<unsigned long long> seeds;
    vector<Map> maps;

    Almanac(string filename){
        ifstream file;
        file.open(filename); 

        string s = "";
        vector<string> values;

        getline(file, s);
        values = split(s, ' ');

        for(int i = 1; i < values.size(); i++) seeds.push_back(stoull(values[i]));

        while( file.good() ){
            getline(file, s);
            if(s.size() == 0){
                getline(file, s);
                maps.push_back(Map(s));
            } else {
                values = split(s, ' ');
                vector<unsigned long long> rule = {};
                for(int i = 0; i < values.size(); i++) rule.push_back(stoull(values[i]));
                maps[maps.size() - 1].rules.push_back(rule);
            }
        }

        file.close();

    };

    vector<string> split(string &s, char c){
        vector<string> v;
        int last = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == c){ 
                v.push_back(s.substr(last, i - last));
                last = i + 1;
            }
        }
        v.push_back(s.substr(last));
        return v;
    };

};

int main (){
    Almanac a = Almanac("input.txt");
    vector<unsigned long long> destinations = vector<unsigned long long>(a.seeds.size(), -1);

    for(int i = 0; i < a.seeds.size(); i++){
        int current_value = a.seeds[i];
        for(int j = 0; j < a.maps.size(); j++){
            for(int k = 0; k < a.maps[j].rules.size(); k++){
                int source = a.maps[j].rules[k][1];
                int range = a.maps[j].rules[k][2];
                int destination = a.maps[j].rules[k][0];

                if(current_value >= source && current_value < source + range){
                    current_value = destination + current_value - source;
                    break;
                }
            } 
        }

        destinations[i] = current_value;

    }

    unsigned long long min = destinations[0];
    for(unsigned long long x : destinations) if(x < min) min = x;
    cout << min;

    return 0;
}

