#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Card {
    int ID;
    vector<int> winning_numbers;
    vector<int> scratched_numbers;

    Card(string line) {
        ID = stoi(line.substr(5,3));

        for(int i = 0; i < 10; i++){
            winning_numbers.push_back(stoi(line.substr(10 + 3*i, 2)));
        }

        for(int i = 0; i < 25; i++){
            scratched_numbers.push_back(stoi(line.substr(42 + 3*i, 2)));
        }
    }

    int calculatePoints(){
        int points = 0;
        for(int i = 0; i < winning_numbers.size(); i++){
            for(int j = 0; j < scratched_numbers.size(); j++){
                if(winning_numbers[i] == scratched_numbers[j]){
                    if(points == 0){
                        points++;
                    } else {
                        points *= 2;
                    }
                }
            }
        }
        return points;
    }

    ~Card(){}
};

int main (){
    ifstream file;
    file.open("input.txt");

    string line = "";
    int sum = 0;

    while( file.good() ){
        getline(file, line);
        Card card = Card(line);
        sum += card.calculatePoints();
    }

    file.close();
    cout << sum;

    return 0;
}