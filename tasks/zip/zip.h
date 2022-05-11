#pragma once

#include <forward_list>
#include <string>
#include <vector>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
public:
    Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
    Zipped& operator++();
    bool operator!=(const Zipped& end) const;
    Zipped begin();      // NOLINT
    Zipped end() const;  // NOLINT
    ZippedPair operator*();

private:
    Iterator list1_begin_;
    Iterator list2_begin_;
    Iterator list1_end_;
    Iterator list2_end_;
    Iterator cur_list1_;
    Iterator cur_list2_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
