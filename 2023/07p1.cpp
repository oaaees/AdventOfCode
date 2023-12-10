#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

struct Hand {
    vector<int> cards;
    int type;
    int bid;

    Hand(vector<string> s){
        set_cards(s[0]);
        set_type(cards);
        set_bid(s[1]);
    }

    void set_cards(string s){

        for(int i = 0; i < s.size(); i++){
            switch(s[i]){
                case 'T':
                cards.push_back(10);
                break;
                case 'J':
                cards.push_back(11);
                break;
                case 'Q':
                cards.push_back(12);
                break;
                case 'K':
                cards.push_back(13);
                break;
                case 'A':
                cards.push_back(14);
                break;
                default:
                cards.push_back(s[i] - 48);
                break;
            }
        }
    }

    void set_type(vector<int> cards){
        vector<int> count = vector<int>(13, 0);

        for(int i = 0; i < cards.size(); i++){
            count[cards[i] - 2]++;
        }

        vector<int> count2 = vector<int>(cards.size(), 0);

        for(int i = 0; i < count.size(); i++){
            if(count[i] != 0) count2[count[i] - 1]++;
        }

        if(count2[0] == 5){ type = 1; return; }
        else if (count2[1] == 1 && count2[0] == 3){ type = 2; return; }
        else if (count2[1] == 2 && count2[0] == 1){ type = 3; return; }
        else if (count2[2] == 1 && count2[0] == 2){ type = 4; return; }
        else if (count2[2] == 1 && count2[1] == 1){ type = 5; return; }
        else if (count2[3] == 1 && count2[0] == 1){ type = 6; return; }
        else if (count2[4] == 1 && count2[0] == 0){ type = 7; return; }
        else { type = -1; return; }
    }

    void set_bid(string s){
        bid = stoi(s);
    }
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

void swap_hands(int i, int j, vector<Hand> &h){
    if (i >= h.size() || j >= h.size()) return;
    Hand temp = h[i];
    h[i] = h[j];
    h[j] = temp;
    return;
}

void sort_hands(vector<Hand> &h){
    for(int i = 0; i < h.size(); i++){
        for(int j = 0; j < h.size() - i - 1; j++){
            if(h[j].type == h[j+1].type){
                for(int k = 0; k < h[j].cards.size(); k++){
                    if (h[j].cards[k] > h[j + 1].cards[k]){
                        swap_hands(j,j+1,h);
                        break;
                    } else if (h[j].cards[k] < h[j + 1].cards[k]){
                        break;
                    }
                }
            }
            else if (h[j].type > h[j+1].type) swap_hands(j, j+1, h);
        }
    }

    return;
}

int main (){
    ifstream file;
    file.open("input.txt");

    string s = "";
    vector<Hand> hands;

    while( file.good() ){
        getline(file, s);
        hands.push_back(Hand(split(s, ' ')));
    }

    file.close();

    sort_hands(hands);

    unsigned long long sum = 0;

    for(int i = 0; i < hands.size(); i++){
        sum += hands[i].bid * (i+1);
    } 

    cout << sum;

    return 0;
}
