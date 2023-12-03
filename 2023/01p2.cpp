#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int checksubstringat(string &s, int index, string a){
    if(s.size() - index < a.size()) return false;

    for(int i = index + 1; i < index + a.length(); i++){
        if(s[i] != a[i - index]) return false;
    }

    return true;
}

void setfirstandlast(int &f, int &l, int n){
    if(f == -1) f = n;
    l = n;
}

int main (){
    ifstream file;
    file.open("HxMf.txt");

    string s = "";
    long long sum = 0;

    while( file.good() ){
        file >> s;
        int f = -1, l = -1;

        for(int i = 0; i < s.length(); i++){
            if(s[i] >= 48 && s[i] <= 57){
                setfirstandlast(f, l, s[i] - 48);
                continue;
            }

            switch (s[i]){
                case 'o':
                if (checksubstringat(s,i,"one")){ setfirstandlast(f, l, 1); i += 1; }
                break;
                case 't':
                if (checksubstringat(s,i,"two")){ setfirstandlast(f, l, 2); i += 1;  break;}
                if (checksubstringat(s,i,"three")){ setfirstandlast(f, l, 3); i += 3; }
                break;
                case 'f':
                if (checksubstringat(s,i,"four")){ setfirstandlast(f, l, 4); i += 3;  break;}
                if (checksubstringat(s,i,"five")){ setfirstandlast(f, l, 5); i += 2;}
                break;
                case 's':
                if (checksubstringat(s,i,"six")){ setfirstandlast(f, l, 6); i += 2; break;}
                if (checksubstringat(s,i,"seven")){ setfirstandlast(f, l, 7); i += 3;}
                break;
                case 'e':
                if (checksubstringat(s,i,"eight")){ setfirstandlast(f, l, 8); i += 3;}
                break;
                case 'n':
                if (checksubstringat(s,i,"nine")){ setfirstandlast(f, l, 9); i += 2;}
                break;
                default:
                break;
            }
        }

        sum += (f * 10) + l;
    }

    file.close();
    std::cout << sum;

    return 0;
}