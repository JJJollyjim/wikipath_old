#ifndef fileinput_hpp
#define fileinput_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

template <typename F>
void process_file(const char *path, std::streamsize max_block_size, F lambda) {
    // void lambda(std::string)
    
    struct stat st;
    stat(path, &st);
    const std::streamsize char_count = st.st_size;
    std::fstream in{path};
    
    std::streamsize current_pos = 0;
    while (current_pos < char_count) {
        std::streamsize to_read = std::min(max_block_size, char_count - current_pos);
        auto str = std::string(to_read, char{});
        in.read(&str[0], str.size());
        lambda(str);
        current_pos += to_read;
    }
}

template <typename F>
void process_file_chars(const char *path, F lambda) {
    // void lambda(char)
    process_file(path, 1000000000, [&lambda](std::string chunk) {
        for (char c : chunk) {
            lambda(c);
        }
    });
}

#endif /* fileinput_hpp */
