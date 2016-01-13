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
#include "fileinput.hpp"

using namespace std;

void print_string_vec(const vector<string>& v) {
    for (auto& i : v) {
        std::cout << i << endl;
    }
}

auto pathfind(vector<vector<uint64_t>> &graph, uint64_t startpoint, uint64_t destination) {
    vector<int32_t> distances (graph.size(), -1);
    vector<int64_t> parents (graph.size(), -1);
    
    queue<int64_t> q;
    
    q.push(startpoint);
    distances[startpoint] = 0;
    
    int64_t current_idx;
    int32_t current_distance;
    while (!q.empty()) {
        current_idx = q.front();
        current_distance = distances[current_idx];
        
        q.pop();
        
        for (auto child : graph[current_idx]) {
            if (distances[child] == -1) {
                if (child == destination) {
                    return current_distance + 1;
                }
                
                distances[child] = current_distance + 1;
                parents[child] = current_idx;
                q.push(child);
            }
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    vector<string> titles;
    unordered_map<string, uint64_t> indices;
    
    {
        enum class State {
            Skipping, Copying
        };
        auto state = State::Skipping;
        uint64_t index = 0;
        string input_line;
        process_file_chars(argv[1], [&state, &input_line, &titles, &indices, &index](char c) {
            if (state == State::Skipping) {
                if (c == '\0') {
                    state = State::Copying;
                }
            } else {
                if (c == '\n') {
                    if (input_line.empty()) {
                        return; // newline after \0, so stay in copying state
                    } else {
                        state = State::Skipping;
                        titles.push_back(input_line);
                        indices[input_line] = index;
                        ++index;
                        input_line.clear();
                    }
                } else {
                    input_line.push_back(c);
                }
            }
        });
    }
    
    titles.shrink_to_fit();
    
    cout << "Step 1 complete" << endl;
    
    vector<vector<uint64_t>> links (titles.size(), vector<uint64_t>{});
    
    vector<vector<uint64_t>> links (titles.size(), vector<uint64_t> {});
    bool first_loop = true;
    
    while (getline(infile, input_line)) {
        if (input_line[0] == 0x00) {
            
            if (first_loop) {
                first_loop = false;
            } else {
                links[index].shrink_to_fit();
                index++;
            }
            switch (state) {
                case State::Nullbyte:
                    if (c == '\n') {
                        state = State::Title;
                    }
                    break;
                case State::Title:
                    if (c == '\n') {
                        state = State::Links;
                    }
                    break;
                case State::Links:
                    if (c != '\n') {
                        line.push_back(c);
                    } else {
                        if (line[0] >= 'a' && line[0] <= 'z')
                            line[0] -= 32;
                        if (indices[line] != 0) {
                            links[index].push_back(indices[line]);
                        }
                        line.clear();
                    }
                    break;
            }
        });
    }
    
    cout << "Step 2 complete" << endl;
    
    pathfind(links, indices["Breadth-first search"], indices["Abstract data type"]);

    return 0;
}
