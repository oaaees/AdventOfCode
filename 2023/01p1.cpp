#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main (){
    ifstream file;
    file.open("input.txt");

    string s = "";
    int sum = 0;

    while( file.good() ){
        file >> s;
        int f = -1, l = -1;

        for(int i = 0; i < s.length(); i++){
            if(s[i] >= 48 && s[i] <= 57){
                if(f == -1) f = s[i] - 48;
                l = s[i] - 48;
            }
        }

        sum += (f * 10) + l;
    }

    file.close();
    cout << sum;

    return 0;
}