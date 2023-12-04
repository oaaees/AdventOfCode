#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int multiplyNeighbours(int i, int j, vector<string> &m);
int fullNumAt(int i, int j, vector<string> &m);
bool has2Neighbours(int i, int j, vector<string> &m);
bool isNum(char c);

int main (){
    ifstream file;
    string s = "";
    vector<string> m = {};

    file.open("input.txt");

    while( file.good() ){
        getline(file,s);
        if(m.size() == 0) m.push_back(string(s.size() + 2, '.'));
        m.push_back('.' + s + '.');
    }
    m.push_back(string(s.size() + 2, '.'));
    file.close();

    int sum = 0;
    for(int i = 1; i < m.size() - 1; i++){
        for(int j = 0; j < m[i].size(); j++){
            if(m[i][j] == '*' && has2Neighbours(i,j,m)){
                sum += multiplyNeighbours(i,j,m);
            }
        }
    }

    cout << sum;
    return 0;
}

bool isNum(char c){
    return (c >= 48 && c <= 57);
}

int multiplyNeighbours(int i, int j, vector<string> &m){
    int mul = 1;

    if(isNum(m[i - 1][j])) mul *= fullNumAt(i - 1,j,m);
    if(isNum(m[i - 1][j + 1])) mul *= fullNumAt(i - 1,j + 1,m);
    if(isNum(m[i][j + 1])) mul *= fullNumAt(i,j + 1,m);
    if(isNum(m[i + 1][j + 1])) mul *= fullNumAt(i + 1,j + 1,m);
    if(isNum(m[i + 1][j])) mul *= fullNumAt(i + 1,j,m);
    if(isNum(m[i + 1][j - 1])) mul *= fullNumAt(i + 1,j - 1,m);
    if(isNum(m[i][j - 1])) mul *= fullNumAt(i,j - 1,m);
    if(isNum(m[i - 1][j - 1])) mul *= fullNumAt(i - 1,j - 1,m);

    return mul;
}

int fullNumAt(int i, int j, vector<string> &m){
    int first = j, last = j;

    while( m[i][first] >= '0' && m[i][first] <= '9') first--;
    while( m[i][last] >= '0' && m[i][last] <= '9') last++;

    string num = m[i].substr(first + 1, last - first - 1);

    for(int x = first + 1; x < last; x++) m[i][x] = '.';

    return stoi(num);
}

bool has2Neighbours(int i, int j, vector<string> &m){
    int count = 0;

    if(isNum(m[i - 1][j])) count++; 
    if(isNum(m[i - 1][j + 1]) && !isNum(m[i - 1][j])) count++; 
    if(isNum(m[i][j + 1])) count++;
    if(isNum(m[i + 1][j + 1])) count++;  
    if(isNum(m[i + 1][j]) && !isNum(m[i + 1][j + 1])) count++; 
    if(isNum(m[i + 1][j - 1]) && !isNum(m[i + 1][j])) count++; 
    if(isNum(m[i][j - 1])) count++; 
    if(isNum(m[i - 1][j - 1]) && !isNum(m[i - 1][j])) count++;

    return count == 2; 
}
