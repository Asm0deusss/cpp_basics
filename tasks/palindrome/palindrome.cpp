#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.length() == 0) {
        return true;
    }
    std::size_t left_iter = 0;
    std::size_t right_iter = str.length() - 1;
    while (left_iter < right_iter) {
        if (str[left_iter] == ' ') {
            ++left_iter;
        }
        if (str[right_iter] == ' ') {
            --right_iter;
        }
        if (str[left_iter] != ' ' && str[right_iter] != ' ') {
            if (str[left_iter] != str[right_iter]) {
                return false;
            }
            ++left_iter;
            --right_iter;
        }
    }
    return true;
}
