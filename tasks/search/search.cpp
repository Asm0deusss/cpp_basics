#include "search.h"
#include <iostream>
#include <unordered_map>
#include <set>
#include <math.h>

bool SortFunc(const std::pair<size_t, float>& fir, const std::pair<size_t, float>& sec) {
    if (fir.second == sec.second) {
        return fir.first < sec.first;
    }
    return fir.second > sec.second;
}

void AddStr(std::set<std::string>& vec, std::string& memo, auto& is_in_str) {
    if (!memo.empty()) {
        is_in_str[memo] = 0;
        vec.insert(memo);
        memo.clear();
    }
}

void AddVec(std::vector<std::vector<std::string>>& vec, const std::string& memo, size_t& index_begin, size_t& length,
            const size_t& i, auto& is_in_str, const auto& query_pars) {
    if (length > 0) {
        std::string add = std::string(memo.begin() + index_begin, memo.begin() + index_begin + length);
        if (query_pars.contains(add)) {
            is_in_str[add] = 1;
        }
        vec.back().push_back(add);
    }
    length = 0;
    index_begin = i + 1;
}

void ParsStr(std::vector<std::vector<std::string>>& vec, std::string& memo, auto& is_in_str, const auto& query_pars,
             auto& query_count) {
    vec.push_back({});
    size_t index_begin = 0;
    size_t length = 0;
    for (size_t i = 0; i < memo.size(); ++i) {
        if (isalpha(memo[i])) {
            ++length;
        } else {
            AddVec(vec, memo, index_begin, length, i, is_in_str, query_pars);
        }
    }
    size_t last = 0;
    AddVec(vec, memo, index_begin, length, last, is_in_str, query_pars);
    memo.clear();
    for (auto& i : query_pars) {
        if (is_in_str[i]) {
            ++query_count[i];
        }
        is_in_str[i] = 0;
    }
}

void ViewPars(const std::string_view& text, std::vector<std::string_view>& view_pars) {
    size_t index_left = 0;
    size_t find;
    while (true) {
        find = text.find('\n', index_left);
        if (find != std::string_view::npos) {
            view_pars.push_back(text.substr(index_left, find - index_left));
            index_left = find + 1;
        } else {
            view_pars.push_back(text.substr(index_left, text.size() - index_left));
            break;
        }
    }
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::pair<size_t, float>> final_res;
    std::vector<std::string_view> ans;
    std::vector<std::vector<std::string>> text_pars;
    std::vector<std::string_view> view_pars;
    std::set<std::string> query_pars;
    std::unordered_map<std::string, size_t> query_count;
    std::unordered_map<std::string, size_t> is_in_str;
    std::string memo;

    ViewPars(text, view_pars);

    for (size_t i = 0; i < query.size(); ++i) {
        if (isalpha(query[i])) {
            memo += tolower(query[i]);
        } else {
            AddStr(query_pars, memo, is_in_str);
        }
    }
    AddStr(query_pars, memo, is_in_str);

    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] != '\n') {
            memo += tolower(text[i]);
        } else {
            ParsStr(text_pars, memo, is_in_str, query_pars, query_count);
        }
    }
    ParsStr(text_pars, memo, is_in_str, query_pars, query_count);

    for (size_t i = 0; i < text_pars.size(); ++i) {
        for (auto& word : text_pars[i]) {
            if (query_pars.contains(word)) {
                ++is_in_str[word];
            }
        }
        float if_idf = 0;
        for (auto& key : query_pars) {
            float add = (static_cast<float>(is_in_str[key]) / static_cast<float>(text_pars[i].size())) *
                        log(static_cast<float>(text_pars.size()) / static_cast<float>(query_count[key]));
            is_in_str[key] = 0;
            if_idf += add;
        }
        if (if_idf > 0) {
            final_res.push_back(std::make_pair(i, if_idf));
        }
    }

    sort(final_res.begin(), final_res.end(), SortFunc);

    for (const auto& i : final_res) {
        if (results_count > 0) {
            ans.push_back(view_pars[i.first]);
            --results_count;
        }
    }
    return ans;
}
