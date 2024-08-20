#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std; 
using uint = unsigned int;

struct file {
    file * parent;
    vector<file *> children;
    string name;
    uint size;
    bool is_dir;

    file(string _name, uint _size, file * _parent){
        name = _name;
        size = _size;
        parent = _parent;
        children = {};
        is_dir = false;
    }

    file(string _name, file * _parent){
        name = _name;
        size = 0;
        parent = _parent;
        children = {};
        is_dir = true;
    }

    file * search_children(string _name){
        for(int i = 0; i < children.size(); i++){
            if (children[i]->name == _name) return children[i];
        }
        return nullptr;
    }

    void add_children(file * file){
        children.push_back(file);
    }
};

void update_filesystem_sizes(file * x){
    file * parent = x->parent;
    file * child = x;
    uint size = x->size;

    while(parent != nullptr){
        parent->size += size;
        child = parent;
        parent = parent->parent;
    }
}

vector<string> get_input(string filename){
    string line = "";
    vector<string> input = {};

    ifstream ReadFile(filename);

    while (getline(ReadFile, line)) {
        input.push_back(line);
    }

    ReadFile.close();
    return input;
}

vector<string> tokenize_line(string s, char d){
    vector<string> output = {};
    uint last = 0;

    for(int i = 0; i < s.size(); i++){
        if(s[i] == d){
            string token = s.substr(last, i - last);
            last = i + 1;
            if (token.size() > 0) output.push_back(token);
        }
    }

    output.push_back(s.substr(last));
    return output;
}

bool is_user_executed(vector<string> tokens){
    return tokens[0] == "$";
}

int main(int argc, char* argv[]){
    vector<string> input = get_input("input.txt");

    file root("/", nullptr);
    file * current_dir = nullptr;

    for(int i = 0; i < input.size(); i++){
        auto line_tokens = tokenize_line(input[i], ' ');

        if(is_user_executed(line_tokens)){
            if(line_tokens[1] == "cd"){
                if (line_tokens[2] == "/" && current_dir == nullptr){
                    current_dir = &root;
                } else if (line_tokens[2] == "..") {
                    current_dir = current_dir->parent;
                } else {
                    file * found = current_dir->search_children(line_tokens[2]);
                    if (found){
                        current_dir = found;
                    } else {
                        cout << "dir " << line_tokens[2] << " is not found in " << current_dir->name;
                    }
                }
            } else if (line_tokens[1] == "ls"){

            }
        } else {
            // It's assumed that if it is not an user-executed command then is a response from a ls command
            // of course this only works for this problem
            
            if(line_tokens[0] == "dir"){
                file * x = new file(line_tokens[1], current_dir);
                current_dir->add_children(x);
            } else {
                file * x = new file(line_tokens[1], stoul(line_tokens[0]), current_dir);
                current_dir->add_children(x);
                update_filesystem_sizes(x);
            }
        }
    }

    unsigned long long total_disk_space = 70000000;
    unsigned long long update_size = 30000000;
    unsigned long long free_space = total_disk_space - root.size;
    unsigned long long minimum_found = total_disk_space;

    queue<file *> q;
    q.push(&root);

    while(!q.empty()){
        file * current = q.front();

        if(current->is_dir && current->size > update_size - free_space && current->size < minimum_found){
            minimum_found = current->size;
        } 

        for(int i = 0; i < current->children.size(); i++){
            q.push(current->children[i]);
        }

        q.pop();
    }    

    cout << minimum_found;

    return 0;
}