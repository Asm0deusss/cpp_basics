#include "unixpath.h"
void UnixPath::AddMemoConstr(const std::string_view &path, const std::size_t &index_begin,
                             const std::size_t &index_length) {
    if (index_length > 0 && index_begin < path.length()) {
        memo_ = std::string(path.begin() + index_begin, path.begin() + index_begin + index_length);
        beg_dir_.push_back(memo_);
        cur_dir_.push_back(memo_);
    }
}

void UnixPath::AddMemo(const std::string_view &path, const std::size_t &index_begin, const std::size_t &index_length) {
    if (index_length > 0 && index_begin < path.length()) {
        memo_ = std::string(path.begin() + index_begin, path.begin() + index_begin + index_length);
        cur_dir_.push_back(memo_);
    }
}

void UpdIndex(const std::size_t &i, std::size_t &index_begin, std::size_t &index_length) {
    index_begin = i + 1;
    index_length = 1;
}

UnixPath::UnixPath(std::string_view initial_dir) {
    size_t index_begin = 0;
    size_t index_length = 1;
    for (std::size_t i = 0; i < initial_dir.size(); ++i) {
        if (initial_dir[i] == '/') {
            --index_length;
            AddMemoConstr(initial_dir, index_begin, index_length);
            UpdIndex(i, index_begin, index_length);
        } else {
            ++index_length;
        }
    }
    AddMemoConstr(initial_dir, index_begin, index_length - 1);
}

void UnixPath::ChangeDirectory(std::string_view path) {
    size_t index_begin = 0;
    size_t index_length = 1;
    std::size_t found = path.find('.');
    if (found == std::string::npos) {
        cur_dir_.clear();
    }
    for (std::size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '.' && i != path.size() - 1 && path[i + 1] == '.') {
            if (!cur_dir_.empty()) {
                cur_dir_.pop_back();
            }
            UpdIndex(i, index_begin, index_length);
        } else if (path[i] == '/') {
            --index_length;
            AddMemo(path, index_begin, index_length);
            UpdIndex(i, index_begin, index_length);
        } else if (path[i] == '.') {
            UpdIndex(i, index_begin, index_length);
        } else if (path[i] != '.' && path[i] != '/') {
            ++index_length;
        }
    }
    AddMemo(path, index_begin, index_length - 1);
}

std::string UnixPath::GetAbsolutePath() const {
    std::string ans;
    for (const auto &i : cur_dir_) {
        ans += '/';
        ans += i;
    }
    if (ans.empty()) {
        ans = '/';
    }
    return ans;
}

std::string UnixPath::GetRelativePath() const {
    std::string ans;
    size_t ind = 0;
    while (ind < cur_dir_.size() && ind < beg_dir_.size()) {
        if (cur_dir_[ind] != beg_dir_[ind]) {
            for (size_t i = 0; i < beg_dir_.size() - ind; ++i) {
                if (i != 0) {
                    ans += '/';
                }
                ans += "..";
            }
            break;
        }
        ++ind;
    }
    if (ans.empty()) {
        ans += ".";
    }
    while (ind < cur_dir_.size()) {
        ans += '/';
        ans += cur_dir_[ind];
        ++ind;
    }
    return ans;
}
