#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> student_sequence;
    std::vector<std::string> ans;
    ans.reserve(queries.size());
    for (const auto& i : student_actions) {
        switch (i.side) {
            case Side::Top:
                student_sequence.push_front(i.name);
                break;
            case Side::Bottom:
                student_sequence.push_back(i.name);
                break;
        }
    }
    for (const auto& i : queries) {
        ans.push_back(student_sequence[i - 1]);
    }
    return ans;
}
