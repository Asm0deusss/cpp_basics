#pragma once

#include <string_view>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <map>
#include <math.h>

class SearchEngine {
private:
    std::string_view text_ref_;
    std::vector<size_t> index_;
    std::vector<std::vector<std::string>> text_pars_;
    std::vector<std::map<std::string, size_t>> precounted_tf_;
    std::map<std::string, size_t> precounted_idf_;
    void ClearBuild();
    void ViewPars();
    void ParsStr(std::string& memo);
    void AddVec(const std::string& memo, size_t& index_begin, size_t& length, const size_t& i = 0);
    std::string_view MakeString(const size_t& ind) const;

public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;
};
