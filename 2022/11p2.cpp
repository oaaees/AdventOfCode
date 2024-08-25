#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm> 

using namespace std; 

struct Monkey {
    int ID;
    queue<unsigned long long int> items;
    int (* operation)(int);
    int (* test)(int);
    int count_inspections{0};

    Monkey (int ID, queue<unsigned long long int> st, int (* op)(int), int (* test)(int)) : ID(ID), items(st), operation(op), test(test) {}

    int get_front_item(){
        int item = items.front();
        count_inspections++;
        items.pop();
        return item;
    };
};

int main (){
    vector<Monkey> monkeys = {};
    monkeys.push_back(Monkey(0, queue<unsigned long long int>({66, 79}) , [](int old){ return old * 11; }, [](int x ){ return (x % 7 == 0) ? 6 : 7; }));
    monkeys.push_back(Monkey(1, queue<unsigned long long int>({84, 94, 94, 81, 98, 75}) , [](int old){ return old * 17; }, [](int x ){ return (x % 13 == 0) ? 5 : 2; }));
    monkeys.push_back(Monkey(2, queue<unsigned long long int>({85, 79, 59, 64, 79, 95, 67}) , [](int old){ return old + 8; }, [](int x ){ return (x % 5 == 0) ? 4 : 5; }));
    monkeys.push_back(Monkey(3, queue<unsigned long long int>({70}) , [](int old){ return old + 3; }, [](int x ){ return (x % 19 == 0) ? 6 : 0; }));
    monkeys.push_back(Monkey(4, queue<unsigned long long int>({57, 69, 78, 78}) , [](int old){ return old + 4; }, [](int x ){ return (x % 2 == 0) ? 0 : 3; }));
    monkeys.push_back(Monkey(5, queue<unsigned long long int>({65, 92, 60, 74, 72}) , [](int old){ return old + 7; }, [](int x ){ return (x % 11 == 0) ? 3 : 4; }));
    monkeys.push_back(Monkey(6, queue<unsigned long long int>({77, 91, 91}) , [](int old){ return old * old; }, [](int x ){ return (x % 17 == 0) ? 1 : 7; }));
    monkeys.push_back(Monkey(7, queue<unsigned long long int>({76, 58, 57, 55, 67, 77, 54, 99}) , [](int old){ return old + 6; }, [](int x ){ return (x % 3 == 0) ? 2 : 1; }));


    const int ROUNDS = 1000;

    for(int i = 0; i < ROUNDS; i++){
        for(int j = 0; j < monkeys.size(); j++){
            while(!monkeys[j].items.empty()){
                int worry = monkeys[j].get_front_item();
                worry = monkeys[j].operation(worry);               
                int throw_to = monkeys[j].test(worry);
                monkeys[throw_to].items.push(worry);
            }
        }
    }

    for(int i = 0; i < monkeys.size(); i++){
        cout << "Monkey " << monkeys[i].ID << " inspected items " << monkeys[i].count_inspections << " times\n";
    }

    sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b){ return a.count_inspections > b.count_inspections; });

    cout << monkeys[0].count_inspections * monkeys[1].count_inspections;

    return 0;
}