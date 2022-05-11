#include "word2vec.h"
#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (vectors.empty()) {
        return {};
    }
    std::vector<std::string> ans;
    const std::size_t n = vectors[0].size();
    std::size_t cur_comp = 0;
    std::size_t max_comp = 0;
    for (std::size_t i = 1; i < vectors.size(); ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            cur_comp += vectors[0][j] * vectors[i][j];
        }
        if (cur_comp == max_comp) {
            ans.push_back(words[i]);
        } else if (cur_comp > max_comp) {
            max_comp = cur_comp;
            ans.clear();
            ans.push_back(words[i]);
        }
        cur_comp = 0;
    }
    return ans;
}
