#include "search.h"

bool SortFunc(const std::pair<size_t, float>& fir, const std::pair<size_t, float>& sec) {
    if (fir.second == sec.second) {
        return fir.first < sec.first;
    }
    return fir.second > sec.second;
}

void SearchEngine::ViewPars() {
    size_t index_left = 0;
    size_t find;
    while (true) {
        find = text_ref_.find('\n', index_left);
        if (find != std::string_view::npos) {
            index_.push_back(find);
            index_left = find + 1;
        } else {
            break;
        }
    }
}

void AddStr(std::string& memo, std::set<std::string>& query_pars) {
    if (!memo.empty()) {
        query_pars.insert(memo);
        memo.clear();
    }
}

void SearchEngine::AddVec(const std::string& memo, size_t& index_begin, size_t& length, const size_t& i) {
    if (length > 0) {
        std::string add = std::string(memo.begin() + index_begin, memo.begin() + index_begin + length);
        ++precounted_tf_.back()[add];
        text_pars_.back().push_back(add);
    }
    length = 0;
    index_begin = i + 1;
}

void SearchEngine::ParsStr(std::string& memo) {
    precounted_tf_.push_back({});
    text_pars_.push_back({});
    size_t index_begin = 0;
    size_t length = 0;
    for (size_t i = 0; i < memo.size(); ++i) {
        if (isalpha(memo[i])) {
            ++length;
        } else {
            AddVec(memo, index_begin, length, i);
        }
    }
    AddVec(memo, index_begin, length);
    for (const auto& i : precounted_tf_.back()) {
        if (i.second) {
            ++precounted_idf_[i.first];
        }
    }
    memo.clear();
}

std::string_view SearchEngine::MakeString(const size_t& ind) const {
    size_t index_right;
    size_t index_left;
    if (ind < index_.size()) {
        index_right = index_[ind] - 1;
        if (ind == 0) {
            index_left = 0;
        } else {
            index_left = index_[ind - 1] + 1;
        }
        return text_ref_.substr(index_left, index_right - index_left + 1);
    } else {
        index_left = index_[ind - 1] + 1;
        return text_ref_.substr(index_left, text_ref_.size() - index_left);
    }
}

void SearchEngine::ClearBuild() {
    index_.clear();
    text_pars_.clear();
    precounted_tf_.clear();
    precounted_idf_.clear();
}

void SearchEngine::BuildIndex(std::string_view text) {
    std::string memo;
    text_ref_ = text;
    ClearBuild();
    ViewPars();
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] != '\n') {
            memo += tolower(text[i]);
        } else {
            ParsStr(memo);
        }
    }
    ParsStr(memo);
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::vector<std::pair<size_t, float>> final_res;
    std::vector<std::string_view> ans;
    std::set<std::string> query_pars;
    std::string memo;
    for (size_t i = 0; i < query.size(); ++i) {
        if (isalpha(query[i])) {
            memo += tolower(query[i]);
        } else {
            AddStr(memo, query_pars);
        }
    }
    AddStr(memo, query_pars);

    for (size_t i = 0; i < text_pars_.size(); ++i) {
        float tf_idf = 0;
        for (auto& key : query_pars) {
            if (precounted_tf_[i].contains(key)) {
                tf_idf += static_cast<float>(precounted_tf_[i].at(key)) / static_cast<float>(text_pars_[i].size()) *
                          log(static_cast<float>(text_pars_.size()) / static_cast<float>(precounted_idf_.at(key)));
            }
        }
        final_res.push_back(std::make_pair(i, tf_idf));
    }
    sort(final_res.begin(), final_res.end(), SortFunc);
    for (const std::pair<size_t, float>& i : final_res) {
        if (results_count > 0) {
            ans.push_back(MakeString(i.first));
            --results_count;
        }
    }
    return ans;
}
