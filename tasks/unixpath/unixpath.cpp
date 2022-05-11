#include "unixpath.h"
#include <vector>
#include <iostream>

void AddMemo(std::vector<std::string>& vec, std::string& memo, std::string_view& path, const std::size_t& index_begin,
             const std::size_t& index_length) {
    if (index_length > 0 && index_begin < path.length()) {
        memo = std::string(path.begin() + index_begin, path.begin() + index_begin + index_length);
        vec.push_back(memo);
    }
}

void UpdIndex(const std::size_t& i, std::size_t& index_begin, std::size_t& index_length) {
    index_begin = i + 1;
    index_length = 1;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string ans;
    std::string memo;
    std::size_t index_begin = 0;
    std::size_t index_length = 1;
    std::vector<std::string> dir;
    for (std::size_t i = 0; i < current_working_dir.size(); ++i) {
        if (current_working_dir[i] == '/') {
            --index_length;
            AddMemo(dir, memo, current_working_dir, index_begin, index_length);
            UpdIndex(i, index_begin, index_length);
        } else {
            ++index_length;
        }
    }
    AddMemo(dir, memo, current_working_dir, index_begin, index_length - 1);
    index_begin = 0;
    index_length = 1;
    std::size_t found = path.find('.');
    if (found == std::string::npos) {
        dir.clear();
    }
    for (std::size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '.' && i != path.size() - 1 && path[i + 1] == '.') {
            if (!dir.empty()) {
                dir.pop_back();
            }
            UpdIndex(i, index_begin, index_length);
        } else if (path[i] == '/') {
            --index_length;
            AddMemo(dir, memo, path, index_begin, index_length);
            UpdIndex(i, index_begin, index_length);
        } else if (path[i] == '.') {
            UpdIndex(i, index_begin, index_length);
        } else if (path[i] != '.' && path[i] != '/') {
            ++index_length;
        }
    }
    AddMemo(dir, memo, path, index_begin, index_length - 1);
    for (std::size_t i = 0; i < dir.size(); ++i) {
        ans += '/';
        ans += dir[i];
    }
    if (ans.empty()) {
        ans = '/';
    }
    return ans;
}
