#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
private:
    std::vector<std::string> beg_dir_;
    std::vector<std::string> cur_dir_;
    std::string memo_;
    void AddMemoConstr(const std::string_view& path, const std::size_t& index_begin, const std::size_t& index_length);
    void AddMemo(const std::string_view& path, const std::size_t& index_begin, const std::size_t& index_length);

public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;
};
