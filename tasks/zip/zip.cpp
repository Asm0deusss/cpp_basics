#include "zip.h"

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    return Zipped(a_begin, a_end, b_begin, b_end);
}

Zipped::Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    list1_begin_ = a_begin;
    list2_begin_ = b_begin;
    list1_end_ = a_end;
    list2_end_ = b_end;
}

Zipped& Zipped::operator++() {
    ++cur_list1_;
    ++cur_list2_;
    return *this;
}

bool Zipped::operator!=(const Zipped& end) const {
    if (cur_list1_ != list1_end_ && cur_list2_ != list2_end_) {
        return true;
    }
    return false;
}

Zipped Zipped::begin() {
    cur_list1_ = list1_begin_;
    cur_list2_ = list2_begin_;
    return *this;
}

Zipped Zipped::end() const {
    return *this;
}

ZippedPair Zipped::operator*() {
    return {*cur_list1_, *cur_list2_};
};
