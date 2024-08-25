#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm> 

using namespace std; 

struct Monkey {
    int ID;
    queue<long long int> items;
    long long int (* operation)(long long int);
    int (* test)(long long int);
    unsigned int count_inspections{0};

    Monkey (int ID, queue<long long int> st, long long int (* op)(long long int), int (* test)(long long int)) : ID(ID), items(st), operation(op), test(test) {}

    int get_front_item(){
        int item = items.front();
        count_inspections++;
        items.pop();
        return item;
    };
};

int main (){
    vector<Monkey> monkeys = {};
    monkeys.push_back(Monkey(0, queue<long long int>({66, 79}) , [](long long int old){ return old * 11; }, [](long long int x ){ return (x % 7 == 0) ? 6 : 7; }));
    monkeys.push_back(Monkey(1, queue<long long int>({84, 94, 94, 81, 98, 75}) , [](long long int old){ return old * 17; }, [](long long int x ){ return (x % 13 == 0) ? 5 : 2; }));
    monkeys.push_back(Monkey(2, queue<long long int>({85, 79, 59, 64, 79, 95, 67}) , [](long long int old){ return old + 8; }, [](long long int x ){ return (x % 5 == 0) ? 4 : 5; }));
    monkeys.push_back(Monkey(3, queue<long long int>({70}) , [](long long int old){ return old + 3; }, [](long long int x ){ return (x % 19 == 0) ? 6 : 0; }));
    monkeys.push_back(Monkey(4, queue<long long int>({57, 69, 78, 78}) , [](long long int old){ return old + 4; }, [](long long int x ){ return (x % 2 == 0) ? 0 : 3; }));
    monkeys.push_back(Monkey(5, queue<long long int>({65, 92, 60, 74, 72}) , [](long long int old){ return old + 7; }, [](long long int x ){ return (x % 11 == 0) ? 3 : 4; }));
    monkeys.push_back(Monkey(6, queue<long long int>({77, 91, 91}) , [](long long int old){ return old * old; }, [](long long int x ){ return (x % 17 == 0) ? 1 : 7; }));
    monkeys.push_back(Monkey(7, queue<long long int>({76, 58, 57, 55, 67, 77, 54, 99}) , [](long long int old){ return old + 6; }, [](long long int x ){ return (x % 3 == 0) ? 2 : 1; }));


    const int ROUNDS = 10000;

    for(int i = 0; i < ROUNDS; i++){
        for(int j = 0; j < monkeys.size(); j++){
            while(!monkeys[j].items.empty()){
                long long int worry = monkeys[j].get_front_item();
                worry = monkeys[j].operation(worry) % 9699690;               
                int throw_to = monkeys[j].test(worry);
                monkeys[throw_to].items.push(worry);
            }
        }
    }

    sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b){ return a.count_inspections > b.count_inspections; });

    for(int i = 0; i < monkeys.size(); i++){
        cout << "Monkey " << monkeys[i].ID << " inspected items " << monkeys[i].count_inspections << " times\n";
    }

    unsigned long long result = (unsigned long long)monkeys[0].count_inspections * (unsigned long long)monkeys[1].count_inspections;

    cout << result;

    return 0;
}