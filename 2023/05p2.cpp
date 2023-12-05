#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
    vector<pair<unsigned long long, unsigned long long>> seed_ranges;
    vector<Map> maps;

    Almanac(string filename){
        ifstream file;
        file.open(filename); 

        string s = "";
        vector<string> values;

        getline(file, s);
        values = split(s, ' ');

        for(int i = 1; i < values.size(); i += 2){
            unsigned long long n = stoull(values[i]);
            unsigned long long n1 = stoull(values[i + 1]);
            
            seed_ranges.push_back(make_pair(n,n+n1));
        }

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

vector<pair<unsigned long long, unsigned long long>> merge_ranges(vector<pair<unsigned long long, unsigned long long>> ranges);

int main (){
    Almanac a = Almanac("input.txt");

    vector<pair<unsigned long long, unsigned long long>> current_ranges = merge_ranges(a.seed_ranges);
    vector<pair<unsigned long long, unsigned long long>> new_ranges = {};

    for(int i = 0; i < a.maps.size(); i++){
        for(int j = 0; j < current_ranges.size(); j++){
            for(int k = 0; k < a.maps[i].rules.size(); k++){
                unsigned long long source = a.maps[i].rules[k][1];
                unsigned long long range = a.maps[i].rules[k][2];
                unsigned long long destination = a.maps[i].rules[k][0];
                int closest = 0;

                if(current_ranges[j].first >= source && current_ranges[j].first < source + range){
                    if(current_ranges[j].second >= source && current_ranges[j].second < source + range){
                        new_ranges.push_back(make_pair(destination + (current_ranges[j].first - source), destination + (current_ranges[j].second - source)));
                        break;
                    } else {
                        new_ranges.push_back(make_pair(destination + (current_ranges[j].first - source), destination + range));
                        current_ranges[j].first = source + range;
                        j--;
                        break;
                    }
                } 

                if(source - current_ranges[j].first < a.maps[i].rules[closest][1] - current_ranges[j].first && (source - current_ranges[j].first > 0)) closest = k;

                if( k == a.maps[i].rules.size() - 1 ){
                    if ( current_ranges[j].second - current_ranges[j].first < a.maps[i].rules[closest][1] - current_ranges[j].first){
                        new_ranges.push_back(make_pair(current_ranges[j].first, current_ranges[j].second));
                    } else {
                        new_ranges.push_back(make_pair(current_ranges[j].first, a.maps[i].rules[closest][1]));
                        current_ranges[j].first = a.maps[i].rules[closest][1] + 1;
                        j--;
                    }
                }
            }
        }

        current_ranges = merge_ranges(new_ranges);
        new_ranges = {};
    }

    sort(current_ranges.begin(), current_ranges.end(), [](auto a, auto b){ return a.first < b.first; });
    cout << current_ranges[0].first;

    return 0;
}

vector<pair<unsigned long long, unsigned long long>> merge_ranges(vector<pair<unsigned long long, unsigned long long>> ranges){
    vector<pair<unsigned long long, unsigned long long>> stack = {};
    sort(ranges.begin(), ranges.end(), [](auto a, auto b){ return (a.first < b.first); });
    stack.push_back(ranges[0]);

    for(int i = 1; i < ranges.size(); i++){
        if( ranges[i].first >= stack.back().first && ranges[i].first <= stack.back().second){
            stack.back().second = ranges[i].second;
        } else {
            stack.push_back(ranges[i]);
        }
    }

    return stack;
}