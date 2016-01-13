#ifndef fileinput_hpp
#define fileinput_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <atomic>
#include <thread>
#include <future>

template <typename F>
void process_file(const char *path, std::streamsize max_block_size, F lambda) {
    // void lambda(char *, std::streamsize)
    
    struct stat st;
    stat(path, &st);
    const std::streamsize char_count = st.st_size;
    std::fstream in{path};
    
    std::streamsize current_pos = 0;
    while (current_pos < char_count) {
        std::streamsize to_read = std::min(max_block_size, char_count - current_pos);
        auto str = static_cast<char *>(malloc(to_read));
        in.read(&str[0], to_read);
        lambda(str, to_read);
        free(str);
        current_pos += to_read;
    }
}

template <typename F>
void process_file_chars(const char *path, F lambda) {
    // void lambda(char)
    process_file(path, 100000000, [&lambda](const char *chunk, std::streamsize size) {
        for (std::streamsize i = 0; i < size; ++i) {
            lambda(*chunk);
            ++chunk;
        }
    });
}

#endif /* fileinput_hpp */
