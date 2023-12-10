#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    string name;
    string left_name;
    string right_name;
    int left_pos;
    int right_pos;

    Node (string n){
        name = n;
        left_name = "";
        right_name = "";
        left_pos = -1;
        right_pos = -1;        
    }

    Node(string n, string l, string r){
        name = n;
        left_name = l;
        right_name = r;
        left_pos = -1;
        right_pos = -1;
    }
};

int pos_in_graph(string s, vector<Node> &g){
    for(int i = 0; i < g.size(); i++){
        if(g[i].name == s) return i;
    }
    return -1;
}

bool every_element_is_in(vector<int> x, vector<int> y){
    for(int i = 0; i < x.size(); i++){
        bool found = false;
        for(int j = 0; j < y.size(); j++){
            if(x[i] == y[j]){
                found = true;
            }
        }
        if(!found) return false;
    }

    return true;
}

int main (){
    string instructions = "LRRLLRLLRRRLRRLRLRRRLRLLRLRRLRRRLRRRLRRLRRRLRLRRRLRLRRLRLRRRLRRLLRRLLLRRLRLRRRLRLRRRLRRLRRRLRLLRRLRRLRLRRRLRRRLRRLRRLLRLLRRRLRLRRLRRRLRRLRRRLRRRLLLLRRLRLRRRLRRRLLRRLLRRLRRRLRRRLRLRLLRRLRLRLRLRLRRLRLRLRRRLRRLRRLRRLRRRLRLRRRLRLRRLRLLLLRRRLLRRRLRLLRRRLRLLRRRLLRRLRLRLRLRLLLLRRLRRRLRLLRRLRRRLRRRLRLRRLRRLRLLRRRR";
    vector<Node> graph = {};
    vector<int> start = {}, end = {};

    ifstream file;
    file.open("input.txt");

    string s = "";
    int sum = 0;

    while( file.good() ){
        getline(file, s);
        string name = s.substr(0, 3), lname = s.substr(7,3), rname = s.substr(12,3);
        int index = pos_in_graph(name, graph);

        if(index == -1){ 
            graph.push_back(Node(name, lname, rname));
            index = graph.size() - 1;
        } else {
            graph[index].left_name = lname;
            graph[index].right_name = rname; 
        }

        if(graph[index].name[2] == 'A') start.push_back(index);
        if(graph[index].name[2] == 'Z') end.push_back(index);

        for(int i = 0; i < graph.size(); i++){
            if(graph[i].name == graph[index].left_name) graph[index].left_pos = i;
            if(graph[i].name == graph[index].right_name) graph[index].right_pos = i;
        }

        if(graph[index].left_pos == -1){
            graph.push_back(Node(lname));
            graph[index].left_pos = graph.size() - 1;
        }
        if(graph[index].right_pos == -1){
            if(graph[index].right_name != graph.back().name){
                graph.push_back(Node(rname));
            }
            graph[index].right_pos = graph.size() - 1;
        }
    }

    file.close();

    vector<int> current = start;
    vector<int> v_counters = {};

    for (int i = 0; i < current.size(); i++){
        int i_pos = 0;
        int counter = 0;

        while( graph[current[i]].name[2] != 'Z' ){
            if(i_pos >= instructions.size()) i_pos = 0;

            if (instructions[i_pos] == 'L'){
                current[i] = graph[current[i]].left_pos;
            } else {
                current[i] = graph[current[i]].right_pos;
            }

            i_pos++;
            counter++;
        }

        cout << counter << " ";
        v_counters.push_back(counter);
    }

    cout << "\n";
    unsigned long long res = v_counters[0];

    for (int i = 1; i < v_counters.size(); i++){
        res = lcm(res, v_counters[i]);
    }

    cout << res;

    return 0;
}