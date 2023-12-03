#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Game {
    string full;
    vector<string> sets;
    vector<vector<pair<int, char>>> plays;
    int ID;

    Game(string line) {
        full = line;
        setID();
        setSets();
        setPlays();
    }

    void setID(){
        string s = "";
        for(int i = 0; i < full.size(); i++){
            if(full[i] >= 48 && full[i] <= 57) s += full[i];
            if(full[i] == ':'){
                full = full.substr(i+2);
                ID = stoi(s);
                break;
            } 
        }
    }

    void setSets(){
        int last = 0;
        for (int i = 0; i < full.length(); i++){
            if(full[i] == ';'){
                sets.push_back(full.substr(last, i - last));
                i += 2;
                last = i;
            }
        }
        sets.push_back(full.substr(last));
    }

    void setPlays(){
        vector<pair<int, char>> v = {};
        vector<vector<pair<int, char>>> mv = {};

        for(int i = 0; i < sets.size(); i++){
            string s = "";
            for(int j = 0; j < sets[i].size(); j++){
                if(sets[i][j] == ' '){
                    int n = stoi(s);
                    char c = sets[i][j + 1];
                    v.push_back(make_pair(n,c));
                    s = "";

                    switch(c){
                        case 'r':
                        j += 5;
                        break;
                        case 'b':
                        j += 6;
                        break;
                        case 'g':
                        j += 7;
                        break;
                    }
                } else {
                    s += sets[i][j];
                }
            }
            mv.push_back(v);
            v = {};
        }

        plays = mv;
    }

    ~Game(){}
};

int main (){
    ifstream file;
    file.open("input.txt");

    string line = "";
    int sum = 0;

    while( file.good() ){
        getline(file, line);
        
        Game game = Game(line);
        bool valid = true;

        for(int i = 0; i < game.plays.size(); i++){
            int blue = 0, red = 0, green = 0;

            for(int j = 0; j < game.plays[i].size(); j++){
                switch(game.plays[i][j].second){
                    case 'r':
                    red += game.plays[i][j].first;
                    break;
                    case 'b':
                    blue += game.plays[i][j].first;
                    break;
                    case 'g':
                    green += game.plays[i][j].first;
                    break;
                    default:
                    break;
                }
            }

            if(blue > 14 || red > 12 || green > 13){
                valid = false;
                break;
            }
        }

        if(valid) sum += game.ID;
    }

    file.close();
    cout << sum;

    return 0;
}