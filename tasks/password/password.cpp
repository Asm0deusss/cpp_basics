#include "password.h"

bool ValidatePassword(const std::string& password) {
    const std::size_t min_length = 8;
    const std::size_t max_length = 14;
    const unsigned char left_border = 33;
    const unsigned char right_border = 126;
    const unsigned char min_valid_types = 3;
    unsigned char is_numb = 0;
    unsigned char is_lower = 0;
    unsigned char is_upper = 0;
    unsigned char is_other = 0;
    if (min_length > password.length() or max_length < password.length()) {
        return false;
    }
    for (std::size_t i = 0; i < password.length(); ++i) {
        if (password[i] >= left_border && password[i] <= right_border) {
            if (std::isdigit(password[i])) {
                is_numb = 1;
            }
            if (std::islower(password[i])) {
                is_lower = 1;
            }
            if (std::isupper(password[i])) {
                is_upper = 1;
            }
            if (std::ispunct(password[i])) {
                is_other = 1;
            }
        } else {
            return false;
        }
    }
    if (is_numb + is_lower + is_upper + is_other >= min_valid_types) {
        return true;
    }
    return false;
}
