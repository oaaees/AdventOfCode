#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

int main(){
    string line;
    vector<int> intervals;
    int count = 0;

    // Read File
    ifstream ReadFile("input.txt");

    while (getline(ReadFile, line)) {
        int last = 0, end = line.size();

        for(int i = 0; i <= end; i++){
            if(line[i] == '-' || line[i] == ',' || i == end){
                string number;

                number = line.substr(last, i-last);
                last = i+1;

                intervals.push_back(stoi(number));
            }
        }

        if((intervals[0] >= intervals[2] && intervals[0] <= intervals[3]) || //Either the start of the first interval is enclosed by the second interval
           (intervals[2] >= intervals[0] && intervals[2] <= intervals[1])){  // Or    the start of the second interval is enclosed by the first interval
            count++;
           }

        intervals = {}; //Flush the array and start over with next line
    }

    ReadFile.close(); 

    cout << "Score is: " << count << endl;

    return 0;
}