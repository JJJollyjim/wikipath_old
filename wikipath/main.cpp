//
//  main.cpp
//  wikipath
//
//  Created by Jamie McClymont on 8/01/16.
//  Copyright (c) 2016 Jamie McClymont. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>
#include <array>
#include <fstream>

using namespace std;

void print_string_vec(const vector<string>& v) {
    for (auto& i : v) {
        std::cout << i << endl;
    }
}

vector<uint64_t> pathfind(vector<vector<uint64_t>> *graph, uint64_t startpoint, uint64_t destination) {
    
    
    return {};
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    fstream infile(argv[1]);

    string input_line;
    vector<string> titles;
    unordered_map<string, uint64_t> indices;
    uint64_t index = 0;
    
    while (getline(infile, input_line)) {
        /*cout << input_line[0];*/
        
        
        if (input_line[0] == 0x00) {
            getline(infile, input_line);
            
            titles.push_back(input_line);
            indices[input_line] = index;
            index++;
        }
        
    }
    
    titles.shrink_to_fit();
    
    cout << "Step 1 complete" << endl;
    
    infile.clear();
    infile.seekg(0);
    index = 0;
    
    vector<vector<uint64_t>> links (titles.size(), {});
    bool first_loop = true;
    
    while (getline(infile, input_line)) {
        if (input_line[0] == 0x00) {
            
            if (first_loop) {
                first_loop = false;
            } else {
                links[index].shrink_to_fit();
                index++;
            }
            
            getline(infile, input_line);
            
        } else {
            if (input_line[0] >= 'a' && input_line[0] <= 'z'){
                input_line[0] -= 32;
            }
            
            if (indices[input_line] != 0) {
                links[index].push_back(indices[input_line]);
            }
        }
    }
    
    links.shrink_to_fit();
    
    cout << "Step 2 complete" << endl;
    
    string title = "Harrier Jump Jet";
    uint64_t id = indices[title];
    
    pathfind(&links, indices["Breadth-first search"], indices["Abstract data type"]);

    return 0;
}


