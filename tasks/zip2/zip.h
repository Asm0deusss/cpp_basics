#pragma once

#include <iterator>

template <typename T1, typename T2>
struct Zipped {

    Zipped(const T1 a_begin, const T1 a_end, const T2 b_begin, const T2 b_end)
        : a_begin(a_begin), a_end(a_end), b_begin(b_begin), b_end(b_end){};
    Zipped& operator++() {
        ++cur_a;
        ++cur_b;
        return *this;
    };
    bool operator!=(const Zipped& end) const {
        if (cur_a != a_end && cur_b != b_end) {
            return true;
        }
        return false;
    };
    Zipped begin() {  // NOLINT
        cur_a = a_begin;
        cur_b = b_begin;
        return *this;
    }
    Zipped end() const {  // NOLINT
        return *this;
    };
    auto operator*() {
        return std::make_pair(*cur_a, *cur_b);
    };

    T1 a_begin;
    T1 a_end;
    T2 b_begin;
    T2 b_end;
    T1 cur_a;
    T2 cur_b;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped<typeof std::begin(sequence1), typeof std::begin(sequence2)>(
        std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}
