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

vector<uint64_t> pathfind(vector<vector<uint64_t>> *graph, uint64_t startpoint, uint64_t destination) {
    
    
    return {};
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
    
    {
        uint64_t index = -1;
        enum class State {
            Nullbyte,
            Title,
            Links
        };
        auto state = State::Nullbyte;
        std::string line;
        process_file_chars(argv[1], [&](char c) {
            if (c == '\0') {
                state = State::Nullbyte;
                ++index;
                return;
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
    
    string title = "Harrier Jump Jet";
    uint64_t id = indices[title];
    
    pathfind(&links, indices["Breadth-first search"], indices["Abstract data type"]);

    return 0;
}


