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
            v.push_back(s.substr(last, i - last));
            last = i + 1;
        }
    }
    v.push_back(s.substr(last));
    return v;
};

vector<int> get_nums(string s){
    vector<string> temp = split(s, ' ');
    vector<int> res = {};

    for(int i = 0; i < temp.size(); i++){
        res.push_back(stoi(temp[i]));
    }

    return res;
};

bool is_all_zeroes(vector<int> v){
    for(int i = 0; i < v.size(); i++) if (v[i] != 0) return false;
    return true;
}

int main (){
    ifstream file;
    file.open("input.txt");

    string s = "";
    vector<vector<int>> nums;
    int sum = 0;

    while( file.good() ){
        getline(file,s);
        nums = {};
        nums.push_back(get_nums(s));

        while(!is_all_zeroes(nums.back())){
            nums.push_back(vector<int>(nums.back().size() - 1, 0));
            for(int i = 0; i < nums.back().size(); i++){
                nums[nums.size() - 1][i] = nums[nums.size() - 2][i+1] - nums[nums.size() - 2][i];
            }
        }

        vector<int> temp = { 0 };

        for(int i = nums.size() - 2; i >= 0; i--){
            temp.push_back(nums[i][0] - temp.back()); 
        }

        sum += temp.back();
    }

    file.close();
    cout << sum;

    return 0;
}